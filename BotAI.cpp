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
		isInDeathZone = true;
		isDying = false;
		intelligence = false;
		
		random = nullptr;
		gameManager = nullptr;
		TimerDeadthAnimation = nullptr;
		deathSound = nullptr;

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
		register_method("ModifySpeedScroll", &BotAI::ModifySpeedScroll);

		//para ver variables en editor
		register_property<BotAI, float>("minSpeed", &BotAI::minSpeed, 0.1);
		register_property<BotAI, float>("maxSpeed", &BotAI::maxSpeed, 1.0);

		//senials
		register_method("_on_BotArea_area_entered", &BotAI::_on_BotArea_area_entered);
		register_method("_on_BotArea_area_exited", &BotAI::_on_BotArea_area_exited);
		register_method("_on_TimerDeadthAnimation_timeout", &BotAI::_on_TimerDeadthAnimation_timeout);
		register_method("_on_deathSound_finished", &BotAI::_on_deathSound_finished);
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
		gameManager = get_tree()->get_nodes_in_group("GameManager")[0];

		//Godot::print("hola mundo soy un BOT");
		//speed -= Random.Range(0f, 1f);
		speed = random->randf_range((real_t)minSpeed, (real_t)maxSpeed);//velocidad del bot
		//intelligence = Random.Range(0f, 100f);
		intelligence = random->randf_range((real_t)0, (real_t)cast_to<GameManager>(gameManager)->bots_Intellicence);//la inteligencia es aleatoria del 1 al 100
		
		//TargetEnd = GameObject.Find("TargetEnd").transform;
		TargetEnd = get_tree()->get_nodes_in_group("TargetEnd")[0];

		//deathZone = GameObject.Find("DeathZone").transform;
		//deathZone = get_tree()->get_nodes_in_group("DeathZone")[0];

		deathSound = get_node<AudioStreamPlayer3D>("deathSound");
		
		TimerDeadthAnimation = get_node<Timer>("TimerDeadthAnimation");

		gameManager->connect("can_Walk", this, "ModifySpeedScroll");

		

	}

	//funcion Process de Godot
	void BotAI::_process(real_t delta)
	{

	}

	void BotAI::_physics_process(const real_t delta)
	{
		if (!isDying)//si esta muriendo
		{
			Move(delta);
			//CheckDeathTime();
		}
	}

	//dependiendo la inteligencia va a caminar o no
	void BotAI::Move(const real_t delta)
	{
		//aca vienen varias condiciones ahora, es para probar
		bool headTimeFinish = cast_to<GameManager>(gameManager)->headTimeFinish;
		
		if (!headTimeFinish)//si la cabeza no se dio vuelta, osea puedo caminar
		{
			//AIChecked = false;//la IA no esta verificada
			Walk(delta);// camina
		}
		else//si la cabeza se dio vuelta
		{
			//float probDead = Random.Range(0f, 100f);
			float probDead = random->randf_range(0, 100);//probabilidad de morir

			if (probDead < intelligence)//ACA VERIFICO LA INTELIGENCIA si la probabilidad de morir es menor a la inteligencia
			{
				Stop();//se detiene
			}
			else//verifique la intelgencia y no se esta moviendo
			{
				Walk(delta);
			}
			
			//if (!AIChecked)//sino verificque la inteligencia
			//{
			//	AIChecked = true;//verifique la inteligencia
			//	//float probDead = Random.Range(0f, 100f);
			//	float probDead = random->randf_range(0, 100);//probabilidad de morir

			//	if (probDead < intelligence)//ACA VERIFICO LA INTELIGENCIA si la probabilidad de morir es menor a la inteligencia
			//	{
			//		Stop();//se detiene
			//	}
			//}
			//else if (AIChecked && !isStopped)//verifique la intelgencia y no se esta moviendo
			//{
			//	Walk(delta);
			//}
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

	//verifica si el tiempo se termino y si se segui moviendo. Si se sigue moviendo es eliminado
	void BotAI::CheckDeathTime()
	{
		//if (cast_to<GameManager>(gameManager)->headTimeFinish)// si la cabeza se dio vuelta y esta caminado
		//{
		//	if (isWalking)//si esta caminando
		//	{
		//		if (isInDeathZone)//sino esta en la zona de muerte
		//		{
		//			isDying = true;//esta mueriendo
		//			//StartCoroutine(DeadthAnimation());
		//			real_t randonWaitTime = random->randf_range(1, 2);//tiempo aleatorio timer
		//			TimerDeadthAnimation->set_wait_time(randonWaitTime);//cambio el tiempo
		//			TimerDeadthAnimation->start();//inicio el timer
		//		}
		//	}
		//}
	}

	void BotAI::_on_TimerDeadthAnimation_timeout()
	{
		//deathSound->play();
		//queue_free();//para probar elimino el nodo
	}

	void BotAI::_on_deathSound_finished()
	{
		//queue_free();
	}

	void BotAI::DeadthAnimation()
	{

	}

	void BotAI::ModifySpeedScroll()
	{
		speed = random->randf_range((real_t)minSpeed, (real_t)maxSpeed);//velocidad del bot
		//Godot::print(String::num_real(speed));
	}
	
	void BotAI::_on_BotArea_area_entered()
	{
		isInDeathZone = true;
	}

	void BotAI::_on_BotArea_area_exited()
	{
		isInDeathZone = false;
	}
	
}
