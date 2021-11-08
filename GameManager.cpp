#include "GameManager.h"

namespace godot 
{
	GameManager::GameManager()
	{
		minutes = 1;
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
	}

	void GameManager::_process(real_t delta)
	{

	}

	void GameManager::SpawnBots()
	{
	}

	Vector3 GameManager::RandomPosition()
	{
		return Vector3();
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
