#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <RayCast.hpp>

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

	};
}


