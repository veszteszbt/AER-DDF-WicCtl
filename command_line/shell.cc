#include <command_line/shell.hh>

namespace commandline {

Parser* shell::parser;
wic::functions* shell::fptr;
int shell::scanDepth = 0;

void shell::init()
{
	journal(journal::info,"shell") << "program started" << journal::end;
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
	journal(journal::info,"shell") << "program finished" << journal::end;
}

void shell::execute()
{
	journal(journal::info,"shell") << "starting new parse cycle" << journal::end;
	parser->process_this();
}

void shell::execute(std::stringstream& ss)
{
	journal(journal::info,"shell") << "starting new parse cycle" << journal::end;
	parser->process_this(ss);
}

void shell::execute(const std::string& filename)
{
	journal(journal::info,"shell") << "starting new parse cycle" << journal::end;
	parser->process_this(filename);
}

}
