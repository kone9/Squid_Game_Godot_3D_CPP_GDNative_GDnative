#pragma once

#include <Godot.hpp>
#include <Node.hpp>
#include <MeshInstance.hpp>
#include <Label.hpp>
#include <AudioStreamPlayer.hpp>
#include <RigidBody.hpp>
#include <PackedScene.hpp>
#include <Position3D.hpp>
#include <Spatial.hpp>
#include <RandomNumberGenerator.hpp>
#include <Area.hpp>
#include <Timer.hpp>
#include <MeshInstance.hpp>
#include <Tween.hpp>
#include <ColorRect.hpp>

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
        public: 
            int bots_Intellicence;
    
        private:
            RandomNumberGenerator *random;
            ColorRect* headTimeFinishColorRect;

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

            Timer* timer_Count_Down;//referenciar al timer que cuenta

            //para ver en el editor
            AudioStreamPlayer *dollSing;//voz del juego para poder moverse
            AudioStreamPlayer * dollSingX2;//voz del juego para poder moverse
            //para ver en el editor
            AudioStreamPlayer *dollHeadOff;//sonido cuando vuelve la cabeza
            //para ver en el editor
            AudioStreamPlayer *dollHeadOn;//sonido cuando rota la cabeza

            //para ver en el editor
            int totalBots;

            //para ver en el editor
            Ref<PackedScene> Bot;//packet de los bots

            Spatial *bots_instance_tree;//donde se van a instanciar los bots nuevos

            //para ver en el editor
            Area* SpawnArea;//posicion para spawnear

            MeshInstance* doll_head;//referencia a la cabeza de la muñeca
            Tween* doll_Tween;//referencia al tween que se encuentra en la escena de doll
            Timer* Timer_Rotate_head;

            public:
                //static bool headTime;
                //static bool headTimeFinish;
                bool headTime;//si empezo el tiempo cuando roto la cabeza
                bool headTimeFinish;//si termino el tiempo cuando rota la cabeza
            
            //metodos
            private:
                void SpawnBots();//crear bots
                Vector3 RandomPosition();//posicion aleatoria
                void DisplayTime(float timeToDisplay);//para mostrar el tiempo
                void HeadTime(float secs);
                void RotHead(int deg, float timeRotate);
                void CountDown();//esto podria ser un timer
        
                //senials
                private:
                    void _on_timer_Count_Down_timeout();
                    void _on_Timer_Rotate_head_timeout();
                    void _on_dollSing_finished();

	};
}


