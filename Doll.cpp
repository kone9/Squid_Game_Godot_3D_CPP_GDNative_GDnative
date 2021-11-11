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
		rotate_raycast(delta);//para detectar movimiento en bots o jugador

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
		Ojos_RayCast->set_rotation_degrees(Vector3(
			Ojos_RayCast->get_rotation_degrees().x,
			Ojos_RayCast->get_rotation_degrees().y - speed_rotation_eye_raycast * delta,
			Ojos_RayCast->get_rotation_degrees().z)
		);
		/*if (Ojos_RayCast->get_rotation_degrees().y > 45)
		{
			Ojos_RayCast->set_rotation_degrees(Vector3(
				Ojos_RayCast->get_rotation_degrees().x,
				Ojos_RayCast->get_rotation_degrees().y - speed_rotation_eye_raycast * delta,
				Ojos_RayCast->get_rotation_degrees().z)
			);
		}
		if (Ojos_RayCast->get_rotation_degrees().y < -45)
		{
			Ojos_RayCast->set_rotation_degrees(Vector3(
				Ojos_RayCast->get_rotation_degrees().x,
				Ojos_RayCast->get_rotation_degrees().y + speed_rotation_eye_raycast * delta,
				Ojos_RayCast->get_rotation_degrees().z)
			);
		}*/
	}
}