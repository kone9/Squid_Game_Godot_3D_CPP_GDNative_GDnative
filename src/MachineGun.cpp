#include "MachineGun.h"
#include "BotAI.h"
#include <SceneTree.hpp>
#include <RigidBody.hpp>
#include "BotAI.h"
#include "PlayerMovement.h"
#include <AudioStreamPlayer3D.hpp>

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
		Tween_shoot = nullptr;
		animationPlayer = nullptr;
		value = 0;
		initial_Transform = Transform::IDENTITY; //The identity basis, with no rotation or scaling applied.
		rotation_speed = 6;

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

		register_property<MachineGun, real_t>("rotation_speed", &MachineGun::rotation_speed, 6);
	}

	void MachineGun::_init()
	{
	}

	void MachineGun::_ready()
	{
		Timer_shoot = get_node<Timer>("Timer_shoot");
		Machine_Gun_Sound = get_node<AudioStreamPlayer3D>("Machine_Gun_Sound");
		Tween_shoot = get_node<Tween>("Tween_shoot");
		animationPlayer = get_node<AnimationPlayer>("AnimationPlayer");

		gameManager = (GameManager*)get_tree()->get_nodes_in_group("GameManager")[0];
		random = RandomNumberGenerator::_new();
		random->randomize();

		initial_Transform = get_transform();
	}

	void MachineGun::_process(real_t delta)
	{
		if (!gameManager->headTimeFinish)//si la cabeza no se dio vuelta
		{
			//Transform t = get_transform();
			//Transform t = initial_Transform;//I get the global position
			//Vector3 lookDir = get_transform().origin;//get the vector towards that object
			//Transform rotTransform = t.looking_at(lookDir, Vector3::UP);
			//Quat thisRotation = Quat(t.basis).slerp(rotTransform.basis, value);
			//value += delta;
			//if (value > 1)
			//{
			//	value = 0;
			//}
			//set_transform(Transform(thisRotation, t.origin));

			//set_rotation_degrees(Vector3::ZERO);
		}
		if (gameManager->headTimeFinish)//si la cabeza esta dada vuelta
		{
			if (gameManager->bots_to_remove.size() != 0)//si hay bots para remover
			{
				if (!is_shooting)//sino estoy disparando
				{
					bot_to_kill = (RigidBody*)gameManager->bots_to_remove.pop_back();//guardo el último elemento del arerglo
					shoot();//útilizo su posición para disparar
				}
			}
			if (bot_to_kill != nullptr && gameManager->headTimeFinish)
			{
				//look_at(bot_to_kill->get_transform().origin, Vector3::UP);//miro al bot
				look_at_with_rotate_smooth(delta);
			}
		}
	}

	//look at with smooth using vector looking at movel with quaternions rotation
	void MachineGun::look_at_with_rotate_smooth(real_t delta)
	{
		Transform t = get_global_transform();//get global transform

		Vector3 lookDir = bot_to_kill->get_global_transform().origin - t.origin;//get the vector towards that object

		Transform rotTransform = t.looking_at(t.origin + lookDir, Vector3::UP);//rotation direction with vector  + global position this machine gun

		Quat thisRotation = Quat(t.basis).slerp(rotTransform.basis, delta * rotation_speed);//Assuming that the matrix is a proper rotation matrix, slerp performs a spherical-linear interpolation with another rotation matrix.
		value += delta;
		if (value > 1)
		{
			value = 1;
		}
		set_transform(Transform(thisRotation, t.origin));//set transform with rotation slerp
	}

	void MachineGun::shoot()
	{
		//look_at(look_at_bot, Vector3::UP);//miro al bot
		is_shooting = true;
		
		float shoot_delay_random = random->randf_range(0.2, 0.3);
		Timer_shoot->set_wait_time(shoot_delay_random);
		Timer_shoot->start();//para activar shoot
	}

	void MachineGun::_on_Timer_shoot_timeout()
	{
		if (gameManager->headTimeFinish)//si la cabeza esta dada vuelta
		{
			//look_at(bot_to_kill->get_transform().origin, Vector3::UP);//miro al bot
			Machine_Gun_Sound->play();
			animationPlayer->play("shoot");

			if (cast_to<Node>(bot_to_kill)->is_in_group("Bot"))// is a bot
			{
				if (cast_to<Node>(bot_to_kill)->is_in_group("Bot_banana"))//to warn that the banana bot is dead and all the others can move
				{
					gameManager->the_banana_died = true;
				}

				cast_to<Node>(bot_to_kill)->get_node<AudioStreamPlayer3D>("Sound_Dead")->play();
				bot_to_kill->queue_free();//temporarily delete
			}

			if (cast_to<Node>(bot_to_kill)->is_in_group("Player"))//is a player
			{
				cast_to<Node>(bot_to_kill)->get_node<AudioStreamPlayer3D>("Sound_Dead")->play();
				cast_to<PlayerMovement>(bot_to_kill)->isDying = true;
				//bot_to_kill->queue_free();//temporarily delete
			}

			bot_to_kill = nullptr;
		}
		else//si la cabeza no esta dada vuelta
		{
			if (bot_to_kill != nullptr)
			{
				if (cast_to<Node>(bot_to_kill)->is_in_group("Bot"))// is a bot
				{
					cast_to<BotAI>(bot_to_kill)->is_to_die = false;
				}

				if (cast_to<Node>(bot_to_kill)->is_in_group("Player"))//is a player
				{
					cast_to<PlayerMovement>(bot_to_kill)->isDying = false;
				}
				bot_to_kill = nullptr;
			}
		}
		is_shooting = false;
	}

	

	//disparo cuando termina el delay
	//void MachineGun::_on_Timer_shoot_timeout()
	//{
	//	if (gameManager->headTimeFinish)//si la cabeza esta dada vuelta
	//	{
	//		//look_at(bot_to_kill->get_transform().origin, Vector3::UP);//miro al bot
	//		Machine_Gun_Sound->play();
	//		animationPlayer->play("shoot");
	//		is_shooting = false;

	//		bot_to_kill->queue_free();
	//		bot_to_kill = nullptr;
	//	}
	//	else//si la cabeza no esta dada vuelta
	//	{
	//		is_shooting = false;
	//		bot_to_kill = nullptr;
	//	}
	//}

}