#include "PruebaVisualStudioDebug.h"

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
		int contador = 0;
		while (contador < 10)
		{
			Godot::print("tendria que parar la ejecucion en cada vuelta");
			Godot::print("tendria que parar NOW!");
			Godot::print("tendria que parar NOW NOW NOW!");
			contador++;
		}

	}
}

