# TP.2 - Una aventura Pokemon

## Algoritmos y programación 2, FIUBA, Curso 03 Méndez

### Autor: Mateo Bulnes
---
## 1. Enunciado

Los Alto Mando de todas las regiones se han reunido en una asamblea de carácter urgente: Los líderes regionales están
notando una preocupante caída de interés por parte de los jóvenes en convertirse en maestros Pokémon. Debido a las
nuevas tecnologías, el interés por los nuevos videojuegos ha aumentado rotundamente, con títulos como 'PacMon' y
'Mankey Kong' que han cautivado a miles de niños y niñas en todo el mundo, han provocado que cada día hayan menos
niñxs jugando afuera con los pokémon y comenzando su camino como maestro Pokémon.
Es por esto que te han contactado para que lleves a cabo el primer videojuego de aventura sobre convertirse en
maestro pokémon.
El objetivo del videojuego es simular el camino que se realiza para convertirse en maestro Pokémon. Para esto, es necesario
obtener todas y cada una de las medallas de la región, comenzando con los gimnasios más sencillos y avanzando hacia
los más difíciles.

## 2. Objetivo

El presente trabajo práctico tiene como finalidad que el alumno se familiarice con las diferentes estructuras de datos
dinámicas implementadas, aplicándolas a un problema concreto y poniendo en práctica su uso integrado.

## 2. Archivos

El trabajo práctico consiste de los siguientes archivos:

- aventura_pokemon.c
- batallas.h 
- batallas.c
- juego.h
- juego.c
- menus.h
- menus.c
- heap.h
- heap.c
- lista.h
- lista.c
- personaje.txt
- gimnasios.txt
- Tp2-aventura_pokemon.pdf
- README

## 3. Compilación y ejecución

El trabajo práctico deberá ser compilado con la siguiente linea: 
`gcc *.c -o juego -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0`

Y chequear memoria y ejecución con la siguiente linea:
`valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./juego`

## 4. Explicación del TP

El trabajo consiste en un videojuego donde se simula la aventura de un entrenador pokemon, el objetivo es derrotar todos los gimnasios y convertirse en maestro pokemon.
Para comenzar el juego, el usuario deberá ingresar el nombre de los archivos de texto que contienen la información para el personaje principal (personaje.txt) y el de los gimnasios (gimnasios.txt). Al ingresar estos archivos se crean las siguientes estructuras: 

1. juego_t
<blockquote>Es la estructura principal del juego, contiene un heap_t que contiene a los gimnasios leídos del archivo, y un personaje_t con la información del personaje principal leída de personaje.txt
</blockquote>

2. personaje_t
<blockquote>
Estructura del personaje principal con el que jugará el usuario. Contiene un string con el nombre del personaje y 2 punteros a  listas simplemente enlazadas donde, una contiene los 6 pokemons que se utilizaran en las batallas, y la otra lista contiene el resto de los pokemons guardados para futuros cambios en la lista de batalla.
</blockquote>

3. heap_t
<blockquote>
Esta estructura es un heap de gimnasios que almacena los gimnasios leídos en el archivo. La implementación corresponde a la de un heap minimal, donde los gimnasios están ordenados por dificultad. Se utiliza el TDA heap ya que facilita la eliminación del gimnasio una vez que el usuario ya lo ha derrotado.
</blockquote>

4. gimnasio_t
<blockquote>
Estructura de un gimnasio, consiste de: 

- Nombre del gimnasio
- Puntero a una lista simplemente enlazada de entrenadores (entrenador_t)
- dificultad (representada en int)
- id de batalla (para identificar el tipo de batalla del gimnasio)
</blockquote>

5. entrenador_t
<blockquote>
Estructura de un entrenador pokemon (rival), consiste de: 

- Nombre del entrenador
- Puntero a una lista simplemente enlazada que contiene a los pokemons del entrenador
</blockquote>

6. pokemon_t
<blockquote>
Estructura de un pokemon. Contiene sus atributos, es decir, Velocidad, Ataque, Defensa, Elemento, Nombre, y la cantidad de mejoras que recibió
</blockquote>
