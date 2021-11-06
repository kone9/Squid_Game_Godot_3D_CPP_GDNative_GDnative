#include "BotAI.h"

namespace godot
{
	//metodo constructor defino variables
	BotAI::BotAI()
	{
		TargetEnd = Transform::IDENTITY;//un transform medio raro, seguro lo cambio

		//PARA VER EN EL EDITOR
		speed = 0;

		//PARA VER EN EL EDITOR
		anim = nullptr;

		//PARA VER EN EL EDITOR
		feetSteps = nullptr;

		//PARA VER EN EL EDITOR
		shoot = nullptr;

		deathZone = Transform::IDENTITY;

		isWalking = false;
		AIChecked = false;
		isStopped = false;
		isInDeathZone = false;
		isDying = false;
		intelligence = false;
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
		Godot::print("hola mundo soy un BOT");
	}
	//funcion Process de Godot
	void BotAI::_process(real_t delta)
	{

	}
}
