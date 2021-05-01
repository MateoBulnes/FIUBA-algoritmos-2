#ifndef _JUEGO_H_
#define _JUEGO_H_

#include <string.h>
#include <stdbool.h>
#include "lista.h"
#include "heap.h"
#include "batallas.h"


#define MAX_NOMBRE 100
#define MAX_ELEMENTOS 50
#define MAX_RUTA 50

#define AMARILLO "\033[1m\033[33m"
#define BLANCO "\033[1m\033[37m"
#define NEGRO "\033[0m\033[30m"
#define ROJO "\033[1m\033[31m"
#define AZUL "\033[1m\033[34m"
#define CELESTE "\033[1m\033[36m"
#define VERDE "\033[1m\033[32m"
#define MARRON "\033[0m\033[33m"
#define FOND_ROJO "\x1B[41m"
#define FOND_BLANCO "\x1B[47m"
#define FOND_AMARILLO "\x1B[43m"
#define RARO "\x1B[0;103m"
#define RESET "\x1B[0m"

typedef struct pokemon{
	int velocidad;
	int defensa;
	int ataque;
	char nombre[MAX_NOMBRE];
	char elemento;
	int cant_mejoras;
} pokemon_t;

typedef struct entrenador{
	lista_t* pokemons; 
	char nombre[MAX_NOMBRE];
} entrenador_t;

typedef struct gimnasio{
	char nombre[MAX_NOMBRE];
	lista_t* entrenadores; 
	int dificultad;
	int id_batalla;
} gimnasio_t;

typedef struct personaje{
	char nombre[MAX_NOMBRE];
	lista_t* pokemons_batalla;
	lista_t* pokemons_obtenidos;
} personaje_t;

typedef struct juego{
	heap_t* gimnasios;
	personaje_t* personaje;
} juego_t;

/*
*PRE: recibe una caracter(tecla presionada) y un string 
*POST: Devuelve true si la tecla es valida (dependiendo del string) y false si la tecla no es valida
*/
bool es_tecla_valida(char tecla, char menu_actual[MAX_NOMBRE]);

/*
*PRE: Recibe un heap inicializado y la ruta del archivo a cargar
*POST: Devuelve 0 si se pudo cargar el gimnasio con exito. Devuelve -1 en caso de error
*/
int cargar_gimnasios(heap_t* grupo_gimnasios, char* ruta_archivo);

/*
*PRE: Recibe la ruta del archvio a cargar
*POST: Devuelve un personaje con todos sus campos cargados. En caso de error devuelve NULL
*/
personaje_t* cargar_personaje(char* ruta_archivo);

/*
*PRE: Recibe un personaje valido e inicializado
*POST: Libera toda la memoria reservada para el personaje
*/
void destruir_personaje(personaje_t* personaje);

/*
*PRE: Recibe un juego sin inicializar
*POST: Inicializa el juego y sus campos
*/
void inicializar_juego(juego_t* juego);

/*
*PRE: Recibe 2 listas validas de pokemons
*POST: Realiza el cambio de elementos entre las listas
*/
void cambiar_pokemons(lista_t* pokemons_batalla, lista_t* pokemons_obtenidos);

/*
*PRE: recibe un personaje inicializado, una pila de entrenadores inicializados, el id de la batalla y un booleano
*POST: Devuelve 0 Si la batalla fue ganada, en caso contrario devolvera -1
*/
int batallar(personaje_t* personaje, lista_t* entrenadores, int id_batalla, bool simulando);

/*
*PRE: Recibe un entrenador inicializado y una lista valida de pokemons
*POST: Agrega 1 pokemon a la lista
*/
void tomar_pokemon(entrenador_t* lider, lista_t* pokemons_obtenidos);

/*
*PRE: Recibe un juego inicializado, un string, la tecla presionada y 3 booleanos
*POST: Realiza la accion correspondiente al menu en el que se este jugando
*/
void determinar_accion(juego_t* juego, char menu_actual[MAX_NOMBRE], char tecla, bool* finalizo_partida, bool* cargue_personaje, bool* simulando);

#endif /* JUEGO_H */