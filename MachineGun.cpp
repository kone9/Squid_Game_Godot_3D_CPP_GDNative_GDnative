#include "MachineGun.h"
#include "BotAI.h"
#include <SceneTree.hpp>
#include <RigidBody.hpp>


namespace godot
{
	MachineGun::MachineGun()
	{
		Timer_shoot = nullptr;
		bot_to_kill = nullptr;
		Machine_Gun_Sound = nullptr;
		is_shooting = false;
		gameManager = nullptr;
		random = nullptr;
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
		gameManager = (GameManager*)get_tree()->get_nodes_in_group("GameManager")[0];
		random = RandomNumberGenerator::_new();
		random->randomize();
	}

	void MachineGun::_process(real_t delta)
	{
		if (gameManager->headTimeFinish)//si la cabeza esta dada vuelta
		{
			if (gameManager->bots_to_remove.size() != 0)//si hay bots para remover
			{
				if (!is_shooting)//sino estoy disparando
				{
					bot_to_kill = (RigidBody*)gameManager->bots_to_remove.pop_back();//guardo el último elemento del arerglo
					shoot(bot_to_kill->get_transform().origin);//útilizo su posición para disparar
				}
			}
		}
	}

	void MachineGun::shoot(Vector3 look_at_bot)
	{
		is_shooting = true;
		//look_at(look_at_bot, Vector3::UP);//miro al bot
		float shoot_delay_random = random->randf_range(0.5, 2);
		Timer_shoot->set_wait_time(shoot_delay_random);
		Timer_shoot->start();//para activar shoot
	}

	//disparo cuando termina el delay
	void MachineGun::_on_Timer_shoot_timeout()
	{
		if (gameManager->headTimeFinish)//si la cabeza esta dada vuelta
		{
			look_at(bot_to_kill->get_transform().origin, Vector3::UP);//miro al bot
			Machine_Gun_Sound->play();
			is_shooting = false;

			bot_to_kill->queue_free();
			bot_to_kill = nullptr;
		}
		else
		{
			is_shooting = false;
			bot_to_kill = nullptr;
		}
	}

}