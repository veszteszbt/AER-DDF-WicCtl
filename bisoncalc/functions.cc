#include "functions.h"
#include "parser/Parser.ih"

extern Parser* parser;

namespace wic{

/*static void delay(const std::vector<std::string> &args){
	
	//std::this_thread::sleep_for(std::chrono::milliseconds(delay));  
	std::cout << "delay" << std::endl;
}*/

/*static void gamestate(const std::vector<std::string> &args)
{
	
	std::cout << "gamestate" << std::endl;

}*/

void functions::add_variable(std::string name, var_value value)
{
	(*parser).symbol_table.set_default_value(name, value);
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

static void write_array(std::map<std::string, var_value> m)
{
	for(auto it = m.begin(); it!=m.end();it++)
	{
		std::cout << "writing array: {key:" << it->first << ", value:" << it->second << "}" << std::endl;
	}
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

static void is_true(int b)
{
	if(b)
	{
		std::cout << "TRUE" << std::endl;
	}
	else
	{
		std::cout << "FALSE" << std::endl;
	}
}

/*static double sinus(double x)
{
	return sin(x);
}*/

static void exit(int i)
{
	std::cout << "exiting program with code " << i << std::endl;
	(*parser).finish(i);
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
	add_command("writearray", write_array);
    //add_command("gamestate",gamestate);
	add_command("echo", echo<int>);
	add_command("echo", echo<double>);
	add_command("echo", echo<std::string>);
	add_command("write_reverse", write_reverse);
	add_command("echo_c", echo_c);
	add_command("echo_end", echo_end);
	add_command("sin", sin);
	add_command("is_true", is_true);
	add_command("exit",exit);
	add_variable("asd", 36);
}
	
var_value functions::run(call* c)
{
	var_value v = 0;
	arguments.clear();
	arguments.resize(0);
	std::string command_name;
	command_name = c->name;
	std::vector<expression_desc*> args = c->args;
	auto runcommand = commands.find(command_name);
	if (runcommand!=commands.end())
	{
		for (unsigned int i=0;i<args.size();i++)
		{
			arguments.push_back(args[i]->val);
		}

		//template<class T>
		//typename std::result_of<T(void)>
		//v lehet void is!! 
		//v = std::result_of<runcommand->second(arguments)>;
		v = runcommand->second(arguments);
	}
	else
	{
		std::cerr << "\e[31;01mERROR:\e[0m Unknown command!" << std::endl;
		journal(journal::info, "functions") << "ERROR: Unknown command!" << journal::end;
		std::terminate();
		//unknown command
	}

	//itt v lehet void is, ne ezeket compareld!
	/*if (std::is_same<decltype(std::result_of<runcommand->second()>) ,int>)
	{

	}
	else if(std::is_same<v, double>)
	{

	}
	else if(std::is_same<v, std::string>)
	{

	}*/
	return v;
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

/*template<>
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
}*/

/*template<>
bool convert(const std::string &input, std::string &output)
{
	output=input;
	return true;
}*/

	 

	

}
