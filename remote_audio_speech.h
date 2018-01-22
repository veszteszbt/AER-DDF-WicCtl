#ifndef WIC_REMOTE_AUDIO_SPEECH_H
# define WIC_REMOTE_AUDIO_SPEECH_H
# include <property_config_base.h>
# include <wicp/role.h>
namespace wic {

template<typename TConfig>
class remote_audio_speech
{
	typedef typename property_config_base::cfg_clock clock;

	struct prop_playing_config : public property_config_base
	{
		typedef bool cfg_value_type;
		static const uint32_t cfg_class_id = TConfig::cfg_class_id;
		static const uint32_t cfg_member_id = TConfig::cfg_member_id;
		static const uint32_t cfg_cooldown_time = 0;
		static const bool cfg_commit_change_only = true;
	};
	typedef wicp::remote_property<prop_playing_config> prop_playing;


public:
	static void init(wicp::role_type &role)
	{ prop_playing::init(role); }

	static void uninit()
	{ prop_playing::uninit(); }

	static bool playing()
	{ return prop_playing::value(); }

	static void playing(bool v)
	{ prop_playing::value(v); }

	static void play()
	{ prop_playing(true); }
	
	constexpr static sched::listener  &on_playing_change = prop_playing::on_change;
};

}
#endif
