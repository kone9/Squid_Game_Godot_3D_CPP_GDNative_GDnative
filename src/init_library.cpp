
// #include "PruebaVisualStudioDebug.h"
// #include "PlayerMovement.h"
// #include "BotAI.h"
// #include "GameManager.h"
// #include "Doll.h"
// #include "MachineGun.h"
#include "PruebaVisualStudioDebug.h"
#include "PlayerMovement.h"
#include "BotAI.h"
#include "GameManager.h"
#include "Doll.h"
#include "MachineGun.h"

using namespace godot;//usamos el espacio de nombres godot sino tenemos varios problemas, no podra explicar mucho esto, pero asi funciona

///////////////////////////////////////////////////
// Las funciones godot_gdnative_init y godot_gdnative_terminate son llamadas
// respectivamente cuando Godot carga nuestro plugin y cuando lo descarga.
// Todo lo que que hacemos aqu� es analizar a trav�s de estas funciones
// en nuestro m�dulo de enlaces para inicializarlo, pero podr�as tener que configurar
// m�s cosas dependiendo de tus necesidades. Por ahora lo dejamos asi sin tocarlo.

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options * o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options * o) {
	Godot::gdnative_terminate(o);
}

//////////////////////////////////////////////////

//-> ESTE ES EL MAS IMPORTANTE METODO PARA REGISTRAR CLASES <- //
extern "C" void GDN_EXPORT godot_nativescript_init(void* handle)
{
	Godot::nativescript_init(handle);//Precauci�n no borrar esto.

	//Registramos todas las clases que creamos aqui abajo
	register_class<PruebaVisualStudioDebug>();//registre la clase HolaMundo
	register_class<PlayerMovement>();//registre la clase HolaMundo
	register_class<BotAI>();//registre la clase HolaMundo
	register_class<GameManager>();//registre la clase HolaMundo
	register_class<Doll>();//registre la clase HolaMundo
	register_class<MachineGun>();//registre la clase MachineGun
	//register_class<YOUCLASE>();//registra tu clase!

}
