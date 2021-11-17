#include "MachineGun.h"
#include "BotAI.h"

namespace godot
{
	MachineGun::MachineGun()
	{
		Timer_shoot = nullptr;
		bot_to_kill = nullptr;
		Machine_Gun_Sound = nullptr;
		is_shooting = false;
	}

	MachineGun::~MachineGun()
	{
	}

	void MachineGun::_register_methods()
	{
		register_method("_ready", &MachineGun::_ready);
		register_method("_process", &MachineGun::_process);

		//senials
		register_method("_on_Timer_shoot_timeout", &MachineGun::_on_Timer_shoot_timeout);
	}

	void MachineGun::_init()
	{
	}

	void MachineGun::_ready()
	{
		Timer_shoot = get_node<Timer>("Timer_shoot");
		Machine_Gun_Sound = get_node<AudioStreamPlayer3D>("Machine_Gun_Sound");
	}

	void MachineGun::_process(real_t delta)
	{
	}

	void MachineGun::shoot(Vector3 look_at_bot)
	{
		if (!is_shooting)
		{
			is_shooting = true;
			look_at(look_at_bot, Vector3::UP);//miro al bot
			Timer_shoot->start();//para activar shoot
		}
	}

	//disparo cuando termina el delay
	void MachineGun::_on_Timer_shoot_timeout()
	{
		Machine_Gun_Sound->play();
		is_shooting = false;
	}

}