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
		Head = (MeshInstance*)get_tree()->get_nodes_in_group("doll_head")[0];//obtengo la cabeza de la muñeca
		SpawnArea = (Area*)get_tree()->get_nodes_in_group("TargetSpawn")[0];//obtengo el nodo 3D
		bots_instance_tree = (Spatial*)get_tree()->get_nodes_in_group("bots_instance_tree")[0];//obtengo el nodo padre donde instancio los bots

		SpawnBots();
		headTime = false;
		timeValue = (float)minutes * 60;

		random = RandomNumberGenerator::_new();
		random->randomize();
	}


	void GameManager::_process(real_t delta)
	{

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
			cast_to<RigidBody>(new_bot)->set_translation( RandomPosition() );

			Godot::print("instanciado bot");
		}
	}

	//posicion aleatoria
	Vector3 GameManager::RandomPosition()
	{
		//Vector3 origin = SpawnArea.position;
		Vector3 origin = SpawnArea->get_translation();
		 
		//Vector3 range = SpawnArea.localScale / 2.0f;
		Node* childCollisionSpawnArea = cast_to<Node>(SpawnArea)->get_child(0);
		Ref<Shape> SpawnAreaCollisionShape = cast_to<CollisionShape>(childCollisionSpawnArea)->get_shape();
		Vector3 range = cast_to<BoxShape>(*SpawnAreaCollisionShape)->get_extents() / 2;//tengo que desferenciar el shape, medio raro, pero funciona
		
		//Vector3 randomRange = new Vector3(
			//Random.Range(-range.x, range.x),
			//Random.Range(-range.y, range.y),
			//Random.Range(-range.z, range.z)
		//);
		
		Vector3 randomRange = Vector3(
			random->randf_range(-range.x, range.x),
			random->randf_range(-range.y, range.y),
			random->randf_range(-range.z, range.z)
		);
			
		//Vector3 randomCoordinate = origin + randomRange;
		Vector3 randomCoordinate = origin + randomRange;
		return randomCoordinate;
	}

	void GameManager::DisplayTime(float timeToDisplay)
	{
	}

	void GameManager::HeadTime(float secs)
	{
	}

	void GameManager::RotHead(int deg)
	{
	}


}
