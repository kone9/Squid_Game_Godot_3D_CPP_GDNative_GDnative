#pragma once

#include <Godot.hpp>
#include <RigidBody.hpp>
#include <AudioStreamPlayer.hpp>
#include <AnimationTree.hpp>

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
        
        private:
            Transform TargetEnd;

            //PARA VER EN EL EDITOR
            float speed;

            //PARA VER EN EL EDITOR
            AnimationTree *anim;

            //PARA VER EN EL EDITOR
            AudioStreamPlayer *feetSteps;

            //PARA VER EN EL EDITOR
            AudioStreamPlayer *shoot;

            Transform deathZone;

            bool isWalking;
            bool AIChecked;
            bool isStopped;
            bool isInDeathZone;
            bool isDying;
            float intelligence;

	};
}

