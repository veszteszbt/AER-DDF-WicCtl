#ifndef PROPERTY_CONFIG_BASE_H
# define PROPERTY_CONFIG_BASE_H

struct wicc_earpc_config
{
	static earpc::udp connection;

	typedef uint64_t command_id_type;

	typedef uint32_t call_id_type;

	static const command_id_type command_id_ack = -1;

	static const command_id_type command_id_nak = -2;

	static const command_id_type command_id_return = -3;

	static const command_id_type command_id_exception = -4;
};
typedef earpc::earpc<wicc_earpc_config> wicc_earpc;

struct property_config_base
{
	typedef std::chrono::high_resolution_clock    cfg_clock;

	typedef wicc_earpc cfg_earpc;

	typedef uint32_t cfg_class_id_type;

	typedef uint32_t cfg_member_id_type;
};
#endif
