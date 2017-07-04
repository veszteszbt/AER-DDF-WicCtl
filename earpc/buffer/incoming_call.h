#ifndef WIC_EARPC_BUFFER_INCOMING_CALL_H
# define WIC_EARPC_BUFFER_INCOMING_CALL_H
# include <list>
# include <chrono>
# include <mutex>
namespace wic {
namespace earpc {
namespace buffer
{
	template<typename TEnv>
	class incoming_call
	{
		typedef typename TEnv::command_id_type  command_id_type;

		typedef typename TEnv::call_id_type     call_id_type;

		typedef typename TEnv::time_point       time_point;

		typedef typename TEnv::clock            clock;

		static const uint32_t call_timeout =    TEnv::call_timeout;

	public:
		struct record_type
		{
			net::ipv4_address ip;

			uint16_t          port;

			command_id_type   command_id;

			call_id_type      call_id;

			uint16_t          checksum;

			time_point        expiry;

			record_type() {}

			record_type(
				net::ipv4_address i,
				uint16_t p,
				command_id_type cmd,
				call_id_type cid,
				uint16_t chk
			)
				: ip(i)
				, port(p)
				, command_id(cmd)
				, call_id(cid)
				, checksum(chk)
				, expiry(clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(call_timeout)))
			{}

		};

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

		static void push(const record_type &v)
		{ container.push_back(v); }

		static iterator find(net::ipv4_address ip, call_id_type call_id)
		{
			iterator i = begin(); 
			while(i != end() && !(i->call_id == call_id && i->ip == ip))
				++i;
			return i;
		}

		static void push(
			net::ipv4_address i,
			uint16_t p,
			command_id_type cmd,
			call_id_type cid,
			uint16_t chk
		)
		{ container.push_back(record_type(i,p,cmd,cid,chk)); }

		static void erase(iterator i)
		{ container.erase(i); }
	};

	template<typename e>
	typename incoming_call<e>::container_type incoming_call<e>::container;

	template<typename e>
	std::mutex incoming_call<e>::mutex;

}}}
#endif
