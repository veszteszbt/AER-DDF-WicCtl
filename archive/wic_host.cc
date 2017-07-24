#include <iostream>
#include <thread>
#include <mutex>
#include <list>
#include <condition_variable>
#include <cstdint>
#include <earpc/udp.h>
#include <earpc/earpc.h>
#include <net/algorithm.h>
#include <string>

struct wicc_earpc_config
{
	static earpc::udp connection;

	typedef uint64_t command_id_type;

	typedef uint32_t call_id_type;

	static const command_id_type command_id_ack = -1;

	static const command_id_type command_id_nak = -2;

	static const command_id_type command_id_return = -3;

	static const command_id_type command_id_exception = -4;
};
typedef earpc::earpc<wicc_earpc_config> wicc_earpc;

earpc::udp wicc_earpc_config::connection(1234, 1234);

namespace pirate {
namespace map {

	static void magnet1_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mMap Magnet Sensor 1: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void magnet2_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mMap Magnet Sensor 2: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
}

namespace stone_chest {
	
	static void stone1_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mStone 1: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void stone2_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mStone 2: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
	static void stone3_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mStone 3: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
	static void stone4_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mStone 4: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
	static void chest_opening_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *door_state
	)
	{
		std::cout << "\e[37;01mChest: " << ((*door_state)?"open":"closed") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
}

namespace cashier_laser{

	struct key_event
	{
		bool    press;
		uint8_t key;
	};
	static void pin_pad_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const key_event *k
	)
	{
		if(!k)
		{
			call_handle.respond(0);
			return;
		}
		std::cout << "\e[37;01pinpad key " << (int)k->key << (k->press?"pressed":"released") << "\e[0m" << std::endl;

		call_handle.respond(1);
	}

	static void fake_cable_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mcable: " << ((*cable_state)?"connected":"disconnected") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

}

namespace rex_flipper {
	
	static void irsensor1_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mIR sensor 1: " << std::dec << *cable_state << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void irsensor2_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mIR sensor 2: " << std::dec << *cable_state << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void irsensor3_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mIR sensor 3: " << std::dec << *cable_state << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void irsensor4_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mIR sensor 4: " << std::dec << *cable_state << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void irsensor5_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mIR sensor 5: " << std::dec << *cable_state << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void rfid_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const uint64_t *cable_state
	)
	{
		std::cout << "\e[37;01mRFID: " << std::hex << *cable_state << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
}

namespace ghostbox {
	static void ghostbox_switch_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mGhost Box Switch: " << std::hex << (*cable_state?"on":"off") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void hanger_switch_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mHanger Switch: " << std::hex << (*cable_state?"on":"off") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void laser_sensor_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mLaser Sensor: " << std::hex << (*cable_state?"on":"off") << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

	static void knock_sensor_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const bool *cable_state
	)
	{
		std::cout << "\e[37;01mKnock Sensor: " << std::dec << (*cable_state) << "\e[0m" << std::endl;
		call_handle.respond(1);
	}

}

namespace wheel {
	static void wheel_notify(
		wicc_earpc::call_handle<uint8_t> call_handle,
		const uint16_t *cable_state
	)
	{
		std::cout << "\e[37;01mWheel: " << std::dec << (*cable_state) << "\e[0m" << std::endl;
		call_handle.respond(1);
	}
}


}


namespace villa
{
	namespace control_room
	{

		struct switch1_config : public property_config_base
		{
			typedef bool cfg_value_type;

			static const bool cfg_commit_change_only = true;

			static const uint32_t cfg_class_id = 0x300030;

			static const uint32_t cfg_member_id = 0x10;

			static const uint32_t cfg_cooldown_time = 50;

		};
		typedef wicp::remote_property<switch1_config> switch1;
	
		static void switch1_notify(
			wicc_earpc::call_handle<uint8_t> call_handle,
			const uint8_t *cable_state
		)
		{
			std::cout << "\e[37;01mSwitch 1: " << std::dec << ((int)*cable_state) << "\e[0m" << std::endl;
			call_handle.respond(1);
		}

		static void switch2_notify(
			wicc_earpc::call_handle<uint8_t> call_handle,
			const uint8_t *cable_state
		)
		{
			std::cout << "\e[37;01mSwitch 2: " << std::dec << ((int)*cable_state) << "\e[0m" << std::endl;
			call_handle.respond(1);
		}
		static void switch3_notify(
			wicc_earpc::call_handle<uint8_t> call_handle,
			const uint8_t *cable_state
		)
		{
			std::cout << "\e[37;01mSwitch 3: " << std::dec << ((int)*cable_state) << "\e[0m" << std::endl;
			call_handle.respond(1);
		}
		static void switch4_notify(
			wicc_earpc::call_handle<uint8_t> call_handle,
			const uint8_t *cable_state
		)
		{
			std::cout << "\e[37;01mSwitch 4: " << std::dec << ((int)*cable_state) << "\e[0m" << std::endl;
			call_handle.respond(1);
		}
		static void switch5_notify(
			wicc_earpc::call_handle<uint8_t> call_handle,
			const uint8_t *cable_state
		)
		{
			std::cout << "\e[37;01mSwitch 5: " << std::dec << ((int)*cable_state) << "\e[0m" << std::endl;
			call_handle.respond(1);
		}
		static void eject_notify(
			wicc_earpc::call_handle<uint8_t> call_handle,
			const bool *cable_state
		)
		{
			std::cout << "\e[37;01mEject: " << std::dec << ((int)*cable_state) << "\e[0m" << std::endl;
			call_handle.respond(1);
		}
	}

}
void call_finish(net::ipv4_address ip,wicc_earpc::command_id_type,const bool *v)
{
	std::cout << "call to " << std::dec
		<< (int)(ip.octet[0]) <<'.'
		<< (int)(ip.octet[1]) <<'.'
		<< (int)(ip.octet[2]) <<'.'
		<< (int)(ip.octet[3])
	
	<< " finished with " << ((v&&*v)?"success":"failure") << std::endl;
}

void serial_get(net::ipv4_address,wicc_earpc::command_id_type,const uint64_t *v)
{
	if(v)
		std::cout << "\e[37mDevice #16 serial: " << std::hex << (*v) << "\e[0m" << std::endl;
}

void time_get(net::ipv4_address,wicc_earpc::command_id_type,const uint64_t *v)
{
	if(v)
		std::cout << "\e[37mDevice #16 clock: " << std::dec << (*v) << "\e[0m" << std::endl;
}

void cpu_get(net::ipv4_address,wicc_earpc::command_id_type,const uint16_t *v)
{
	if(v)
		std::cout << "\e[37mDevice #16 cpu usage: " << std::dec << ((float)(*v))/655.35 << "%\e[0m" << std::endl;
}

int main()
{
	// Pirate - Map Controller - Magnet Sensor 1
	wicc_earpc::set_command(0x10001000000083,pirate::map::magnet1_notify);

	// Pirate - Map Controller - Magnet Sensor 2
	wicc_earpc::set_command(0x10001000000103,pirate::map::magnet2_notify);

	// Pirate - Stone Chest Controller - Stone 1
	wicc_earpc::set_command(0x10002000000083,pirate::stone_chest::stone1_notify);

	// Pirate - Stone Chest Controller - Stone 2
	wicc_earpc::set_command(0x10002000000103,pirate::stone_chest::stone2_notify);

	// Pirate - Stone Chest Controller - Stone 3
	wicc_earpc::set_command(0x10002000000183,pirate::stone_chest::stone3_notify);

	// Pirate - Stone Chest Controller - Stone 4
	wicc_earpc::set_command(0x10002000000203,pirate::stone_chest::stone4_notify);

	// Pirate - Stone Chest Controller - Chest Opening
	wicc_earpc::set_command(0x10002000000283,pirate::stone_chest::chest_opening_notify);

	// Pirate - Cashier Laser Controller - Pin Pad
	wicc_earpc::set_command(0x10003000000183,pirate::cashier_laser::pin_pad_notify);

	// Pirate - Cashier Laser Controller - Fake Cable 
	wicc_earpc::set_command(0x10003000000303,pirate::cashier_laser::fake_cable_notify);


	// Pirate - Rex Flipper Controller - IR Sensor 1
	wicc_earpc::set_command(0x10004000000103,pirate::rex_flipper::irsensor1_notify);

	// Pirate - Rex Flipper Controller - IR Sensor 2
	wicc_earpc::set_command(0x10004000000203,pirate::rex_flipper::irsensor2_notify);

	// Pirate - Rex Flipper Controller - IR Sensor 3
	wicc_earpc::set_command(0x10004000000303,pirate::rex_flipper::irsensor3_notify);

	// Pirate - Rex Flipper Controller - IR Sensor 4
	wicc_earpc::set_command(0x10004000000403,pirate::rex_flipper::irsensor4_notify);

	// Pirate - Rex Flipper Controller - IR Sensor 5
	wicc_earpc::set_command(0x10004000000503,pirate::rex_flipper::irsensor5_notify);

	// Pirate - Rex Flipper Controller - RFID 
	wicc_earpc::set_command(0x10004000000583,pirate::rex_flipper::rfid_notify);

	// Pirate - Ghostbox Controller - Ghost Box Switch
	wicc_earpc::set_command(0x10005000000203,pirate::ghostbox::ghostbox_switch_notify);

	// Pirate - Ghostbox Controller - Hanger Switch 
	wicc_earpc::set_command(0x10005000000283,pirate::ghostbox::hanger_switch_notify);

	// Pirate - Ghostbox Controller - Laser Sensor
	wicc_earpc::set_command(0x10005000000303,pirate::ghostbox::laser_sensor_notify);

	// Pirate - Ghostbox Controller - Knock Sensor
	wicc_earpc::set_command(0x10005000000383,pirate::ghostbox::knock_sensor_notify);

	// Pirate - Wheel Controller - Wheel
	wicc_earpc::set_command(0x10006000000083,pirate::wheel::wheel_notify);
	
	// Villa - Control Room Controller - Switch1
	//wicc_earpc::set_command(0x30003000000083,villa::control_room::switch1_notify);

	// Villa - Control Room Controller - Switch2
	wicc_earpc::set_command(0x30003000000103,villa::control_room::switch2_notify);

	// Villa - Control Room Controller - Switch3
	wicc_earpc::set_command(0x30003000000183,villa::control_room::switch3_notify);

	// Villa - Control Room Controller - Switch4
	wicc_earpc::set_command(0x30003000000203,villa::control_room::switch4_notify);

	// Villa - Control Room Controller - Switch5
	wicc_earpc::set_command(0x30003000000283,villa::control_room::switch5_notify);

	// Villa - Control Room Controller - Eject
	wicc_earpc::set_command(0x30003000000383,villa::control_room::eject_notify);

	int c;
	while(std::cin)
	{
		std::string x;
		std::getline(std::cin,x);

		char buffer[32];
		int i = 0;
		for(; i < x.size();++i)
			buffer[i] = x[i];
		for(;i<32;++i)
			buffer[i]=32;


		wicc_earpc::call<bool,const char[32]>(
			net::ipv4_address(192,168,100,3),
			0x10003000000102,
			buffer,
			call_finish
		);

		wicc_earpc::call<bool,bool>(
			net::ipv4_address(192,168,100,3),
			0x10003000000282,
			(c++)&1,
			call_finish
		);

/*		wicc_earpc::call<bool,uint16_t>(
			net::ipv4_address(192,168,100,5),
			0x10005000000402,
			((((uint32_t)c)&0xff)*0x1000)&0xffff,
			call_finish
		);
*/
		wicc_earpc::call<uint64_t,bool>(
			net::ipv4_address(192,168,100,16),
			0xffffffff00001001,
			1,
			serial_get
		);

		wicc_earpc::call<uint64_t,bool>(
			net::ipv4_address(192,168,100,16),
			0xffffffff00001002,
			1,
			time_get
		);

		wicc_earpc::call<uint16_t,bool>(
			net::ipv4_address(192,168,100,16),
			0xffffffff00001006,
			1,
			cpu_get
		);

	}

	t.join();
	return 0;
}

