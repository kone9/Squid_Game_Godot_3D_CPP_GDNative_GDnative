#include "GameManager.h"

namespace godot 
{
	GameManager::GameManager()
	{

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
