#include "Doll.h"
#include <RigidBody.hpp>
#include <SceneTree.hpp>

namespace godot
{
	Doll::Doll()
	{
		Ojos_RayCast = nullptr;
		gameManager = nullptr;
		speed_rotation_eye_raycast = 0.1;
		can_rotate_right = true;
		can_rotate_backward = true;
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
		register_property<Doll, float>("speed_rotation_eye_raycast", &Doll::speed_rotation_eye_raycast, 0.1);
	}

	void Doll::_init()
	{
	}

	void Doll::_ready()
	{
		Godot::print("creada DOLL");
		Ojos_RayCast = get_node<RayCast>("Ojos_RayCast");
		gameManager = (GameManager*)get_tree()->get_nodes_in_group("GameManager")[0];
	}

	void Doll::_process(real_t delta)
	{
	}

	void Doll::_physics_process(const real_t delta)
	{
		rotate_raycast(delta);//roto el raycast constantemente
		
		if (gameManager->headTimeFinish)//si termino el tiempo cuando se pueden mover
		{
			if (Ojos_RayCast->is_colliding())//si colisiona el raycast
			{
				RigidBody* bot = cast_to<RigidBody>(Ojos_RayCast->get_collider());//obtengo el nodo rigibody colisionado
				if (bot->get_linear_velocity().z != 0)//si su lineal velocity en el eje z es distion de cero
				{
					Godot::print(bot->get_name());//imprimo el nombre
					bot->queue_free();//lo elimino
				}
			}
		}
	}


	//para rotar el raycast y detectar enemigos
	void Doll::rotate_raycast(const real_t delta)
	{
		Vector3 rotation_raycast = Ojos_RayCast->get_rotation_degrees();
		rotation_raycast.y = rotate_lateral(delta, rotation_raycast);

		Ojos_RayCast->set_rotation_degrees(Vector3(
			rotation_raycast.x,
			rotation_raycast.y,
			rotation_raycast.z)
		);
		
	}

	float Doll::rotate_front(const real_t delta, Vector3 rotation_raycast)
	{
		if (rotation_raycast.z < 0 && can_rotate_backward)
		{
			can_rotate_backward = false;
			rotation_raycast.z -= 1;
		}
		if (rotation_raycast.z > 85 && !can_rotate_backward)
		{
			can_rotate_backward = true;
			rotation_raycast.z += 1;
		}
		return rotation_raycast.z;
	}

	float Doll::rotate_lateral(const real_t delta, Vector3 rotation_raycast)
	{
		rotation_raycast.y += speed_rotation_eye_raycast * delta;
		if (rotation_raycast.y > 55 && can_rotate_right)
		{
			speed_rotation_eye_raycast *= -1;
			can_rotate_right = false;
		}
		if (rotation_raycast.y < -55 && !can_rotate_right)
		{
			speed_rotation_eye_raycast *= -1;
			can_rotate_right = true;
		}
		return rotation_raycast.y;
	}
}