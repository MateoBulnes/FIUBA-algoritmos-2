# GRAN PESCA POKEMON
## Algoritmos y programación 2, FIUBA, Curso 03 Méndez
### Autor: Mateo Bulnes

## 1. Introducción
Los pokémon son unas criaturas que se encuentran en la naturaleza. Se clasifican en 18 tipos (planta, fuego, agua,
volador, tierra, etc). Cada pokémon tiene una cantidad determinada de movimientos o ataques que puede aprender, los
cuales se pueden clasificar por su tipo o elemento (por ejemplo, el ataque rayo burbuja es un ataque tipo agua). Además,
los pokémon cuentan con diferentes atributos que los distinguen de otros pokémon de la misma especie: Velocidad, Color,
Peso, entre otros.
Los entrenadores pokémon, tienen como meta cumplir dos objetivos: capturar a todas las especies de pokémon disponibles
y completar así la información de todos los pokémon en la Pokédex (Enciclopedia Pokémon). Por otro lado,
deben entrenarlos y enfrentarlos a pokémones pertenecientes a otros entrenadores para demostrar sus habilidades,
fortalezas, talentos y así convertirse en un Maestro Pokémon.
Para cumplir la primer meta, los entrenadores viajan a lo largo y ancho de las regiones del mundo, capturando los
diferentes pokémon que encuentran en su camino. Hoy los entrenadores se encontrarán con la oportunidad de capturar
pokémon de tipo agua de una manera distinta a la usual...

## 2. Objetivos
El presente trabajo tiene como finalidad que el alumno repase algunos de los conocimientos adquiridos en Algoritmos y
Programación I, así como también que comience a familiarizarse con las herramientas a utilizar a lo largo de la materia,
tales como el manejo de memoria dinámica y la utilización de punteros a funciones.

## 3. Enunciado
La líder de gimnasio Misty organizó un evento de pesca que se llevará a cabo en su acuario, ubicado en Ciudad Celeste.
Para ello necesitará muchos y muy variados pokémon de tipo agua. El lugar indicado en Kanto para obtener a todos
estos pokémon es el arrecife que rodea a las Islas Espuma.
Para realizarlo, te pide que la ayudes a trasladar los pokémon seleccionados desde el arrecife a su acuario, donde será
realizado el evento.
A Misty le preocupa perjudicar la población de las especies más vulnerables, es por ello que te pide realizar una simulación
del arrecife, pudiendo ver como quedará su estado dependiendo de qué especies se elijan para el evento.

## 4. Archivos
- evento_pesca.h
- evento_pesca.c
- main.c
- arrecife.txt
- enunciado_Tp1_eventopesca.pdf
- README.md

## 5. Resultado esperado
Se espera que el trabajo compile con la siguiente linea: 

`gcc *.c -Wall -Wconversion -Werror -std=c99 -o evento_pesca` 

Y sea corrido con valgrind: 

`valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca arrecife.txt`

## 6. Ejercitación Teórica
Explique brevemente y de forma concisa los siguientes conceptos:

**a**. Punteros:

Un puntero se define como una variable que almacena una direccion de memoria, los mismos agregan complejidad ya que es el programador quien debe controlar
		su uso. Particularmente en este tp se tienen 2 punteros en el stack donde cada uno guarda la direccion de memoria de 2 estructuras (arrecife_t y acuario_t) en el heap, y a su vez
		esas estructuras tienen un puntero que apunta a un vector de pokemon_t.

**b**. Aritmética de punteros:

Los operadores que se utilizan con punteros son, '&' que se usa para acceder a la dirección de memoria de la variable apuntada; luego, está '*' que se utiliza para declarar la variable puntero y además para acceder al valor de la variable apuntada.
		Un ejemplo utilizado en el tp es cuando escribo (arrecife->pokemon + 5) donde pokemon es un puntero a un vector de pokemon, le estoy diciendo que vaya a donde apunta el puntero (primer elemento del vector) luego al sumarle 5 estoy avanzando 5 elementos en el vector. Por lo tanto decir arrecife->pokemon[6] es lo mismo que (arrecife->pokemon + 5). 

**c**. Punteros a funciones:
  
Un puntero a función es un puntero que almacena la dirección de memoria de una función y se puede usar para invocarla.
		La ventaja que nos da es que por ejemplo en este tp, en vez de hacer 5 funciones para trasladar pokemones con distintos criterios, donde todas tienen la misma lógica pero condiciones sobre que pokemons deben ser trasladados distintas, puedo hacer una función sola y pasarle el puntero, entonces lo único que tengo que hacer es ir cambiando a que función apunta ese puntero para poder reutilizar esa función.

**d**. Malloc y Realloc:

 Malloc es una función que reserva una cantidad determinada de bytes en el heap y devuelve un puntero a esa memoria, si no pudo reservar la memoria devolverá NULL

Realloc modifica el tamaño de un bloque de memoria al que apunta un puntero, es decir que se puede agrandar o achicar tantos bytes como lo desee el programador, recibe un puntero a una dirección de memoria y la cantidad total de bytes que tiene que tener el bloque después de la operación. Realloc puede devolver 3 casos. Puede devolver el mismo bloque de memoria agrandado o achicado (funciono bien); puede devolver un bloque de memoria agrandado pero en otra dirección de memoria distinta, es decir que no pudo agrandar el bloque que yo le pase entonces buscó uno que si pudo agrandar, le pasó la información del bloque que yo le pase y me devolvió la dirección de memoria de ese bloque. Y finalmente puede devolvernos NULL, es decir que no pudo agrandar el bloque que le pasamos ni pudo encontrar otro para agrandar.


		
