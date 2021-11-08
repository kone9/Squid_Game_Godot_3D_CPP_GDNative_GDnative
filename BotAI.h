#pragma once

#include <Godot.hpp>
#include <RigidBody.hpp>
#include <AudioStreamPlayer.hpp>
#include <AnimationTree.hpp>
#include <RandomNumberGenerator.hpp>
#include <Position3D.hpp>

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
        
        private:
            RandomNumberGenerator *random;

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

            bool isWalking;
            bool AIChecked;
            bool isStopped;
            bool isInDeathZone;
            bool isDying;
            float intelligence;

        //Metodos
        private:
            void Move(const real_t delta);
            void Walk(const real_t delta);
            void Stop();
            void CheckDeathTime();
            void DeadthAnimation();
            
           /* void OnTriggerEnter(Collider other);
            void OnTriggerExit(Collider other);*/


	};
}

