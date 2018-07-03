#include "functions.h"

namespace wic{

/*static void delay(const std::vector<std::string> &args){
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(delay));  
	std::cout << "delay" << std::endl;
}*/

static void gamestate(const std::vector<std::string> &args)
{
	
	std::cout << "gamestate" << std::endl;

}

static void write_int(int i)
{
	std::cout << "writing int: " << i << std::endl;
	//active=false;
}

static void write_double(double d)
{
	std::cout << "writing double: " << d << std::endl;
	//active=false;
}

static void write_string(std::string s)
{
	std::cout << "writing string: " << s << std::endl;
	//active=false;
}

static void write_reverse(std::string s)
{
	std::reverse(s.begin(), s.end());
	std::cout << s << std::endl;
	std::reverse(s.begin(), s.end());
}

static void echo_c(std::string s, int i)
{
	//std::cout << "writing " << s << " " << i << "times" << std::endl;
	for (int j=0;j<i;j++)
	{
		std::cout << s;
	}
	//std::cout << std::endl;
}

static void echo_end()
{
	std::cout << std::endl;
}

template<typename T>
static void echo(T t)
{
	std::cout << t << std::endl;
}

template<>
void echo(int i)
{
	std::cout << i << std::endl;
}

template<>
void echo(double d)
{
	std::cout << d << std::endl;
}

template<>
void echo(std::string s)
{
	std::cout << s << std::endl;
}

functions::functions()
{
	//active=true;
	/*alsa_host::init();
	
	process::sql_executor::init();
	
	wicc_earpc::init();
	
	devstat::init();

	gmclient_test::test_room_1::init();
	 ezek a vic hostban még a ciklus előtt vannak*/
	
	
	
	
	//ez var_Value miatt még nem jó
	add_command("writeint",write_int);
	add_command("writedouble",write_double);
	add_command("writestring",write_string);
    add_command("gamestate",gamestate);
	add_command("echo", echo<int>);
	add_command("echo", echo<double>);
	add_command("echo", echo<std::string>);
	add_command("write_reverse", write_reverse);
	add_command("echo_c", echo_c);
	add_command("echo_end", echo_end);
}
	
void functions::run(call* c)
{
	//while(/*active*/true) //végtelenciklus
	//{ 
		//int row = row_number;
		arguments.clear();
		arguments.resize(0);
		std::string command_name;
		//std::getline(std::cin,asd);
		//std::stringstream x(asd);
		command_name = c->name;
		std::vector<expression_desc*> args = c->args;
		//std::string _command;
		//std::string tempstring;
		//x >> _command;
		//if (!x.fail())
		//{
			auto runcommand = commands.find(command_name);
			if (runcommand!=commands.end())
			{
				//while (x >> tempstring)
				for (unsigned int i=0;i<args.size();i++)
				{
					arguments.push_back(args[i]->val);
				}
				runcommand->second(arguments);
			}
			else
			{
				std::cerr << "\e[31;01mERROR:\e[0m Unknown command!" << std::endl;
				journal(journal::info, "functions") << "ERROR: Unknown command!" << journal::end;
		        std::terminate();
				//unknown command
			}
		//}
		//else{
		//		std::cout << "Cannot read command" << std::endl;
				//in.setstate(std::ios::failbit);
		//	}

	//}

	//gmclient_test::test_room_1::init();

}





template<typename V, typename T>
static bool convert(const V &input, T &output)
{
	return false;
}

/*template<>
bool convert(const std::string &input, int &output)
{
	std::stringstream s(input);
	s >> std::noskipws >> output;
	if(s.fail() || !s.eof())
		return false;
	return true;
}*/

template<>
bool convert(const var_value &v, int &output)
{
	if (v.get_type() == u_integer)
	{
		output = v.value<int>();
		return true;
	}
	else
	{
		return false;
	}
}

template<>
bool convert(const var_value &v, double &output)
{
	if (v.get_type() == u_double)
	{
		output = v.value<double>();
		return true;
	}
	else
	{
		return false;
	}
}

template<>
bool convert(const var_value &v, std::string &output)
{
	if (v.get_type() == u_string)
	{
		output = v.value<std::string>();
		return true;
	}
	else
	{
		return false;
	}
}

/*template<>
bool convert(const std::string &input, std::string &output)
{
	output=input;
	return true;
}*/

	 

	

}
