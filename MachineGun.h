#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>

namespace godot
{
	class MachineGun : public Spatial
	{
		GODOT_CLASS(MachineGun, Spatial)

	public:
		MachineGun();
		virtual ~MachineGun();
		static void _register_methods();

		void _init();
		void _ready();
		void _process(real_t delta);
	};
}


