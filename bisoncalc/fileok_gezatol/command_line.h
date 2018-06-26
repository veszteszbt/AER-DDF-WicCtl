#ifndef COMMAND_LINE_H
#define COMMAND_LINE_H

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

namespace wic{

class command_line
{
    std::vector<std::string> arguments;
    template<typename... Targ> 
    class command_wrapper
    {
        typedef std::tuple<std::decay_t<Targ>... > arg_tuple_t;
        
        std::function<void(Targ...)> command;

        template<int index = sizeof...(Targ)-1>
        std::enable_if_t<index>
        create_tuple(arg_tuple_t &t, const std::vector<std::string> &args, std::vector<std::string> &errv)
        {
            if(!convert(args[index],std::get<index>(t)))
                errv.push_back(std::to_string(index+1)+" ("+types::type::name(std::get<index>(t))+")");
            create_tuple<index-1>(t,args);
        }

        
        template<int index = sizeof...(Targ)-1>
        std::enable_if_t<!index>
        create_tuple(arg_tuple_t &t, const std::vector<std::string> &args, std::vector<std::string> &errv)
        {
            if (!convert(args[0],std::get<0>(t)))
                errv.push_back(std::to_string(index+1)+" ("+types::type::name(std::get<0>(t))+")");
        }
 
    public:
        command_wrapper(std::function<void(Targ...)> c) : command(c){}
        void operator()(const std::vector<std::string> &args)
        {
            std::vector<std::string> errorvect;
            errorvect.reserve(sizeof...(Targ));
            if(args.size()!=sizeof...(Targ))
                std::cout << "expected " << sizeof...(Targ) << " arguments, received " << args.size() << std::endl;
            else
            {
                arg_tuple_t fnargs;
                create_tuple(fnargs, args, errorvect);
                int rv = errorvect.size();
                if(rv==0)
                    std::apply(command,fnargs);
                else if (rv==1)
                    std::cout << "argument " << errorvect[0] << " is invalid" << std::endl;
                else
                {
                    std::cout << "arguments " << errorvect[0];
                    for (int i=1;i<rv;i++)
                    {
                        std::cout << ", " << errorvect[i];
                    }
                    std::cout << " are invalid" << std::endl;
                }
            }
        }
    };
    std::map<std::string, std::function<void(const std::vector<std::string> &args)> > commands;
public:
    template<typename... Targ>
    void add_command(const std::string &name, std::function<void(Targ...)> cmd)
    {
        commands[name] = command_wrapper<Targ...>(cmd);
    }

    template<typename... Targ>
    void add_command(const std::string &name, void(*cmd)(Targ...))
    {
        commands[name] = command_wrapper<Targ...>(cmd);
    }

    void run();

    command_line();



};








}


#endif