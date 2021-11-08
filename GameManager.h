#pragma once

#include <Godot.hpp>
#include <Node.hpp>

namespace godot
{
	class GameManager : public Node
	{
		GODOT_CLASS(GameManager, Node)
		
		public:
			GameManager();
			virtual ~GameManager();
			static void _register_methods();

			void _init();
			void _ready();
			void _process(real_t delta);

        //variables
        private:
            //para ver en el editor
            int minutes;
            float timeValue;
            float lastTimeToHead;

            //para ver en el editor
            //Transform Head;
            //para ver en el editor
            //int headTimer;

            //para ver en el editor
            //Text timeText;

            //para ver en el editor
            //AudioSource dollSing;
            //para ver en el editor
            //AudioSource dollHeadOff;
            //para ver en el editor
            //AudioSource dollHeadOn;

            //para ver en el editor
            //int totalBots;

            //para ver en el editor
            //GameObject Bot;

            //para ver en el editor
            //Transform SpawnArea;

            public:
                static bool headTime;
                static bool headTimeFinish;
            
            //metodos
            private:
                void SpawnBots();//crear bots
                Vector3 RandomPosition();//posicion aleatoria
                void DisplayTime(float timeToDisplay);//para mostrar el tiempo
                void HeadTime(float secs);
                void RotHead(int deg);
                void CountDown();//esto podria ser un timer

	};
}


