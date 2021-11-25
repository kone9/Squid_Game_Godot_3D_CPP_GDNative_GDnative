#pragma once

#include <Godot.hpp>
#include <RigidBody.hpp>
#include <AudioStreamPlayer.hpp>
#include <AnimationTree.hpp>
#include <RandomNumberGenerator.hpp>
#include <Position3D.hpp>
#include <Node.hpp>
#include <Timer.hpp>
#include <AudioStreamPlayer3D.hpp>
#include <Area.hpp>


namespace godot
{
	class BotAI :public RigidBody
	{
		GODOT_CLASS(BotAI,RigidBody)

		public:
			BotAI();
			virtual ~BotAI();
			static void _register_methods();

			void _init();
			void _ready();
			void _process(real_t delta);
            void _physics_process(const real_t delta);
        
        public:
            bool is_to_die;

        private:
            RandomNumberGenerator *random;
            Node* gameManager;
            Timer* TimerDeadthAnimation;
            AudioStreamPlayer3D* deathSound;
            bool is_collided_with_another_bot;

        private:
            Position3D *TargetEnd;//posicion final

            //PARA VER EN EL EDITOR
            float maxSpeed;
            float minSpeed;
            float speed;

            //PARA VER EN EL EDITOR
            AnimationTree *anim;

            //PARA VER EN EL EDITOR
            AudioStreamPlayer *feetSteps;

            //PARA VER EN EL EDITOR
            AudioStreamPlayer *shoot;

            Position3D *deathZone;//posicion de muerte

            bool isWalking;//si esta caminando
            bool AIChecked;//para saber si la IA esta verificada
            bool isStopped;//si esta detenido
            bool isInDeathZone;//si esta en la zona de morir
            float intelligence;//la inteligencia de este bot

        bool isDying;//si esta muerto
        
        //Metodos
        private:
            void Move(const real_t delta);
            void Walk(const real_t delta);
            void Stop();
            void CheckDeathTime();
            void DeadthAnimation();
            void ModifySpeedScroll();
        
        //senials
        private:
            void _on_BotArea_area_entered(Area* area);
            void _on_BotArea_area_exited(Area* area);
            void _on_TimerDeadthAnimation_timeout();
            void _on_deathSound_finished();

           /* void OnTriggerEnter(Collider other);
            void OnTriggerExit(Collider other);*/


	};
}

