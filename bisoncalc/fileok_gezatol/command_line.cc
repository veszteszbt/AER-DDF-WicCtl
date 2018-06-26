#include "command_line.h"

namespace wic{

command_line::command_line()
{
    //active=true;
    /*alsa_host::init();
    
    process::sql_executor::init();
    
    wicc_earpc::init();
    
    devstat::init();

    gmclient_test::test_room_1::init();
     ezek a vic hostban még a ciklus előtt vannak*/

}
    
void command_line::run()
{
    while(/*active*/true) //végtelenciklus
    { 
        arguments.clear();
        arguments.resize(0);
        std::string asd;
        std::getline(std::cin,asd);
        std::stringstream x(asd);
        std::string _command;
        std::string tempstring;
        x >> _command;
        if (!x.fail())
        {
            auto runcommand = commands.find(_command);
            if (runcommand!=commands.end())
            {
                while (x >> tempstring)
                {
                    arguments.push_back(tempstring);
                }
                runcommand->second(arguments);
            }
            else
            {
                std::cout << "Unknown command!" << std::endl;
                //unknown command
            }
        }
        else{
                std::cout << "Cannot read command" << std::endl;
                //in.setstate(std::ios::failbit);
            }

}

    //gmclient_test::test_room_1::init();

}

static void delay(const std::vector<std::string> &args){
    
    //std::this_thread::sleep_for(std::chrono::milliseconds(delay));  
    std::cout << "delay" << std::endl;
}

static void gamestate(const std::vector<std::string> &args)
{
    
    std::cout << "gamestate" << std::endl;

}

static void exit_program(int i)
{
    std::cout << "exit program with exit code " << i << std::endl;
    //active=false;
}



template<typename T>
static bool convert(const std::string &s, T &output)
{
    return false;
}

template<>
bool convert(const std::string &input, int &output)
{
    std::stringstream s(input);
    s >> std::noskipws >> output;
    if(s.fail() || !s.eof())
        return false;
    return true;
}

template<>
bool convert(const std::string &input, std::string &output)
{
    output=input;
    return true;
}

     

    

}
