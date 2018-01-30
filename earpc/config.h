namespace earpc {

template<
	typename TcommandId,
	typename TcallId,
	uint16_t tLocalPort,
	uint16_t tRemotePort
>
struct config
{
	typedef TcommandId               cfg_command_id_type;
                                  
	typedef TcallId                  cfg_call_id_type;

	static const cfg_command_id_type cfg_command_id_ack       = -1;

	static const cfg_command_id_type cfg_command_id_nak       = -2;

	static const cfg_command_id_type cfg_command_id_return    = -3;

	static const cfg_command_id_type cfg_command_id_exception = -4;

	static const uint32_t            cfg_call_timeout         = 3200;

	static const uint16_t            cfg_local_port           = tLocalPort;
                                   
	static const uint16_t            cfg_remote_port          = tRemotePort;

	static ::earpc::udp                cfg_connection;
};

template<typename a, typename b, uint16_t lp, uint16_t rp>
::earpc::udp config<a,b,lp,rp>::cfg_connection(lp,rp);

typedef config<uint64_t,uint32_t,1234,1234> default_config;

}
