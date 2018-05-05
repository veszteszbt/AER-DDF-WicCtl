#include "parser/Parser.ih"
#include "journal/journal.h"

Parser* parser;

int main(int argc, char* argv[])
{
	journal::init("test/journal.txt");
	journal(journal::info,"main") << "program started" << journal::end;
	if (argc < 2)
	{
		parser = new Parser;
		(*parser).parse();
	}
	else
	{
		std::string filename = argv[1];
		parser = new Parser(filename);
		(*parser).parse();
	}
	delete parser;
	journal(journal::info,"main") << "program finished" << journal::end;
	journal::uninit();
	return 0;
}



/*using namespace std;



void input_handler( ifstream& in, int argc, char* argv[] );

int main( int argc, char* argv[] )
{
	ifstream in;
	input_handler( in, argc, argv );
	yyFlexLexer fl(&in, &cout);
	fl.yylex();
	return 0;
}

void input_handler( ifstream& in, int argc, char* argv[] )
{
	if( argc < 2 )
	{   
		cerr << "Please specify a file to parse." << endl;
		exit(1);
	}
	in.open( argv[1] );
	if( !in )
	{
		cerr << "File " << argv[1] << "could not be opened." << endl;
		exit(1);
	}
}
*/
