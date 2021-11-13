#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <RayCast.hpp>
#include "GameManager.h"


namespace godot
{
	class Doll : public RayCast
	{
		GODOT_CLASS(Doll, RayCast)
		
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
			GameManager* gameManager;
			float speed_rot_raycast_lateral;
			float speed_rot_raycast_frontal;
			bool can_rotate_right;
			bool can_rotate_backward;
			int direction_speed;//para usar como multiplicador de direccion

		private:
			void rotate_raycast(const real_t delta);
			float rotate_front(const real_t delta, Vector3 rotation_raycast);
			Vector3 rotate_lateral(const real_t delta, Vector3 rotation_raycast);

	};
}


