#include "BotAI.h"
#include <SceneTree.hpp>
#include "GameManager.h"

#include "AnimationNodeStateMachinePlayback.hpp"
#include "AnimationNodeStateMachine.hpp"

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
		is_collided_with_another_bot = false;
		is_to_die = false;
		use_global_intelligence = true;
		bot_intelligence = 100;
		i_am_the_banana = false;

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
		register_property<BotAI, float>("maxSpeed", &BotAI::maxSpeed, 1.0);
		register_property<BotAI, bool>("use_global_intelligence", &BotAI::use_global_intelligence, true);
		register_property<BotAI, int>("bot_intelligence", &BotAI::bot_intelligence, 100);
		register_property<BotAI, bool>("i_am_the_banana", &BotAI::i_am_the_banana, false);

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
		// random = RandomNumberGenerator::_new();
		// random->randomize();
		

		// speed = random->randf_range((real_t)minSpeed, (real_t)maxSpeed);//velocidad del bot
		
		// //If you use global intelligence or that of the bot, it is because of the bots that are on the scene and are not instantiated
		// if (use_global_intelligence)
		// {
		// 	intelligence = random->randf_range((real_t)0, (real_t)cast_to<GameManager>(gameManager)->bots_Intellicence);//la inteligencia es aleatoria del 1 al 100
		// 	//bot_intelligence = cast_to<GameManager>(gameManager)->bots_Intellicence;
		// }
		// else
		// {
		// 	intelligence = random->randf_range((real_t)0, (real_t)bot_intelligence);//la inteligencia es aleatoria del 1 al 100
		// }
		

		// //TargetEnd = get_tree()->get_nodes_in_group("TargetEnd")[0];

		// TimerDeadthAnimation = get_node<Timer>("TimerDeadthAnimation");
	
		
		// if(anim == nullptr) return;
		// AnimationNodeStateMachine *state_machine = animation_tree->get_node("parameters/StateMachine");
		

		AnimationTree *animation_tree = get_node<AnimationTree>("AnimationTreeBot");

		if (animation_tree) {
        // Accede al AnimationNodeStateMachine
        // AnimationNodeStateMachine *state_machine = animation_tree->get("parameters/StateMachine");  // Ajusta la ruta según tu configuración

        // if (state_machine) {
        //     // Obtén la instancia de AnimationNodeStateMachinePlayback desde el AnimationTreePlayer
        //     AnimationNodeStateMachinePlayback *playback = animation_tree->get_node("parameters/StateMachine")->get_current_node_playback();

        //     if (playback) {
        //         // Realiza operaciones con AnimationNodeStateMachinePlayback
        //         playback->travel("nombre_del_estado");  // Reemplaza "nombre_del_estado" con el nombre real del estado
        //     }
        // }
    }
		

	}

	//funcion Process de Godot
	void BotAI::_process(real_t delta)
	{

	}

	void BotAI::_physics_process(const real_t delta)
	{
		Walk(delta);
		// if (cast_to<GameManager>(gameManager)->finish_Intro)
		// {
		// 	if (!isDying)//sino esta muriendo
		// 	{
		// 		Move(delta);
		// 		//CheckDeathTime();
		// 	}
		// }
	}

	//dependiendo la inteligencia va a caminar o no
	void BotAI::Move(const real_t delta)
	{
		//aca vienen varias condiciones ahora, es para probar
		bool headTimeFinish = cast_to<GameManager>(gameManager)->headTimeFinish;
		
		

		if (!headTimeFinish)//si la cabeza no se dio vuelta, osea puedo caminar
		{
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
				if (!is_collided_with_another_bot)//sino colisiona con otro bot
				{
					Walk(delta);
				}
			}

		}
	}

	void BotAI::Walk(const real_t delta)
	{	
		isWalking = true;
		isStopped = false;
		
		// Vector3 move_vector_Horizontal = get_transform().basis.x * TargetEnd->get_translation().x;
		// Vector3 move_vector_vertical = get_transform().basis.z * TargetEnd->get_translation().z;
		Vector3 move_vector_Horizontal = get_transform().basis.x;
		Vector3 move_vector_vertical = get_transform().basis.z;
		Vector3 MoveVector = -(move_vector_vertical + move_vector_Horizontal) * speed;//tiene que ser vector forward posiblemente aca tenga un error

		set_linear_velocity(Vector3(MoveVector.x, -3, MoveVector.z));
		
		//cast_to<AnimationNodeStateMachinePlayback>(anim)->travel("walk");
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
		//cast_to<AnimationNodeStateMachinePlayback>(anim)->travel("idle");
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
	
	void BotAI::_on_BotArea_area_entered(Area* area)
	{
		isInDeathZone = true;

		if ( area->is_in_group("BotArea") )
		{
			is_collided_with_another_bot = true;
		}
	}

	void BotAI::_on_BotArea_area_exited(Area* area)
	{
		isInDeathZone = false;

		if (area->is_in_group("BotArea"))
		{
			is_collided_with_another_bot = false;
		}
	}
	
}
