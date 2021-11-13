#include "Doll.h"
#include <RigidBody.hpp>
#include <SceneTree.hpp>

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
		Godot::print("creada raycast de deteccion");
		gameManager = (GameManager*)get_tree()->get_nodes_in_group("GameManager")[0];
	}

	void Doll::_process(real_t delta)
	{
	}

	void Doll::_physics_process(const real_t delta)
	{
		//force_raycast_update();
		rotate_raycast(delta);//roto el raycast constantemente
		if (gameManager->headTimeFinish)//si termino el tiempo cuando se pueden mover
		{
			
			if (is_colliding())//si colisiona el raycast
			{
				RigidBody* bot = cast_to<RigidBody>(get_collider());//obtengo el nodo rigibody colisionado
				if (bot->get_linear_velocity().z != 0 || bot->get_linear_velocity().x != 0)//si su lineal velocity en el eje z es distion de cero
				{
					Godot::print(bot->get_name());//imprimo el nombre
					Godot::print(String::num_real( bot->get_linear_velocity().z) );//imprimo el nombre
					bot->queue_free();//lo elimino
				}
			}

		}
	}


	//para rotar el raycast y detectar enemigos
	void Doll::rotate_raycast(const real_t delta)
	{
		Vector3 rotation_raycast = get_rotation_degrees();
		//rotation_raycast.y = rotate_lateral(delta, rotation_raycast);
		rotation_raycast.z = rotate_front(delta, rotation_raycast);

		set_rotation_degrees(Vector3(
			rotation_raycast.x,
			rotation_raycast.y,
			rotation_raycast.z
			)
		);
	}

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

	float Doll::rotate_lateral(const real_t delta, Vector3 rotation_raycast)
	{
		rotation_raycast.y += speed_rot_raycast_lateral * delta;
		if (rotation_raycast.y > 90 && can_rotate_right)
		{
			speed_rot_raycast_lateral *= -1;
			can_rotate_right = false;
			//rotate_front(delta, rotation_raycast);
		}
		if (rotation_raycast.y < -90 && !can_rotate_right)
		{
			speed_rot_raycast_lateral *= -1;
			can_rotate_right = true;
			//rotate_front(delta, rotation_raycast);
		}
		return rotation_raycast.y;
	}
}