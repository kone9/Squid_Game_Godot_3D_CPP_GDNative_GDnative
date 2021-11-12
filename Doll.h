#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <RayCast.hpp>
#include "GameManager.h"


namespace godot
{
	class Doll : public Spatial
	{
		GODOT_CLASS(Doll,Spatial)
		
		//metodos de godot
		public:
			Doll();
			virtual ~Doll();
			static void _register_methods();

			void _init();
			void _ready();
			void _process(real_t delta);
			void _physics_process(const real_t delta);

		private:
			RayCast* Ojos_RayCast;//guarda el raycast que funciona como los ojos de la muñeca
			GameManager* gameManager;
			float speed_rotation_eye_raycast;
			bool can_rotate_right;
			bool can_rotate_backward;

		private:
			void rotate_raycast(const real_t delta);
			float rotate_front(const real_t delta, Vector3 rotation_raycast);
			float rotate_lateral(const real_t delta, Vector3 rotation_raycast);

	};
}


