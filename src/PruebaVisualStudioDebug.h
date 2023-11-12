
#pragma once
#ifndef PRUEBAVISUALSTUDIODEBUG_H//nose si sea necesario, pero esto lo saque de los ejemplos lo dejo por las dudas, asi funciona
#define PRUEBAVISUALSTUDIODEBUG_H//nose si sea necesario, pero esto lo saque de los ejemplos lo dejo por las dudas, asi funciona


#include <Godot.hpp>
#include <Node.hpp>
namespace godot {
    class PruebaVisualStudioDebug : public Node
    {
    private:
        GODOT_CLASS(PruebaVisualStudioDebug, Node)

    public:
        //metodo contructor, ojo no se llama directo, usar init()
        //PruebaVisualStudioDebug();
        //metodo destructor, ni idea como funciona en godot, pero lo declaramos por las dudas aunque no lo usemos
       // ~PruebaVisualStudioDebug();
        //Para hacer la magia de usar Godot Engine con C++ y Gdnative hay que registrar metodos y propiedades con este metodo... //IMPORTANTE tenemos que registrar los metodos sino godot no los detecta, a veces al registrar las propiedades para que se vean en el editor no se cargan, si pasa eso, reinicia el editor
        static void _register_methods();


        //metodo init no es el ready.PRECAUCION: si llamas a los nodos desde aca vas a tener punteros colgados y se va a cerrar la aplicacion. Se puede usar para definir cosas, pero en las practicas que yo hice no pude buscar nodos desde aca. "Es llamada una vez que Godot ha creado nuestro objeto adecuadamente"..Este método no se registra y es obligatorio que este en todas las clases 
        void _init();
        //metodo ready de godot, desde aca podes llamar a los nodos cuando se carganla escena, se ejecuta una sola vez.. Este metodo tiene que estar registrado
        void _ready();
    };
}

#endif