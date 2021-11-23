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
		Tween_shoot = nullptr;
		value = 0;
		initial_Transform = Transform::IDENTITY; //The identity basis, with no rotation or scaling applied.

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
		Tween_shoot = get_node<Tween>("Tween_shoot");

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
			
			
			set_rotation_degrees(Vector3::ZERO);
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

				/*Transform look = get_global_transform().looking_at(bot_to_kill->get_global_transform().origin, Vector3::UP);
				set_rotation_degrees(look.basis.z * delta);*/
				
				//////////////////////
				////obtener el vector hacia el rigidbody
				//Vector3 vector_direction = bot_to_kill->get_global_transform().origin - get_global_transform().origin;

				////obtener el angulo hacia el rigidbody
				//float angle_z = get_global_transform().basis.z.angle_to(vector_direction);//angulo en el eje z hacia el bot
				//float angle_y = get_global_transform().basis.y.angle_to(vector_direction);//angulo en el eje z hacia el bot
				//float r = get_global_transform().basis.z.angle_to( get_rotation() );
				////vector3::slerp(vector3::zero, );
				//
				//////obtener la rotacion de este frame
				//Vector3 angle_delta = get_rotation_degrees();

				//////obtener la rotacion completa hacia el rigidbody
				//angle = godot::Math::lerp_angle(r, angle, 1);

				////clamp para que no se pase la posicion
				//angle = godot::Math::clamp(angle, r - angle_delta, r + angle_delta);

				////cambio la rotacion en el angulo nuevo
				//set_rotation_degrees( angle );

				Transform t = get_transform();
				//Transform t = get_global_transform();//get the global position
				Vector3 lookDir = bot_to_kill->get_transform().origin - t.origin;//get the vector towards that object
				Transform rotTransform = t.looking_at(lookDir, Vector3::UP );
				//Quat thisRotation = Quat(t.basis).slerp( rotTransform.basis, value * 0.1 );//Assuming that the matrix is a proper rotation matrix, slerp performs a spherical-linear interpolation with another rotation matrix.
				Quat thisRotation = Quat(t.basis).slerp( rotTransform.basis, value );//Assuming that the matrix is a proper rotation matrix, slerp performs a spherical-linear interpolation with another rotation matrix.
				value += delta;
				if (value > 1)
				{
					value = 1;
				}
				set_transform( Transform(thisRotation, t.origin) );//set transform with rotation

			}
		}
	}


	void MachineGun::shoot()
	{
		//look_at(look_at_bot, Vector3::UP);//miro al bot
		is_shooting = true;
		float shoot_delay_random = random->randf_range(0.5, 2);
		Timer_shoot->set_wait_time(shoot_delay_random);
		Timer_shoot->start();//para activar shoot
	}

	//disparo cuando termina el delay
	void MachineGun::_on_Timer_shoot_timeout()
	{
		if (gameManager->headTimeFinish)//si la cabeza esta dada vuelta
		{
			//look_at(bot_to_kill->get_transform().origin, Vector3::UP);//miro al bot
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