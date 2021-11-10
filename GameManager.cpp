#include "GameManager.h"
#include <SceneTree.hpp>

#include <CollisionShape.hpp>
#include <Shape.hpp>
#include <BoxShape.hpp>

namespace godot 
{
	GameManager::GameManager()
	{
		minutes = 5;
		timeValue = 1;
		lastTimeToHead = 1;

		//para ver en el editor
		Head = nullptr;
		//para ver en el editor
		headTimer = 1;//cabeza timer tiempo de rotacion

		//para ver en el editor
		timeText = nullptr; //para el tiempo 

		dollSing = nullptr;
		//para ver en el editor
		dollHeadOff = nullptr;
		//para ver en el editor
		dollHeadOn = nullptr;

		totalBots = 1;

		Bot = nullptr;

		SpawnArea = nullptr;

		headTime = false;
		headTimeFinish = false;

		bots_instance_tree = nullptr;
		random = nullptr;
		timer_Count_Down = nullptr;

		doll_head = nullptr;
		doll_Tween = nullptr;
		dollSingX2 = nullptr;

		headTimeFinishColorRect = nullptr;
	}

	GameManager::~GameManager()
	{

	}

	void GameManager::_register_methods()
	{
		//metodos de godot
		register_method("_ready", &GameManager::_ready);
		register_method("_process", &GameManager::_process);

		//metodos del juego
		register_method("SpawnBots", &GameManager::SpawnBots);
		register_method("RandomPosition", &GameManager::RandomPosition);
		register_method("DisplayTime", &GameManager::DisplayTime);
		register_method("HeadTime", &GameManager::HeadTime);
		register_method("RotHead", &GameManager::RotHead);

		//para ver en el editor
		register_property<GameManager, int>("minutes", &GameManager::minutes, 1);
		register_property<GameManager, int>("headTimer", &GameManager::headTimer, 1);
		register_property<GameManager, int>("totalBots", &GameManager::totalBots, 1);
		register_property<GameManager, Ref<PackedScene> >("Bot", &GameManager::Bot, nullptr);//propiedad packet scene para que se vea en el editor

		//senials
		register_method("_on_timer_Count_Down_timeout", &GameManager::_on_timer_Count_Down_timeout);
		register_method("_on_Timer_Rotate_head_timeout", &GameManager::_on_Timer_Rotate_head_timeout);
		register_method("_on_dollSing_finished", &GameManager::_on_dollSing_finished);

		register_signal<GameManager>("can_Walk", godot::Dictionary());

	}

	void GameManager::_init()
	{

	}

	void GameManager::_ready()
	{
		Godot::print("GameManager Creado");
		random = RandomNumberGenerator::_new();
		random->randomize();
		
		Head = (MeshInstance*)get_tree()->get_nodes_in_group("doll_head")[0];//obtengo la cabeza de la muñeca
		SpawnArea = (Area*)get_tree()->get_nodes_in_group("TargetSpawn")[0];//obtengo el nodo 3D
		bots_instance_tree = (Spatial*)get_tree()->get_nodes_in_group("bots_instance_tree")[0];//obtengo el nodo padre donde instancio los bots
		timeText = (Label*)get_tree()->get_nodes_in_group("timeText")[0];
		timer_Count_Down = (Timer*)get_tree()->get_nodes_in_group("timer_Count_Down")[0];
		doll_head = (MeshInstance*)get_tree()->get_nodes_in_group("doll_head")[0];
		doll_Tween = (Tween*)get_tree()->get_nodes_in_group("doll_Tween")[0];
		dollSing = (AudioStreamPlayer*)get_tree()->get_nodes_in_group("dollSing")[0];
		dollHeadOn = (AudioStreamPlayer*)get_tree()->get_nodes_in_group("dollHeadOn")[0];
		dollHeadOff = (AudioStreamPlayer*)get_tree()->get_nodes_in_group("dollHeadOff")[0];
		dollSingX2 = (AudioStreamPlayer*)get_tree()->get_nodes_in_group("dollSingX2")[0];
		Timer_Rotate_head = (Timer*)get_tree()->get_nodes_in_group("Timer_Rotate_head")[0];

		headTimeFinishColorRect = (ColorRect*)get_tree()->get_nodes_in_group("headTimeFinishColorRect")[0];

		
		dollSing->play();//inicio con sonido de voz

		SpawnBots();
		headTime = false;
		timeValue = (float)minutes * 60;


	}


	void GameManager::_process(real_t delta)
	{
		DisplayTime( timer_Count_Down->get_time_left() );
	}
	
	//para instanciar los bots
	void GameManager::SpawnBots()
	{
		/*for (int i = 0; i < totalBots; i++)
			Instantiate(Bot, RandomPosition(), SpawnArea.rotation);*/

		for (int i = 0; i < totalBots; i++)
		{
			//Instantiate(Bot, RandomPosition(), SpawnArea.rotation);
			Node* new_bot = Bot->instance();
			bots_instance_tree->add_child(new_bot);
			cast_to<RigidBody>(new_bot)->set_translation( RandomPosition() );//instancia en posicion aleatoria

			/*Godot::print("instanciado bot");*/
		}
	}

	//posicion aleatoria
	Vector3 GameManager::RandomPosition()
	{
		//Vector3 origin = SpawnArea.position;
		Node* childCollisionSpawnArea = cast_to<Node>(SpawnArea)->get_child(0);
		Vector3 origin = cast_to<CollisionShape>(childCollisionSpawnArea)->get_global_transform().origin;//posicion global de este nodo
		 
		//Vector3 range = SpawnArea.localScale / 2.0f;
		Ref<Shape> SpawnAreaCollisionShape = cast_to<CollisionShape>(childCollisionSpawnArea)->get_shape();
		Vector3 range = cast_to<BoxShape>(*SpawnAreaCollisionShape)->get_extents();//tengo que desferenciar el shape, medio raro, pero funciona
		
		/*Vector3 randomRange = new Vector3(Random.Range(-range.x, range.x),
			Random.Range(-range.y, range.y),
			Random.Range(-range.z, range.z));*/

		Vector3 randomRange = Vector3(
				random->randf_range(-(real_t)range.x, (real_t)range.x),
				1.0,
				random->randf_range(-(real_t)range.z, (real_t)range.z)
		);
		
		////Vector3 randomCoordinate = origin + randomRange;
		Vector3 randomCoordinate = origin + randomRange;//posicion de origen más posicion aleatoria en el dentro del rectangulo de instancia
		//return randomCoordinate;
		return randomCoordinate;
	}

	//muestra el tiempo que queda en el nodo label usando el timer de la escena
	void GameManager::DisplayTime(float timeToDisplay)
	{
		/*if (timeToDisplay < 0)
			timeToDisplay = 0;*/

		//float mins = Mathf.FloorToInt(timeToDisplay / 60);
		int min = timeToDisplay / 60;//redondea a entero

		//float secs = Mathf.FloorToInt(timeToDisplay % 60);
		int secs = (int)timeToDisplay % 60;//en c++ solo se permite int como modulo

		//timeText.text = string.Format("{0:00}:{1:00}", mins, secs);
		timeText->set_text( String::num_int64(min) + " : " + String::num_int64(secs) );
	}

	//para rotar la cabeza cada cierto tiempo, aca tendria que decir cuando se puede o no puede moverse
	void GameManager::HeadTime(float secs)
	{
		//if (timeValue <= 0)
		//{
		//	headTimeFinish = true;
		//	RotHead(180);
		//	return;
		//}

		//if (secs % headTimer == 0 && secs != lastTimeToHead)
		//{
		//	lastTimeToHead = secs;
		//	headTime = !headTime;

		//	if (headTime)
		//	{
		//		dollHeadOn.Play(0);//sonido
		//	}
		//	else
		//	{
		//		if (!dollSing.isPlaying)
		//			dollHeadOff.Play(0);//sonido

		//		if (!dollSing.isPlaying)
		//			dollSing.PlayDelayed(1);//sonido
		//	}
		//}

		
	}

	void GameManager::RotHead(int deg, float timeRotate)
	{
		Vector3 new_rotation = doll_head->get_rotation_degrees();
		new_rotation.y += deg;
		
		doll_Tween->interpolate_property(
			doll_head,
			"rotation_degrees",
			doll_head->get_rotation_degrees(),
			new_rotation,
			timeRotate,
			Tween::TransitionType::TRANS_LINEAR,
			Tween::EaseType::EASE_OUT
		);

		if (!doll_Tween->is_active())//lo voy a ejecutar solo cuando no este activo
		{
			doll_Tween->start();//ejecuto el tween
		}
	}

	void GameManager::_on_timer_Count_Down_timeout()
	{
		Godot::print("termino el tiempo");
	}

	//si este timer no termino muere
	void GameManager::_on_Timer_Rotate_head_timeout()
	{
		Godot::print("tendria que VOLVER la cabeza");
		headTimeFinish = false;//cuando termina el tiempo puede moverse, sino no pueden moverse
		RotHead(-180, 0.5);
		dollHeadOn->play();//sonido cabeza
		int random_dollSing = random->randi_range(0, 1);
		
		headTimeFinishColorRect->set_frame_color(Color(0, 1, 0));
		
		emit_signal("can_Walk");//emite la señal que se puede volver a caminar
		
		if (random_dollSing == 0)
		{
			dollSing->play();//activo sonido, cuando termina da vuelta la cabeza
		}
		else
		{
			dollSingX2->play();//activo sonido, cuando termina da vuelta la cabeza
		}
	}

	void GameManager::_on_dollSing_finished()
	{
		Godot::print("tendria que ROTAR la cabeza");
		RotHead(180,1);
		headTimeFinish = true;
		headTimeFinishColorRect->set_frame_color(Color(1, 0, 0));
		int randomTime = random->randi_range(6,10);
		Timer_Rotate_head->set_wait_time(randomTime);
		Timer_Rotate_head->start();//activo timer que si se mueven mueren
		dollHeadOff->play();//sonido cabeza
	}


}
