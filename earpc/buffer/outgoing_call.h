#ifndef WIC_EARPC_BUFFER_OUTGOING_CALL_H
# define WIC_EARPC_BUFFER_OUTGOING_CALL_H
# include <cstdint>
# include <list>
# include <chrono>
# include <mutex>
# include <earpc/buffer/outgoing_call_record.h>
namespace wic {
namespace earpc {
namespace buffer
{
	template<typename TEnv>
	class outgoing_call
	{
		typedef typename TEnv::command_id_type  command_id_type;

		typedef typename TEnv::call_id_type     call_id_type;

	public:
		typedef outgoing_call_record<TEnv>        record_type;

		typedef typename record_type::callback_type        callback_type;

		typedef std::list<record_type>            container_type;

		typedef typename container_type::iterator iterator;

		static container_type                     container;

		static std::mutex                         mutex;

		static void lock()
		{ mutex.lock(); }

		static void unlock()
		{ mutex.unlock(); }

		static iterator begin()
		{ return container.begin(); }

		static iterator end()
		{ return container.end(); }

		static iterator find(net::ipv4_address ip, call_id_type call_id)
		{
			iterator i = begin();
			while(i != end() && !(call_id == i-> call_id && ip == i->ip))
				++i;
			return i;
		}

		static void push(const record_type &v)
		{ container.push_back(v); }

		static void push(
			net::ipv4_address i,
			command_id_type   cmd,
			call_id_type      cid,
			const void       *a,
			uint16_t          as,
			uint16_t          rs,
			callback_type     cb
		)
		{ container.push_back(record_type(i,cmd,cid,a,as,rs,cb)); }

		static void erase(iterator i)
		{ container.erase(i); }

		static bool has_call_to(net::ipv4_address ip)
		{
			for(auto i = begin(); i != end(); ++i)
				if(i->ip == ip)
					return true;
			return false;
		}
	};

	template<typename e>
	typename outgoing_call<e>::container_type outgoing_call<e>::container;

	template<typename e>
	std::mutex outgoing_call<e>::mutex;
}}}
#endif
