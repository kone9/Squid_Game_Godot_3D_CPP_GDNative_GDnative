#include "BotAI.h"
#include <SceneTree.hpp>

namespace godot
{
	//metodo constructor defino variables
	BotAI::BotAI()
	{
		TargetEnd = nullptr;//un transform medio raro, seguro lo cambio

		speed = 0;//PARA VER EN EL EDITOR

		anim = nullptr;//PARA VER EN EL EDITOR

		feetSteps = nullptr;//PARA VER EN EL EDITOR

		shoot = nullptr;//PARA VER EN EL EDITOR

		deathZone = nullptr;

		isWalking = false;
		AIChecked = false;
		isStopped = false;
		isInDeathZone = false;
		isDying = false;
		intelligence = false;
		
		random = nullptr;
	}

	//metodo destructor
	BotAI::~BotAI()
	{

	}
	
	//para registrar las funciones
	void BotAI::_register_methods()
	{
		//metodos de Godot
		register_method("_ready", &BotAI::_ready);
		register_method("_process", &BotAI::_process);
	}

	//fundamental, sino esta se cierra el editor NO ES READY
	void BotAI::_init()
	{

	}
	//funcion ready de Godot
	void BotAI::_ready()
	{
		random = RandomNumberGenerator::_new();
		random->randomize();

		Godot::print("hola mundo soy un BOT");
		//speed -= Random.Range(0f, 1f);
		speed -= random->randf_range((real_t)0, (real_t)1);
		//intelligence = Random.Range(0f, 100f);
		intelligence = random->randf_range((real_t)0, (real_t)100);
		
		//TargetEnd = GameObject.Find("TargetEnd").transform;
		TargetEnd = get_tree()->get_nodes_in_group("TargetEnd")[0];

		//deathZone = GameObject.Find("DeathZone").transform;
		deathZone = get_tree()->get_nodes_in_group("DeathZone")[0];

	}

	//funcion Process de Godot
	void BotAI::_process(real_t delta)
	{
	}


	void BotAI::Move()
	{
	}


	void BotAI::Walk()
	{
	}


	void BotAI::Stop()
	{
	}


	void BotAI::CheckDeathTime()
	{
	}


	void BotAI::DeadthAnimation()
	{
	}
}
