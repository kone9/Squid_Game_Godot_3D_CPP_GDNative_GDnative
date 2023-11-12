#include "PruebaVisualStudioDebug.h"
#include "Area.hpp"

namespace godot
{
	//PruebaVisualStudioDebug::PruebaVisualStudioDebug
	//{

	//}

	//PruebaVisualStudioDebug::~PruebaVisualStudioDebug()
	//{
	//}

	void godot::PruebaVisualStudioDebug::_register_methods()
	{
		register_method("_ready", &PruebaVisualStudioDebug::_ready);
		Vector3 hola = Vector3::ZERO;
	}

	void godot::PruebaVisualStudioDebug::_init()
	{
	}

	void godot::PruebaVisualStudioDebug::_ready()
	{

		Godot::print("cambiado texto en linux");
		Godot::print("cambiado texto en linux");
		Godot::print("cambiado texto en linux");
		Godot::print("cambiado texto en linux");

		//Area* newArea = Area::_new();

		//if(!godot_is_instance_valid(newArea)) return;
		//add_child(newArea);
		
		// if(godot_is_instance_valid(newArea))
		// {
		// 	Godot::print(newArea->get_name());
		// }
		// String texto {"AreaGDNative"};
		// newArea->set_name("AreaGDNative");

		int contador = 0;
		// while (contador < 10)
		// {
		// 	Godot::print("tendria que parar la ejecucion en cada vuelta");
		// 	Godot::print("tendria que parar NOW!");
		// 	Godot::print("tendria que parar NOW NOW NOW!");
		// 	contador++;
		// }

	}
}

