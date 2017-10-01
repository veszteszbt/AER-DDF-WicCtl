#include <iostream>
#include <sstream>
#include "alsa_pcm.h"

int main()
{
	std::stringstream s;

	short x = 0;
	for(int i = 0; i < 1048576; ++i)
	{
		s.write(reinterpret_cast<char*>(&x),2);
		x+=100;
	}

			
	alsa::player p1(0,0,s);
	alsa::player p2(0,0,s);
/*	alsa::player p3(0,0,s);
	alsa::player p4(0,0,s);
	alsa::player p5(0,0,s);
	alsa::player p6(0,0,s);
	alsa::player p7(0,0,s);
*/		
	while(true);
	return 0;
}
