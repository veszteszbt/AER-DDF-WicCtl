#ifndef WICP_PROCESS_LOG_H
# define WICP_PROCESS_LOG_H
# include <mutex>
# include <condition_variable>
# include <thread>
# include <string>
# include <list>
# include <iomanip>
# include <chrono>

# include <cppconn/driver.h>
# include <cppconn/exception.h>
# include <cppconn/resultset.h>
# include <cppconn/statement.h>

namespace wicp {
namespace process
{
	template<typename TEnv>
	class log
	{
		typedef typename TEnv::clock           clock;

		typedef typename TEnv::history_type    history_type;

		typedef typename TEnv::history_record  history_record;

		typedef typename TEnv::value_type      value_type;

		
		static const uint32_t cooldown_time                         = TEnv::cooldown_time;

		constexpr static history_type         &history              = TEnv::history;

		constexpr static std::mutex           &history_lock         = TEnv::history_lock;


		static std::thread *proc_thread;

		static std::list<std::string> buffer;

		static std::mutex buffer_lock;

		static typename clock::time_point time;

                static std::mutex               suspend_lock;

                static std::condition_variable  suspend_cv;

		static void start()
		{
			using namespace std::chrono_literals;

			sql::Connection *con = get_driver_instance()->connect("tcp://127.0.0.1:3306","root","Ge25Za40");

			std::cout << "\e[32;01m - \e[0mwicp log process: initialized" << std::endl;

			while(1)
			{
				buffer_lock.lock();
				if(!buffer.size())
				{
					buffer_lock.unlock();
					std::cout << "\e[37;01m - \e[0mwicp log process: nothing to do; suspending until next notify" << std::endl;
					std::unique_lock<std::mutex> ul(suspend_lock);
					suspend_cv.wait(ul);
					continue;
				}
				buffer_lock.unlock();

					sql::Statement *s = con->createStatement();
					s->execute("START TRANSACTION");
					while(1)
					{
						buffer_lock.lock();
						if(!buffer.size())
						{
							buffer_lock.unlock();
							break;
						}
						const std::string q = buffer.back();
						buffer.pop_back();
						buffer_lock.unlock();
						try
						{
							std::cout << "\e[36;01m" << q << "\e[0m" << std::endl;
							s->execute(q.c_str());
						}
						catch(sql::SQLException &ex)
						{
							std::cout << "\e[31;01m - \e[0mwicp log process: MySQL error " << ex.getErrorCode() <<
								" in query `" << q << "': " << ex.what() << std::endl;
						}
					}
					s->execute("COMMIT");
					delete s;
			}
		}

	public:
		static void init()
		{
			proc_thread = new std::thread(start);
			time = clock::time_point::min();
		};

		static void uninit()
		{
			delete proc_thread;
		}

		static void notify()
		{
			history_lock.lock();
			const history_record r = history.front();
			history_lock.unlock();

			buffer_lock.lock();
			if(r.time > time)
			{
				time = r.time;
				buffer_lock.unlock();

				std::stringstream s;
				s << "INSERT INTO `wic`.`log_wicp` VALUES (" << 
					std::chrono::time_point_cast<std::chrono::nanoseconds>(r.time).time_since_epoch().count() << ',' <<
					TEnv::class_id << ',' <<
					TEnv::member_id << ",X'" << std::hex;

				for(int i = 0; i < sizeof(value_type); ++i)
					s << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(*reinterpret_cast<const uint8_t*>(&r.value));
					
				s << "');";

				buffer_lock.lock();
				buffer.push_front(s.str());
				buffer_lock.unlock();

				std::lock_guard<std::mutex> lg(suspend_lock);
				suspend_cv.notify_one();
			}
			else
				buffer_lock.unlock();
		}
	};

	template<typename e>
	std::thread *log<e>::proc_thread;

	template<typename e>
	std::list<std::string> log<e>::buffer;

	template<typename e>
	std::mutex log<e>::buffer_lock;

	template<typename e>
	typename log<e>::clock::time_point log<e>::time;

	template<typename e>
	std::mutex               log<e>::suspend_lock;

	template<typename e>
	std::condition_variable  log<e>::suspend_cv;
}}
#endif
