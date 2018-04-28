#include "parser/Parser.ih"

Parser parser;

int main()
{
	parser.parse();
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