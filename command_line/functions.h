#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>
#include <utility>
#include <tuple>
#include <typeinfo>
#include "types/type.h"
#include "parser/semantics.h"
#include <algorithm>
#include <iterator>
#include <type_traits>

namespace wic{

/*template<typename V, typename T>
static bool convert(const V &input, T &output);

template<>
bool convert(const var_value &v, int &output);

template<>
bool convert(const var_value &v, double &output);

template<>
bool convert(const var_value &v, std::string &output);

template<>
bool convert(const std::string &input, std::string &output);*/

class functions
{
	template<typename Tret, typename... Targ>
	class command_wrapper
	{
		typedef std::tuple<std::decay_t<Targ>... > arg_tuple_t;
		
		std::function<Tret(Targ...)> command;

		template<int index = sizeof...(Targ)>
		std::enable_if_t< ! (index <= 0)>
		create_tuple(arg_tuple_t &t, const std::vector<var_value> &args, std::vector<std::string> &errv)
		{
			//std::cout << "indukcio" << std::endl;

			if(!(args[index-1].value(std::get< index-1 >(t))))
				errv.push_back(
					std::to_string(index) +
					" (" + types::type::name(std::get< index-1 >(t)) + ")"
				);

			create_tuple<index-1>(t,args,errv);
		}

		
		template<int index = sizeof...(Targ)>
		std::enable_if_t<index <= 0>
		create_tuple(arg_tuple_t &t, const std::vector<var_value> &args, std::vector<std::string> &errv)
		{ /*std::cout << "alapeset" << std::endl; */ }

		template<typename Tr = Tret>
		std::enable_if_t<std::is_same_v<Tr,void>,var_value>
		execute(arg_tuple_t &a)
		{
			std::apply(command,a);
			return var_value(0);
		}

		template<typename Tr = Tret>
		std::enable_if_t<!std::is_same_v<Tr,void>,var_value>
		execute(arg_tuple_t &a)
		{ return var_value(std::apply(command,a)); }
 
	public:
		//int row;
		command_wrapper(std::function<Tret(Targ...)> c) : command(c){}
		var_value operator()(const std::vector<var_value> &args)
		{
			std::vector<std::string> errorvect;
			errorvect.reserve(sizeof...(Targ));
			if(args.size()!=sizeof...(Targ))
			{
				std::cerr << "\e[31;01mERROR:\e[0m expected " << sizeof...(Targ) << " arguments, received " << args.size() << std::endl;
				journal(journal::info, "functions") << "expected " << sizeof...(Targ) << " arguments, received " << args.size() << journal::end;
				std::terminate();
			}
			else
			{
				arg_tuple_t fnargs;
				create_tuple(fnargs, args, errorvect);
				int rv = errorvect.size();
				if(rv==0)
					return execute(fnargs);

				else if (rv==1)
				{
					std::cerr << "\e[31;01mERROR:\e[0m argument " << errorvect[0] << " is invalid" << std::endl;
					journal(journal::info, "functions") << "argument " << errorvect[0] << " is invalid" << journal::end;
					std::terminate();
				}
				else
				{
					std::cerr << "\e[31;01mERROR:\e[0m arguments " << errorvect[rv-1];
					journal(journal::info, "functions") << "arguments " << errorvect[rv-1];
					for (int i=rv-2;i>=0;i--)
					{
						std::cerr << ", " << errorvect[i];
						journal(journal::info, "functions") << ", " << errorvect[i];
					}
					std::cerr << " are invalid" << std::endl;
					journal(journal::info, "functions") << " are invalid" << journal::end;
					std::terminate();
				}
			}
		}
	};

	std::vector<var_value> arguments;

	std::map<std::string, std::function<var_value(const std::vector<var_value> &args)> > commands;

public:
	template<typename Tret, typename... Targ>
	void add_command(const std::string &name, std::function<Tret(Targ...)> cmd)
	{ commands[name] = command_wrapper<Tret,Targ...>(cmd); }

	template<typename Tret, typename... Targ>
	void add_command(const std::string &name, Tret(*cmd)(Targ...))
	{ commands[name] = command_wrapper<Tret,Targ...>(cmd); }

	void add_variable(std::string name, var_value value);

	var_value run(call* c);

	functions();
};
}

#endif