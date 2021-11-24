#pragma once

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Timer.hpp>
#include <AudioStreamPlayer3D.hpp>
#include <RigidBody.hpp>
#include <Node.hpp>
#include "GameManager.h"
#include <RandomNumberGenerator.hpp>
#include <Tween.hpp>


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
		GameManager* gameManager;
		bool is_shooting;//si esta disparando o no
		Transform initial_Transform;//initial transform of this Node
		real_t value; //to use with delta time and rotate the rifle
		real_t rotation_speed;


		void shoot();

	private:
		Timer* Timer_shoot;
		RandomNumberGenerator* random;
		Tween* Tween_shoot;

	//senials
	private:
		void _on_Timer_shoot_timeout();




	};
}


