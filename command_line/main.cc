#include "shell.hh"
#include <functional>

// template <typename T, typename... Targs>
// void exec(shell &s)
// {
    
// }

// template<typename TConfig, typename... Targs>
// void exec<room_property<TConfig>, Targs...>(shell &s)
// {
//     add_command(std::string(TConfig::name)+"::get", [](){return room_property<TConfig>::value();} );
//     add_command(std::string(TConfig::name)+"::set", [](const typename TConfig::value_type &x){room_property<TConfig>::value(x);} );
//     exec<Targs...>();
// }


// template <>
// void exec<>(shell &s)
// {return;}

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		commandline::shell shell;

		std::stringstream c(
			"x = 5;"
			"writeint(x);"
			"exit(1);"
		);
		shell.execute(c);

		std::function<void()> f = [](){ std::cout << "Hello world!" << std::endl; };
		shell.add_command(
			std::string("print_hello"),
			f
		);
		shell.execute();
	}
	else
	{
		std::string filename = argv[1];
		commandline::shell shell(filename);
	}
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
