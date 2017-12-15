#ifndef EARPC_BUFFER_OUTGOING_CALL_RECORD_H
# define EARPC_BUFFER_OUTGOING_CALL_RECORD_H

namespace wic {
namespace earpc {
namespace buffer {

template<typename TEnv>
struct outgoing_call_record
{
	typedef typename TEnv::call_id_type    call_id_type;
	typedef typename TEnv::command_id_type command_id_type;
	typedef typename TEnv::time_point      time_point;
	typedef typename TEnv::clock           clock;

	typedef void (*callback_type)(
		net::ipv4_address,
		command_id_type,
		const void*
	);

	static const uint32_t call_timeout =    TEnv::call_timeout;

	net::ipv4_address ip;

	call_id_type      call_id;

	command_id_type   command_id;

	callback_type     callback;

	void             *arg; 

	uint16_t          arg_size;
		
	uint16_t          return_size;

	time_point        expiry;
	
	outgoing_call_record()
		: arg(0)
		, arg_size(0)
	{}

	outgoing_call_record(const outgoing_call_record &t)
		: ip(t.ip)
		, call_id(t.call_id)
		, command_id(t.command_id)
		, callback(t.callback)
		, arg_size(t.arg_size)
		, return_size(t.return_size)
		, expiry(t.expiry)
	{
		if (this == &t)
			return;
		arg = malloc(arg_size);
		memcpy(arg, t.arg, arg_size);
	}

	outgoing_call_record &operator=(const outgoing_call_record &t)
	{
		if (this == &t)
			return *this;
		ip = t.ip;
		call_id = t.call_id;
		command_id = t.command_id;
		callback = t.callback;
		arg_size = t.arg_size;
		return_size = t.return_size;
		expiry = t.expiry;
		if (arg)
			free(arg);

		arg = malloc(arg_size);
		memcpy(arg, t.arg, arg_size);
		return *this;
	}

	
	outgoing_call_record(
		net::ipv4_address i,
		command_id_type cmd,
		call_id_type cid,
		const void *a,
		uint16_t as,
		uint16_t rs,
		callback_type cb
	)       
		: ip(i)
		, call_id(cid)
		, command_id(cmd)
		, callback(cb)
		, arg(malloc(as))
		, arg_size(as)
		, return_size(rs)
		, expiry(clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(call_timeout)))
	{
		memcpy(arg,a,as);
	}

	~outgoing_call_record()
	{
		if(arg)
			free(arg);
	}


	void reset_expiry()
	{ expiry = clock::now()+std::chrono::milliseconds(static_cast<uint32_t>(call_timeout)); }
};

}}}
#endif
