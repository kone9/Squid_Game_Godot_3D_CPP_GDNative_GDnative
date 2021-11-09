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

			Godot::print("instanciado bot");
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

	void GameManager::HeadTime(float secs)
	{
	}

	void GameManager::RotHead(int deg)
	{
	}


}
