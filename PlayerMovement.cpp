
#include "PlayerMovement.h"
#include <CanvasItem.hpp>
#include <InputEventMouseMotion.hpp>
#include <Viewport.hpp>

namespace godot
{

	PlayerMovement::PlayerMovement()
	{
		// TODO Auto-generated constructor stub
		PlayerMovementInput = Vector3::ZERO;
		PlayerMouseInput = Vector2::ZERO;
		xRot = 0;

		//variable para tener en el editor referencia
		anim = nullptr;

		isJumping = false;
		isWalking = false;
		isMoving = false;
		isDying = false;
		isInDeathZone = false;

		//variable para ver en el editor colisicon
		FloorMask = 0;

		//para ver en el editor
		FeetTransform = Transform::IDENTITY;

		//para ver en el editor
		PlayerCamera = nullptr;

		//para ver en el editor
		//Rigidbody PlayerBody; NO ES NECESARIO REFERENCIA A EL MISMO ACA NO HAY COMPONENTES SINO NODOS

		//variable para ver en el editor
		Speed = 0;

		//variable para ver en el editor
		Sensitivity = 0;

		//variable para ver en el editor
		Jumpforce = 0;

		//variable para ver en el editor
		feetSteps = nullptr;
		//variable para ver en el editor
		shoot = nullptr;

		//variable para ver en el editor
		deathZone = nullptr;

		input = nullptr;
		PlayerCamera = nullptr;
		h = 0;
		v = 0;
	}

	PlayerMovement::~PlayerMovement()
	{
		// TODO Auto-generated destructor stub
	}

	void PlayerMovement::_register_methods()
	{
		//registro los m�todos
		register_method("_ready", &PlayerMovement::_ready);
		register_method("_process", &PlayerMovement::_process);
		register_method("_physics_process", &PlayerMovement::_physics_process);
		//		register_method("_input", &PlayerMovement::_input);
		register_method("MovePlayer", &PlayerMovement::MovePlayer);
		register_method("MovePlayerCamera", &PlayerMovement::MovePlayerCamera);
		register_method("CheckJumping", &PlayerMovement::CheckJumping);
		register_method("CheckMoving", &PlayerMovement::CheckMoving);
		register_method("CheckDeathTime", &PlayerMovement::CheckDeathTime);

		//Variables para ver en el editor
		register_property<PlayerMovement, float>("PlayerMovement", &PlayerMovement::Speed, 1);
		register_property<PlayerMovement, float>("Sensitivity", &PlayerMovement::Sensitivity, 1);
		register_property<PlayerMovement, float>("Jumpforce", &PlayerMovement::Jumpforce, 1);

	}

	void PlayerMovement::_init()
	{
	}

	void PlayerMovement::_ready()
	{
		input = Input::get_singleton();//obtener el input

		PlayerCamera = get_node<Camera>("Camera");//obtener la camara
		Godot::print("inicio el juegador con el player movement");
		Godot::print("proyecto funcionado correctamente");
		Godot::print("PROYECTO LISTO PARA SUBIR");
	}

	void PlayerMovement::_process(const real_t delta)
	{
		//		if (isDying) {return;}
		//		float v = input->get_action_strength("w") - input->get_action_strength("s");//movimiento adelante
		if (input->is_action_pressed("w"))
		{
			Godot::print("presione W");
		}
		//Godot::print(String::num_real(h));

		//		float h = input->get_action_strength("a") - input->get_action_strength("d");//movimiento horizontal
		//		Godot::print(String::num_real(v));
		PlayerMouseInput = get_viewport()->get_mouse_position();//posicion de mouse

		PlayerMovementInput = Vector3(h, 0, v);//para obtener el input y luego mover
//		Godot::print(String::num_real(PlayerMouseInput.x));
//		Godot::print(String::num_real(PlayerMouseInput.y));

		CheckJumping();//verifica si esta saltando
		CheckMoving();//verifiva si se mueve
		MovePlayer();//muevo el personaje
		MovePlayerCamera();//muevo la camera

		isWalking = (h != 0 || v != 0);//si es distinto de cero me estoy moviendo
//		anim.SetBool("isWalking", isWalking);//activo animacion caminar

		if (isWalking && !isJumping && !feetSteps->is_playing())//si estoy caminando y no estoy saltando y no se esta reproduciendo el sonido
		{
			//			feetSteps->play();//sonido feetSteps
		}
		else
		{
			//			feetSteps->stop();//sonido feetSteps Stop
		}

		CheckDeathTime();//tiene que ver con el tiempo, capas modifico por tiemr
	}

	void PlayerMovement::_physics_process(const real_t delta)
	{

	}

	//	void PlayerMovement::_input(const Ref<InputEvent> event)
	//	{
	////		PlayerMouseInput = get_viewport()->get_mouse_position();
	//	}

	void PlayerMovement::MovePlayer()
	{
		//		Vector3 MoveVector = transform.TransformDirection(PlayerMovementInput) * Speed;

		Vector3 MoveVector = PlayerMovementInput * Speed;//tiene que ser vector forward posiblemente aca tenga un error

//		PlayerBody.velocity = new Vector3(MoveVector.x, PlayerBody.velocity.y, MoveVector.z);
		set_linear_velocity(Vector3(MoveVector.x, get_linear_velocity().y, MoveVector.z));

		//		if (Input.GetKeyDown(KeyCode.Space))
		if (input->is_action_just_pressed("click_izquierdo"))//para saltar
		{
			if (!isJumping)//sino estoy saltando
			{
				Godot::print("tendria que saltar");
				add_force(Vector3::UP * Jumpforce, Vector3::ZERO);
				//				PlayerBody.AddForce(Vector3.up * Jumpforce, ForceMode.Impulse);
			}
		}
	}

	void PlayerMovement::MovePlayerCamera()
	{
		//		xRot -= PlayerMouseInput.y * Sensitivity;
		xRot = -PlayerMouseInput.y * Sensitivity;

		//		transform.Rotate(0f, PlayerMouseInput.x * Sensitivity, 0f);
		set_rotation_degrees(Vector3(0, -PlayerMouseInput.x * Sensitivity, 0));//rota sobre el eje y el personaje

//		PlayerCamera.transform.localRotation = Quaternion.Euler(xRot, 0f, 0f);
		PlayerCamera->set_rotation_degrees(Vector3(xRot + 45, 0, 0));//para rotar sobre el eje X
	}

	void PlayerMovement::CheckJumping()
	{

	}

	void PlayerMovement::CheckMoving()
	{

	}

	void PlayerMovement::CheckDeathTime()
	{
	}

} /* namespace godot */


