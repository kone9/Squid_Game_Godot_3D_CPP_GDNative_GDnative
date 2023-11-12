#include "Doll.h"
#include <RigidBody.hpp>
#include <SceneTree.hpp>
#include "BotAI.h"
#include "PlayerMovement.h"

namespace godot
{
	Doll::Doll()
	{
		gameManager = nullptr;
		speed_rot_raycast_lateral = 100;
		speed_rot_raycast_frontal = 100;
		can_rotate_right = true;
		can_rotate_backward = true;
		direction_speed = 1;
	}

	Doll::~Doll()
	{
	}
	void Doll::_register_methods()
	{
		//de godot
		register_method("_ready", &Doll::_ready);
		register_method("_process", &Doll::_process);
		register_method("_physics_process", &Doll::_physics_process);

		//metodos de clase.
		register_method("rotate_raycast", &Doll::rotate_raycast);
		
		//propiedades
		register_property<Doll, float>("speed_rot_raycast_lateral", &Doll::speed_rot_raycast_lateral, 100);
		register_property<Doll, float>("speed_rot_raycast_frontal", &Doll::speed_rot_raycast_frontal, 100);
		register_property<Doll, int>("direction", &Doll::direction_speed, 1);
	}

	void Doll::_init()
	{
	}

	void Doll::_ready()
	{
		//Godot::print("creada raycast de deteccion");
		gameManager = (GameManager*)get_tree()->get_nodes_in_group("GameManager")[0];
	}

	void Doll::_process(real_t delta)
	{
	}

	void Doll::_physics_process(const real_t delta)
	{
		if (gameManager->headTimeFinish)//si se puede eliminar los jugadores
		{
			force_raycast_update();
			rotate_raycast(delta);//roto el raycast constantemente

			if (is_colliding())//si colisiona el raycast
			{
				RigidBody* bot = cast_to<RigidBody>(get_collider());//obtengo el nodo rigibody colisionado

				if (bot->get_linear_velocity().z != 0 || bot->get_linear_velocity().x != 0)//si su lineal velocity en el eje z es distion de cero
				{
					if ( cast_to<Node>(bot)->is_in_group("Bot") )//if it is a bot 
					{
						if (!cast_to<BotAI>(bot)->is_to_die)//if bot NOT is to day
						{
							cast_to<BotAI>(bot)->is_to_die = true;
							gameManager->bots_to_remove.append(bot);//agrego a la lista de bots a eliminar
						}
					}
					if (cast_to<Node>(bot)->is_in_group("Player"))//if it is a Player 
					{
						if (!cast_to<PlayerMovement>(bot)->isDying)//if player NOT is to dead
						{
							gameManager->bots_to_remove.append(bot);//agrego a la lista de bots a eliminar
							/*Godot::print( String::num_int64( gameManager->bots_to_remove.size() ) );*/
						}
					}

				}

			}

		}
	}

	//para rotar el raycast y detectar enemigos
	void Doll::rotate_raycast(const real_t delta)
	{
		Vector3 rotation_raycast = rotate_lateral(delta, get_rotation_degrees());
		//rotation_raycast.z = rotate_front(delta, rotation_raycast);

		set_rotation_degrees(Vector3(
			rotation_raycast.x,
			rotation_raycast.y,
			rotation_raycast.z
			)
		);
	}

	//para rotar frontal, "EJE X", al final no lo uso pero lo dejo por las dudas
	float Doll::rotate_front(const real_t delta, Vector3 rotation_raycast)
	{
		rotation_raycast.z += speed_rot_raycast_frontal * delta;
		//if (rotation_raycast.y > 90 && can_rotate_right)
		if (rotation_raycast.z < 0 && !can_rotate_backward)
		{
			speed_rot_raycast_frontal *= -1;
			can_rotate_backward = true;
		}
		//if (rotation_raycast.y < -90 && !can_rotate_right)
		if (rotation_raycast.z > 85 && can_rotate_backward)
		{
			speed_rot_raycast_frontal *= -1;
			can_rotate_backward = false;
		}
		return rotation_raycast.z;
	}

	Vector3 Doll::rotate_lateral(const real_t delta, Vector3 rotation_raycast)
	{
		rotation_raycast.y += speed_rot_raycast_lateral * delta;
		if (rotation_raycast.y > 90 && can_rotate_right)
		{
			speed_rot_raycast_lateral *= -1;
			can_rotate_right = false;
			//rotation_raycast.z = rotate_front(delta, rotation_raycast);
		}
		if (rotation_raycast.y < -90 && !can_rotate_right)
		{
			speed_rot_raycast_lateral *= -1;
			can_rotate_right = true;
			//rotation_raycast.z = rotate_front(delta, rotation_raycast);
		}
		return rotation_raycast;
	}
}