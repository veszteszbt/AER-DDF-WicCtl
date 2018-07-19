#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "parser/Parser.ih"
#include "journal/journal.h"
#include "functions.h"
#include <sstream>



namespace commandline {

class shell
{

	void init();

public:

	static Parser* parser;
	static wic::functions* fptr;
	static int scanDepth;

	shell();

	shell(const std::string &filename);

	~shell();
	
	template<typename Tret, typename... Targ>
	void add_command(const std::string &name, std::function<Tret(Targ...)> function)
	{
		fptr->add_command(name, function);
		std::cout << "command added!" << std::endl;
	}

	template<typename Tret, typename... Targ>
	void add_command(const std::string &name, Tret(*function)(Targ...))
	{
		fptr->add_command(name, function);
		std::cout << "command added!" << std::endl;
	}

	void execute();

	void execute(std::stringstream& ss);

	void execute(const std::string& filename);
};

}
#endif