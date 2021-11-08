#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <MeshInstance.hpp>
#include <Label.hpp>
#include <AudioStreamPlayer.hpp>
#include <RigidBody.hpp>
#include <PackedScene.hpp>
#include <Position3D.hpp>

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
            MeshInstance *Head;
            //para ver en el editor
            int headTimer;//cabeza timer tiempo de rotacion

            //para ver en el editor
            Label *timeText; //para el tiempo 

            //para ver en el editor
            AudioStreamPlayer *dollSing;
            //para ver en el editor
            AudioStreamPlayer *dollHeadOff;
            //para ver en el editor
            AudioStreamPlayer *dollHeadOn;

            //para ver en el editor
            int totalBots;

            //para ver en el editor
            Ref<PackedScene> Bot;//packet de los bots

            //para ver en el editor
            Position3D *SpawnArea;//posicion para spawnear

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


