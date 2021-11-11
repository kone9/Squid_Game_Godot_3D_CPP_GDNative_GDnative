#include "Doll.h"
#include <RigidBody.hpp>
#include <SceneTree.hpp>

namespace godot
{
	Doll::Doll()
	{
		Ojos_RayCast = nullptr;
		gameManager = nullptr;
	}

	Doll::~Doll()
	{
	}
	void Doll::_register_methods()
	{
		register_method("_ready", &Doll::_ready);
		register_method("_process", &Doll::_process);
		register_method("_physics_process", &Doll::_physics_process);
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
}