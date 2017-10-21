#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <audio.h>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>
#include <wicp/local_property.h>
#include <wicp/remote_property.h>
#include <string>
#include <device_state.h>
#include <game_event.h>
#include <timer.h>
#include <process/sql_executor.h>
#include <property_config_base.h>

#include <peripheral/gpio_output.h>
#include <peripheral/pin_pad.h>


earpc::udp wicc_earpc_config::connection(1234, 1234);

typedef typename wicc_earpc::template call_handle<std::string> asd_handle_type;

void asd(asd_handle_type a,
    const std::string& b
)
{
	a.respond("response to " + b);
}

void visszater(net::ipv4_address,wicc_earpc::command_id_type,const std::string& xx){
    if(&xx)
	std::cout << "received " << xx << std::endl;
    else
        std::cout << "(error)" << std::endl;
}

int main()
{
    wicc_earpc::init();
    wicc_earpc::set_command(14, asd);

    std::string x;
    while(true)
    {
        std::cin >> x;

    wicc_earpc::call(
        net::ipv4_address(192,168,1,46),
        14,
        std::string("hello string from 55"),
        visszater
    );
    }
    return 0;
}
