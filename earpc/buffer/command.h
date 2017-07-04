#ifndef WIC_EARPC_BUFFER_COMMAND_H
# define WIC_EARPC_BUFFER_COMMAND_H
# include <list>
# include <chrono>
# include <mutex>
namespace wic {
namespace earpc {
namespace buffer
{
	template<typename TEnv>
	class command
	{
		typedef typename TEnv::command_id_type  command_id_type;

		typedef typename TEnv::call_id_type     call_id_type;

		typedef typename TEnv::time_point       time_point;

		typedef typename TEnv::clock            clock;

		typedef typename TEnv::call_handle_base call_handle_base;

	public:
		typedef void (*callback_type)(call_handle_base,const void*);

		struct record_type
		{
			command_id_type command_id;

			uint16_t arg_size;

			uint16_t ret_size;

			callback_type callback;

			record_type()
				: callback(0)
			{}

			record_type(
				command_id_type cmd,
				uint16_t as,
				uint16_t rs,
				callback_type c
			)
				: command_id(cmd)
				, arg_size(as)
				, ret_size(rs)
				, callback(c)
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

		static void push(
			command_id_type cmd,
			uint16_t as,
			uint16_t rs,
			callback_type c
		)
		{ container.push_back(record_type(cmd,as,rs,c)); }

		static void erase(iterator i)
		{ container.erase(i); }
	};

	template<typename e>
	typename command<e>::container_type command<e>::container;

	template<typename e>
	std::mutex command<e>::mutex;
}}}
#endif
