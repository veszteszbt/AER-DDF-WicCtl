#include <shell.hh>

namespace commandline {

Parser* shell::parser;
wic::functions* shell::fptr;
int shell::scanDepth = 0;

void shell::init()
{
	journal::init("journal/journal.txt");
	journal(journal::info,"main") << "program started" << journal::end;
	scanDepth = 0;
}

shell::shell()
{
	init();

	std::stringstream s("");
	parser = new Parser(s);
	fptr = new wic::functions;
}

shell::shell(const std::string &filename)
{
	init();

	execute(filename);
}

shell::~shell()
{
	delete parser;
	delete fptr;
	journal(journal::info,"main") << "program finished" << journal::end;
	journal::uninit();
}

void shell::execute()
{
	parser->process_this();
}

void shell::execute(std::stringstream& ss)
{
	parser->process_this(ss);
}

void shell::execute(const std::string& filename)
{
	parser->process_this(filename);
}

}