#ifndef SRC_PLAYERMOVEMENT_H_
#define SRC_PLAYERMOVEMENT_H_

#pragma once

#include <Godot.hpp>
#include <RigidBody.hpp>
#include <AnimationTree.hpp>
#include <AudioStreamPlayer.hpp>
#include <InputEvent.hpp>
#include <Input.hpp>
#include <Camera.hpp>
#include <PhysicsDirectBodyState.hpp>

namespace godot
{

	class PlayerMovement : public RigidBody
	{
		GODOT_CLASS(PlayerMovement, RigidBody)

	public:
		PlayerMovement();
		virtual ~PlayerMovement();
		static void _register_methods();

		//metodo init no es el ready.PRECAUCION: si llamas a los nodos desde aca vas a tener punteros colgados y se va a cerrar la aplicacion. Se puede usar para definir cosas, pero en las practicas que yo hice no pude buscar nodos desde aca. "Es llamada una vez que Godot ha creado nuestro objeto adecuadamente"..Este método no se registra y es obligatorio que este en todas las clases
		void _init();
		//metodo ready de godot, desde aca podes llamar a los nodos cuando se carganla escena, se ejecuta una sola vez.. Este metodo tiene que estar registrado
		void _ready();
		void _physics_process(const real_t delta);
		void _process(const real_t delta);
		void _integrate_forces(const PhysicsDirectBodyState* state);
		

	private:
		Input* input;//para obtener el input

		//esto es un copy y paste de la clase copiada del juego hecho para youtube
		//VARIABLES
	private:
		Vector3 PlayerMovementInput;
		Vector2 PlayerMouseInput;
		float xRot;

		//variable para tener en el editor referencia
		AnimationTree* anim;

		bool isJumping;//si esta saltando
		bool isWalking;//si esta caminando
		bool isMoving;//si esta movimiendose
		bool isDying;//esta muriendo
		bool isInDeathZone;//esta en zona de muerto

		//variable para ver en el editor colisicon
		int FloorMask;

		//para ver en el editor
		Transform FeetTransform;

		//para ver en el editor
//		   Transform PlayerCamera;//ojo en unity era un gameobject que se obtiene desde el editor
		Camera* PlayerCamera;//para obtener la Camara

		//para ver en el editor
		//Rigidbody PlayerBody; NO ES NECESARIO REFERENCIA A EL MISMO ACA NO HAY COMPONENTES SINO NODOS

		//variable para ver en el editor
		float Speed;

		//variable para ver en el editor
		float Sensitivity;

		//variable para ver en el editor
		float Jumpforce;

		//variable para ver en el editor
		AudioStreamPlayer* feetSteps;
		//variable para ver en el editor
		AudioStreamPlayer* shoot;

		//variable para ver en el editor
		Transform* deathZone;


		//METODOS DEL JUEGO
		void MovePlayer();//para mover el personaje

		void MovePlayerCamera();//para mover la camara con el perosnaje

		void CheckJumping();//para saber si esta saltando

		void CheckMoving();//para saber si se esta momiendo

		void CheckDeathTime();//para morir cuando no es el tiempo


//		    void OnTriggerEnter(Collider other);///Suplantar por triggers godot

//		    void OnTriggerExit(Collider other);//Suplantar por triggers godot
	};

} /* namespace godot */

#endif /* SRC_PLAYERMOVEMENT_H_ */

