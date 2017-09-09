#ifndef WIC_EARPC_BUFFER_OUTGOING_CALL_H
# define WIC_EARPC_BUFFER_OUTGOING_CALL_H
# include <cstdint>
# include <list>
# include <chrono>
# include <mutex>
namespace wic {
namespace earpc {
namespace buffer
{
	template<typename TEnv>
	class outgoing_call
	{
		typedef typename TEnv::command_id_type  command_id_type;

		typedef typename TEnv::call_id_type     call_id_type;

		typedef typename TEnv::time_point       time_point;

		typedef typename TEnv::clock            clock;

		static const uint32_t call_timeout =    TEnv::call_timeout;

	public:
		typedef void (*callback_type)(
			net::ipv4_address,
			command_id_type,
			void*
		);

		struct record_type
		{
			net::ipv4_address ip;

			call_id_type      call_id;

			command_id_type   command_id;

			callback_type     callback;

			const void       *arg; 

			uint16_t          arg_size;
				
			uint16_t          return_size;

			time_point        expiry;
			

			record_type() {}

			template<typename Treturn>
			record_type(
				net::ipv4_address i,
				command_id_type cmd,
				call_id_type cid,
				const void *a,
				uint16_t as,
				void (*cb)(
					net::ipv4_address,
					command_id_type,
					Treturn*
				)
			)       
				: ip(i)
				, call_id(cid)
				, command_id(cmd)
				, callback(reinterpret_cast<callback_type>(cb))
				, arg(a)
				, arg_size(as)
				, return_size(sizeof(Treturn))
				, expiry(clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(call_timeout)))
			{}

			record_type(
				net::ipv4_address i,
				command_id_type cmd,
				call_id_type cid,
				const void *a,
				uint16_t as,
				void (*cb)(
					net::ipv4_address,
					command_id_type,
					const std::string &
				)
			)       
				: ip(i)
				, call_id(cid)
				, command_id(cmd)
				, callback(reinterpret_cast<callback_type>(cb))
				, arg(a)
				, arg_size(as)
				, return_size(-1) 
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

		static iterator find(net::ipv4_address ip, call_id_type call_id)
		{
			iterator i = begin();
			while(i != end() && !(call_id == i-> call_id && ip == i->ip))
				++i;
			return i;
		}

		static void push(const record_type &v)
		{ container.push_back(v); }

		template<typename Treturn>
		static void push(
			net::ipv4_address i,
			command_id_type   cmd,
			call_id_type      cid,
			const void       *a,
			uint16_t          as,
			void (*cb)(
				net::ipv4_address,
				command_id_type,
				Treturn*
			)
		)
		{ container.push_back(record_type(i,cmd,cid,a,as,cb)); }

		static void push(
			net::ipv4_address i,
			command_id_type   cmd,
			call_id_type      cid,
			const void       *a,
			uint16_t          as,
			void (*cb)(
				net::ipv4_address,
				command_id_type,
				const std::string&
			)
		)
		{ container.push_back(record_type(i,cmd,cid,a,as,cb)); }

		static void erase(iterator i)
		{ container.erase(i); }
	};

	template<typename e>
	typename outgoing_call<e>::container_type outgoing_call<e>::container;

	template<typename e>
	std::mutex outgoing_call<e>::mutex;
}}}
#endif
