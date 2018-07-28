#ifndef WICP_PROCESS_COMMIT_H
# define WICP_PROCESS_COMMIT_H
# include <atomic>
# include <condition_variable>
# include <cstdint>
# include <chrono>
# include <mutex>
# include <pthread.h>
# include <thread>
# include <queue>
# include <unordered_set>
# include <net/ipv4_address.h>
# include <journal.h>
# include <types/time.h>
# include <wicp/types/property_record.h>

namespace wicp {
namespace process
{
	template<typename TEnv>
	class commit
	{
		typedef typename TEnv::object_id_type		object_id_type;

		struct cooldown_record
		{
			object_id_type	object_id;

			uint64_t		cooldown_time;

			cooldown_record() = default;

			cooldown_record(
				object_id_type pobject_id,
				uint64_t pcooldown_time
			)
				: object_id(pobject_id)
				, cooldown_time(pcooldown_time)
			{}

			bool operator()(const cooldown_record &lhs, const cooldown_record &rhs) const
			{ return lhs.cooldown_time < rhs.cooldown_time; }
		};

		typedef std::chrono::high_resolution_clock	clock;

		typedef typename TEnv::proc_sync			proc_sync;

		typedef typename TEnv::proc_log				proc_log;

		typedef typename TEnv::property_data_type	property_data_type;

		typedef typename TEnv::history_type			history_type;

		typedef typename TEnv::history_record		history_record;

		typedef typename TEnv::member_id_type		member_id_type;

		typedef typename TEnv::encap_object_type	encap_object_type;

		typedef typename TEnv::wic_class			wic_class;

		typedef typename TEnv::member_id 			member_id;

		typedef typename TEnv::property_record_base	property_record_base;

		typedef sched::lockable<
			std::priority_queue<
				cooldown_record,
				std::vector<cooldown_record>,
				cooldown_record
		>>											cooldowns_type;

		typedef sched::lockable<
			std::unordered_set<object_id_type>
		>											object_id_buffer_type;

		static cooldowns_type						cooldowns;

		static object_id_buffer_type				object_id_buffer;

		static const uint32_t 	cooldown_time	= 	TEnv::cooldown_time;

		static std::mutex							suspend_lock;

		static std::condition_variable				suspend_cv;

		static std::thread							*proc_thread;

		static volatile bool						is_running;

		static journal jrn(uint8_t level)
		{
			int* x, *y;
			return journal(level,"wicp.commit") << "property: " << std::hex <<
				TEnv::class_id << "::" << TEnv::member_id::value << ' ';
		}
		
		template <typename Tproperty>
		static std::enable_if_t<
			std::is_base_of_v<
				property_record_base, 
				Tproperty
			>, bool
		> is_sync_needed(const Tproperty &property)
		{ return !property.history.empty() && property.local_value != property.history.front().value; }


		static void check_cooldowns()
		{
			cooldowns.lock();
			while(!cooldowns.empty())
			{
				const auto lowest = cooldowns.top();
				const auto current_time = ::types::time::msec(clock::now());
				if(lowest.cooldown_time <= current_time)
				{
					wic_class::template lock<encap_object_type>();
					auto lowest_it = 
						wic_class::template find<encap_object_type>(lowest.object_id);
					if(lowest_it != wic_class::end())
					{
						auto &property = lowest_it->second.properties.template get<member_id>();
						property.cooldown_pending = false;
						if(is_sync_needed(property))
							safe_emplace_to_object_id_buffer(lowest.object_id);

						jrn(journal::trace) << 
							"object: "<< std::hex << lowest.object_id << 
							"; cooldown expired" << 
							journal::end;
					}
					cooldowns.pop();
					wic_class::template unlock<encap_object_type>();
				}
				else
					break;
			}
			cooldowns.unlock();
		}
		static void start()
		{
			jrn(journal::debug) << "initialized" << journal::end;
			while(is_running)
			{
				while(1)
				{
					check_cooldowns(); // TODO proper name
					object_id_buffer.lock();

					if(object_id_buffer.empty())
					{
						object_id_buffer.unlock();
						break;
					}
					
					const object_id_type object_id = *object_id_buffer.begin();
					object_id_buffer.erase(object_id_buffer.begin());
					object_id_buffer.unlock();

					
					wic_class::template lock<encap_object_type>();
					auto it = wic_class::template find<encap_object_type>(object_id);
					if(it == wic_class::end())
					{
						wic_class::template unlock<encap_object_type>();
						jrn(journal::error) << "Invalid `" << wic_class::name << 
							"' object reference " << std::hex << object_id << journal::end;
						continue;
					}

					it->second.property_lock.lock();
					auto &property = it->second.properties.template get<member_id>();
					if(property.cooldown_pending)
					{
						it->second.property_lock.unlock();
						wic_class::template unlock<encap_object_type>();
						jrn(journal::trace) << "cooldown pending; ignoring object: " << std::hex << object_id << journal::end;
						continue;
					}
					else if(!is_sync_needed(property))
					{
						it->second.property_lock.unlock();
						wic_class::template unlock<encap_object_type>();
						jrn(journal::trace) << "no change; ignoring object " << std::hex << object_id << journal::end;
						continue;
					}
					else
						property.cooldown_pending = true;

					jrn(journal::trace) << 
						"object: " << std::hex << object_id << 
						"; comitting new value to history; length is " << int(property.history.size()) << 
						journal::end;

					const history_record hr(property.local_value);
					property.history.emplace_front(hr);
					if(property.history.size() > TEnv::history_size)
						property.history.pop_back();

					if(TEnv::sync_local(property))
					{
						it->second.property_lock.unlock();
						wic_class::template unlock<encap_object_type>();
						// TODO journal
						property.on_change(object_id);
					}
					else
					{
						it->second.property_lock.unlock();
						wic_class::template unlock<encap_object_type>();
					}

					proc_sync::notify(object_id);
					proc_log::notify(object_id);
					cooldowns.lock();
					cooldowns.emplace(object_id, ::types::time::msec(hr.time) + static_cast<uint32_t>(cooldown_time));
					cooldowns.unlock();
				}
				std::unique_lock<std::mutex> ul(suspend_lock);
				object_id_buffer.lock();
				if(object_id_buffer.empty())
				{
					object_id_buffer.unlock();
					if(cooldowns.empty())
					{
						jrn(journal::trace) << "no change; suspending until next notify" << journal::end;
						suspend_cv.wait(ul);
					}
					else
					{
						cooldowns.lock();
						const auto lowest = cooldowns.top();
						const auto current_time = ::types::time::msec(clock::now());
						if(lowest.cooldown_time > current_time)
						{
							cooldowns.unlock();
							jrn(journal::trace) << "no change; suspending for " << lowest.cooldown_time - current_time << "ms" << journal::end;
							suspend_cv.wait_until(
								ul, 
								clock::time_point(std::chrono::milliseconds(lowest.cooldown_time))
							);
							jrn(journal::trace) << "resuming" << journal::end;
							wic_class::template lock<encap_object_type>();
							auto lowest_it = 
								wic_class::template find<encap_object_type>(lowest.object_id);
							if(lowest_it != wic_class::end())
							{
								auto &property = lowest_it->second.properties.template get<member_id>();
								if(is_sync_needed(property))
									safe_emplace_to_object_id_buffer(lowest.object_id);
							}
							wic_class::template unlock<encap_object_type>();
						}
						else
						{
							cooldowns.unlock();
							jrn(journal::trace) << "no change; suspending until next notify" << journal::end;
							suspend_cv.wait(ul);
						}
					}
				}
				else
					object_id_buffer.unlock();
			}
			jrn(journal::debug) << "uninitialized" << journal::end;
		}

		static void safe_emplace_to_object_id_buffer(object_id_type object_id)
		{
			object_id_buffer.lock();
			object_id_buffer.emplace(object_id);
			object_id_buffer.unlock();
		}
	public:

		static void init()
		{
			is_running = true;
			proc_thread = new std::thread(start);

#ifdef __linux__
			pthread_setname_np(proc_thread->native_handle(),"wicp commit");
#endif

		}

		static void uninit()
		{
			is_running = false;
			proc_thread->join();
			delete proc_thread;
		}

		static void notify(object_id_type pobject_id)
		{
			safe_emplace_to_object_id_buffer(pobject_id);
			std::lock_guard<std::mutex> lg(suspend_lock);
			suspend_cv.notify_one();
		}
	};

	template<typename c>
	std::mutex commit<c>::suspend_lock;

	template<typename c>
	std::thread *commit<c>::proc_thread;

	template<typename c>
	std::condition_variable commit<c>::suspend_cv;

	template<typename c>
	volatile bool           commit<c>::is_running;

	template <typename TEnv>
	typename commit<TEnv>::cooldowns_type commit<TEnv>::cooldowns;

	template <typename TEnv>
	typename commit<TEnv>::object_id_buffer_type commit<TEnv>::object_id_buffer;
}}
#endif
