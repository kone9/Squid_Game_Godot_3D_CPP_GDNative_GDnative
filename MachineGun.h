#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Timer.hpp>
#include <AudioStreamPlayer3D.hpp>
#include <RigidBody.hpp>


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

	public:
		RigidBody* bot_to_kill;
		AudioStreamPlayer3D* Machine_Gun_Sound;
		bool is_shooting;//si esta disparando o no

		void shoot(Vector3 look_at_bot);

	private:
		Timer* Timer_shoot;

	//senials
	private:
		void _on_Timer_shoot_timeout();




	};
}


