#ifndef ALSA_HOST_H
# define ALSA_HOST_H
# include <iostream>
# include <string>
# include <sstream>
# include <map>
# include <alsa/asoundlib.h>
# include <alsa/control.h>

class alsa_host
{
	class alsa_card_t
	{
		static std::string ll_get_name(int id)
		{
			char *n;
			snd_card_get_name(id,&n);
			if(!n)
				return "";
			return std::string(n);
		}

		static std::string ll_get_longname(int id)
		{
			char *n = 0;
			snd_card_get_longname(id,&n);
			if(!n)
				return "";
			return std::string(n);
		}

		static std::string ll_get_hwid(int id)
		{
			std::stringstream s;
			s << "hw:" << std::dec << id;
			return s.str();
		}

	public:

		const std::string longname;

		const std::string name;

		const std::string hwid;

		const int id;

		alsa_card_t()
			: id(-1)
		{}

		alsa_card_t(int pid)
			: id(pid)
			, name(ll_get_name(pid))
			, longname(ll_get_longname(pid))
			, hwid(ll_get_hwid(pid))
			
		{
			// collect information about sound card
			snd_ctl_t *ctl;

			if(snd_ctl_open(&ctl,hwid.c_str(),0))
			{
				std::cout << "alsa host: error obtaining ctl for sound card #" << id << std::endl;
				return;
			}

			snd_ctl_card_info_t *info;
			snd_ctl_card_info_malloc(&info);

			snd_ctl_card_info(ctl,info);

			//std::cout << "Components: " << snd_ctl_card_info_get_components(info) << std::endl;

			snd_ctl_card_info_free(info);

			std::cout << "alsa host: registered sound card #" << id << " - " << name << " ("<<longname<<")" << std::endl;

		}
	};

	typedef std::map<int,alsa_card_t*> cards_by_id_t;

	static cards_by_id_t cards_by_id;
public:

	static void init()
	{
		int card = -1;
		
		// collect and allocate sound cards
		for(
			snd_card_next(&card);
			card >= 0;
			snd_card_next(&card)
		)
			if(cards_by_id.find(card) != cards_by_id.end())
				std::cout << "alsa host: warning: sound card " << card << " already exists; omitting";

			else
				cards_by_id[card] = new alsa_card_t(card);
	}

	static void uninit()
	{

	}

	static void reg(uint8_t card_id, uint8_t channel_id)
	{

	}

	
};
#endif
