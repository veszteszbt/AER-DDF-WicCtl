namespace earpc {

template<typename TcommandId, typename TcallId>
struct config
{
	static earpc::udp connection;

	typedef TcommandId command_id_type;

	typedef TcallId call_id_type;

	static const command_id_type command_id_ack       = -1;

	static const command_id_type command_id_nak       = -2;

	static const command_id_type command_id_return    = -3;

	static const command_id_type command_id_exception = -4;
};

template<typename a, typename b>
earpc::udp config<a,b>::connection(1234, 1234);

typedef config<uint64_t,uint32_t> default_config;

}
