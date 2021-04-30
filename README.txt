README:

FUNCIONAMIENTO:  
	Una vez ejecutado el programa se verifica si el usuario paso una ruta por linea de comando, si no lo hizo se imprime por pantalla un mensaje de error y finaliza el programa.
	Luego se le pregunta al usuario en que formato quiere que se muestren los pokemon, dependiendo de la respuesta se le asignara la funcion correspondiente al puntero a funcion mostrar_pokemon
	Se crea el arrecife con los pokemons del archivo y tambien el acuario vacio, en caso de error el puntero queda apuntando a NULL. Si alguno de los punteros apunta a NULL no se realiza el traslado de pokemons, se libera la memoria de la estructura que se creo con exito y finaliza el programa. Si ningun puntero apunta a NULL (no hubo errores), se realiza el traslado, elegi recorrer el vector de pokemons 2 veces, la primera vez me fijo cuantos pokemons cumplen con las condiciones pedidas y luego si tengo suficientes pokemons para trasladar recorro una segunda vez el vector donde me voy fijando cada pokemon, si cumple con las condiciones lo paso a un vector auxiliar y lo elimino del vector, luego achico el vector (usando realloc); una vez que saque la cantidad pedida agrego los pokemons que me quedaron en el vector auxiliar al acuario. Una vez que termina el traslado se muestra por pantalla el resultado, se guardan los pokemones del acuario en el archivo correspondiente y se libera la memoria para el arrecife y el acuario.

COMPILACION: 
	gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesc
EJECUCION: 
	El programa debe ser ejecutado con la siguiente linea: ./evento_pesca arrecife.txt
	se le debe pasar por linea de comando la ruta a un archivo, en caso contario se activara un mensaje de error.

CONCEPTOS: 
	PUNTEROS:
		Un puntero se define como una variable que almacena una direccion de memoria, los mismos agregan complejidad ya que es el programador quien debe controlar
		su uso. Particularmente en este tp se tienen 2 punteros en el stack donde cada uno guarda la direccion de memoria de 2 estructuras (arrecife_t y acuario_t) en el heap, y a su vez
		esas estructuras tienen un puntero que apunta a un vector de pokemon_t.

	ARITMETICA DE PUNTEROS:
		Los operadores que se utilizan con punteros son, '&' que se usa para acceder a la direccion de memoria de la variable apuntada; luego esta '*' que se utiliza para declarar la variable puntero y ademas para acceder al valor de la variable apuntada.
		Un ejemplo utilizado en el tp es cuando escribo (arrecife->pokemon + 5) donde pokemon es un puntero a un vector de pokemon, le estoy diciendo que vaya a donde apunta el puntero (primer elemento del vector) luego al sumarle 5 estoy avanzando 5 elementos en el vector. Por lo tanto decir arrecife->pokemon[6] es lo mismo que (arrecife->pokemon + 5).

	FUNCIONES A PUNTEROS: 
		Un puntero a una funcion es la direccion de memoria de una funcion en el programa y permite ejecutar la funcion desde cualquier parte del mismo.
		La ventaja que nos da es que por ejemplo en este tp, en vez de hacer 5 funciones para trasladar pokemones con distintos criterios, donde todas tienen la misma logica pero condiciones sobre que pokemons deben ser trasladados distintas, puedo hacer una funcion sola y pasarle el puntero, entonces lo unico que tengo que hacer es ir cambiando a que funcion apunta ese puntero para poder reutilizar esa funcion.

	MALLOC Y REALLOC:
		Malloc es una funcion que reserva una cantidad determinada de bytes en el heap y devuelve un puntero a esa memoria, si no pudo reservar la memoria devolvera NULL
		En el tp se necesita usar malloc para reservar un arrecife_t y un acuario_t en el heap y luego asignarle esa direccion de memoria a un puntero.

		Realloc modifica el tamaño de un bloque de memoria al que apunta un puntero, es decir que se puede agrandar o achicar tantos bytes como lo desee el programador, recibe un puntero a una direccion de memoria y un tamaño de bytes a agrandar. Realloc puede devolver 3 casos. Puede devolver el mismo bloque de memoria agrandado o achicado (funciono bien); puede devolver un bloque de memoria agrandado pero en otra direccion de memoria distinta, es decir que no pudo agrandar el bloque que yo le pase entonces buscó uno que si pudo agrandar, le pasó la informacion del bloque que yo le pase y me devolvio la direccion de memoria de ese bloque. Y finalmente puede devolvernos el bloque que le pasamos sin modificar, es decir que no pudo agrandar el bloque que le pasamos ni pudo encontrar otro para agrandar.
		Si le pasamos un puntero apuntando a NULL Realloc funciona como malloc.


