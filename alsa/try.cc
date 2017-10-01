#include <iostream>
#include <sstream>
#include "alsa_pcm.h"

int main()
{
	std::stringstream s1,s2;

	short x = 0;
	for(int i = 0; i < 44100; ++i)
	{
		s1.write(reinterpret_cast<char*>(&x),2);
		x+=800;
	}

	x = 0;
	for(int i = 0; i < 44100; ++i)
	{
		s2.write(reinterpret_cast<char*>(&x),2);
		x+=1600;
	}
	std::string sd1 = s1.str(), sd2 = s2.str();
			
	alsa::player p(0);

	while(true)
	{
		std::string x;
		std::cin >> x;
		std::cout << "\e[32;01m" << x << "\e[0m" << std::endl;
		if(x == "a")
		{
			s1.clear();
			s1.str(sd1);
			p.play(s1,0);
		}
		else if(x=="b")
		{
			s2.clear();
			s2.str(sd1);
			p.play(s2,1);
		}
	}
	return 0;
}
