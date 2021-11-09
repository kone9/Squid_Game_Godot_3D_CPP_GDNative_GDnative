#include "BotAI.h"
#include <SceneTree.hpp>
#include "GameManager.h"

namespace godot
{
	//metodo constructor defino variables
	BotAI::BotAI()
	{
		TargetEnd = nullptr;//un transform medio raro, seguro lo cambio

		speed = 0.1;//PARA VER EN EL EDITOR
		minSpeed = 0;
		maxSpeed = 1;

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
		gameManager = nullptr;
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
		register_method("_physics_process", &BotAI::_physics_process);
		register_method("Move", &BotAI::Move);
		register_method("Walk", &BotAI::Walk);
		register_method("Stop", &BotAI::Stop);
		register_method("Stop", &BotAI::CheckDeathTime);
		register_method("Stop", &BotAI::DeadthAnimation);

		//para ver variables en editor
		register_property<BotAI, float>("minSpeed", &BotAI::minSpeed, 0.1);
		register_property<BotAI, float>("maxSpeed", &BotAI::maxSpeed, 1.0);
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

		//Godot::print("hola mundo soy un BOT");
		//speed -= Random.Range(0f, 1f);
		speed = random->randf_range((real_t)minSpeed, (real_t)maxSpeed);//velocidad del bot
		//intelligence = Random.Range(0f, 100f);
		intelligence = random->randf_range((real_t)0, (real_t)100);
		
		//TargetEnd = GameObject.Find("TargetEnd").transform;
		TargetEnd = get_tree()->get_nodes_in_group("TargetEnd")[0];

		//deathZone = GameObject.Find("DeathZone").transform;
		deathZone = get_tree()->get_nodes_in_group("DeathZone")[0];
		gameManager = get_tree()->get_nodes_in_group("GameManager")[0];

	}

	//funcion Process de Godot
	void BotAI::_process(real_t delta)
	{

	}

	void BotAI::_physics_process(const real_t delta)
	{
		if (isDying)
			return;

		Move(delta);
		CheckDeathTime();
	}


	void BotAI::Move(const real_t delta)
	{
		//aca vienen varias condiciones ahora, es para probar
		bool headTimeFinish = cast_to<GameManager>(gameManager)->headTimeFinish;
		if (!headTimeFinish)
		{
			Walk(delta);
		}
		else
		{
			Stop();
		}
	}

	void BotAI::Walk(const real_t delta)
	{	

		//isWalking = true;
		isWalking = true;
		//isStopped = false;
		isStopped = false;
		//float step = speed * Time.deltaTime;
		
		//transform.position = Vector3.MoveTowards(transform.position, TargetEnd.position, step);
		Vector3 move_vector_Horizontal = get_transform().basis.x * TargetEnd->get_translation().x;
		Vector3 move_vector_vertical = get_transform().basis.z * TargetEnd->get_translation().z;
		Vector3 MoveVector = -(move_vector_vertical + move_vector_Horizontal) * speed;//tiene que ser vector forward posiblemente aca tenga un error

//		transform.position = Vector3.MoveTowards(transform.position, TargetEnd.position, step);
		set_linear_velocity(Vector3(MoveVector.x, -3, MoveVector.z));
		
		//animaciones
		//anim.SetBool("isWalking", true);
		//feetSteps.loop = true;
		//feetSteps.Play(0);
	}


	void BotAI::Stop()
	{
		isWalking = false;
		isStopped = true;
		set_linear_velocity(Vector3( 0 , 0, 0));
		//animaciones
		//anim.SetBool("isWalking", false);
		//feetSteps.loop = false;
	}


	void BotAI::CheckDeathTime()
	{

	}


	void BotAI::DeadthAnimation()
	{

	}
}
