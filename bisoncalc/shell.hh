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
	
	void execute();

	void execute(std::stringstream& ss);

	void execute(const std::string& filename);
};

}
#endif