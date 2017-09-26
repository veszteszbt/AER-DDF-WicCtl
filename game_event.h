#ifndef GAME_EVENT_H
# define GAME_EVENT_H

class game_event
{
	const uint32_t site;
	const uint32_t room;
	const uint32_t event;
public:
	game_event(uint32_t psite, uint32_t proom, uint32_t pevent)
		: site(psite)
		, room(proom)
		, event(pevent)
	{}

	void propagate()
	{
//		std::cout << "\e[36;01mEvent " << site << '.' << room << '.' << event << "\e[0m" << std::endl	;
	}
};
#endif
