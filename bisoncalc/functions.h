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



namespace wic{

template<typename V, typename T>
static bool convert(const V &input, T &output);

template<>
bool convert(const var_value &v, int &output);

template<>
bool convert(const var_value &v, double &output);

template<>
bool convert(const var_value &v, std::string &output);

template<>
bool convert(const std::string &input, std::string &output);

class functions
{
    std::vector<var_value> arguments;
    

    template<typename... Targ> 
    class command_wrapper
    {
        typedef std::tuple<std::decay_t<Targ>... > arg_tuple_t;
        
        std::function<void(Targ...)> command;


        template<int index = sizeof...(Targ)>
        std::enable_if_t<!(index <= 0)>
        create_tuple(arg_tuple_t &t, const std::vector<var_value> &args, std::vector<std::string> &errv)
        {
            //std::cout << "indukcio" << std::endl;

            if(!convert(args[index-1],std::get<index-1>(t)))
				errv.push_back(std::to_string(index)+" ("+types::type::name(std::get<index-1>(t))+")");
            create_tuple<index-1>(t,args,errv);
        }

        
        template<int index = sizeof...(Targ)>
        std::enable_if_t<index <= 0>
        create_tuple(arg_tuple_t &t, const std::vector<var_value> &args, std::vector<std::string> &errv)
        {
            //std::cout << "alapeset" << std::endl;
            //if (!convert(args[0],std::get<0>(t)))
            //    errv.push_back(std::to_string(index+1)+" ("+types::type::name(std::get<0>(t))+")");
               
        }
 
    public:
        //int row;
        command_wrapper(std::function<void(Targ...)> c) : command(c){}
        void operator()(const std::vector<var_value> &args)
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
                {
                    std::apply(command,fnargs);
                }
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
    std::map<std::string, std::function<void(const std::vector<var_value> &args)> > commands;
public:
    template<typename... Targ>
    void add_command(const std::string &name, std::function<void(Targ...)> cmd)
    {
        std::cout << "added command" << std::endl;
        commands[name] = command_wrapper<Targ...>(cmd);
    }

    template<typename... Targ>
    void add_command(const std::string &name, void(*cmd)(Targ...))
    {
         std::cout << "added command" << std::endl;
        commands[name] = command_wrapper<Targ...>(cmd);
    }

    void run(call* c);

    functions();



};








}


#endif