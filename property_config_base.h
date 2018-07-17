#ifndef PROPERTY_CONFIG_BASE_H
# define PROPERTY_CONFIG_BASE_H

typedef earpc::default_earpc wicc_earpc;

struct property_config_base
{
	typedef std::chrono::high_resolution_clock    cfg_clock;

	// typedef wicc_earpc cfg_earpc;

	typedef uint32_t cfg_class_id_type;

	typedef uint32_t cfg_member_id_type;

	typedef uint64_t cfg_object_id_type;

	static const bool cfg_commit_change_only = true;

	static const uint32_t cfg_cooldown_time = 0;

	static const bool cfg_replicate_locally = true;

	static const uint32_t cfg_history_size = 16;
};
#endif
