#ifndef WIC_EARPC_BUFFER_PARKING_CALL_H
# define WIC_EARPC_BUFFER_PARKING_CALL_H
# include <earpc/buffer/outgoing_call_record.h>
# include <map>
# include <list>
namespace wic {
namespace earpc {
namespace buffer {

template<typename TEnv>
struct parking_call
{
	typedef typename TEnv::command_id_type  command_id_type;

	typedef typename TEnv::call_id_type     call_id_type;

	typedef outgoing_call_record<TEnv> record_type;

	typedef typename record_type::callback_type callback_type;

	typedef typename std::map<net::ipv4_address,std::list<record_type>> container_type;
private:
	static container_type container;

	static std::mutex mutex;
public:

	static void lock()
	{ mutex.lock(); }

	static void unlock()
	{ mutex.unlock(); }

	static void push(const record_type &r)
	{ container[r.ip].push_back(r);	}

	static void push(
		net::ipv4_address i,
		command_id_type   cmd,
		call_id_type      cid,
		const void       *a,
		uint16_t          as,
		uint16_t          rs,
		callback_type     cb
	)
	{ container[i].push_back(record_type(i,cmd,cid,a,as,rs,cb)); }

	static bool pop(net::ipv4_address ip, record_type &out)
	{
		auto host = container.find(ip);
		if(host == container.end())
			return false;

		std::list<record_type> &calls = host->second;
		if(!calls.size())
			return false;

		out = calls.front();
		calls.pop_front();
		out.reset_expiry();
		return true;
	}

};

template<typename e>
typename parking_call<e>::container_type parking_call<e>::container;

template<typename e>
std::mutex parking_call<e>::mutex;

}}}
#endif
