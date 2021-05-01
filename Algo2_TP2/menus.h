#ifndef _MENUS_H_
#define _MENUS_H_

#include <stdio.h>
#include "juego.h"

/*
*POST: Muestra el menu de inicio por pantalla
*/
void mostrar_menu_inicio();
/*
*PRE: Recibe la ruta del archivo de personaje
*POST: Muestra el menu para ingresar la ruta del personaje por pantalla
*/
void mostrar_ingreso_personaje(char ruta_personaje[MAX_RUTA]);
/*
*PRE: Recibe una tecla, el menu actual y la ruta a un archivo de gimnasios
*POST: Muestra el menu para ingresar la ruta de los gimnasios
*/
void mostrar_opcion_gimnasios(char* tecla, char menu_actual[MAX_NOMBRE], char ruta_gimnasio[MAX_RUTA]);
/*
*PRE: Recibe el nombre del gimnasio actual
*POST: Muestra por pantalla el menu del gimnasio
*/
void mostrar_menu_gimnasio(char nombre_gimnasio[MAX_NOMBRE]);
/*
*PRE: Recibe el gimnasio actual
*POST: Muestra el gimnasio actual por pantalla
*/
void mostrar_gimnasio(gimnasio_t* gimnasio);
/*
*PRE; Recibe 2 pokemons, el id de batalla y el nombre del personaje y el contrincante
*POST: Muestra la batalla por pantalla
*/
void mostrar_batalla(pokemon_t* pkm_personaje, pokemon_t* pkm_contrincante, int id_batalla, char nombre_personaje[MAX_NOMBRE], char nombre_contrincante[MAX_NOMBRE]);
/*
*PRE: Recibe el nombre del entrenador
*POST: Muestra el menu de batalla ganada por pantalla
*/
void mostrar_batalla_ganada(char nombre_entrenador[MAX_NOMBRE]);
/*
*PRE: Recibe el nombre del gimnasio actual y un booleano
*POST: Muestra el menu de victoria por pantalla 
*/
void mostrar_menu_victoria(char nombre_gimnasio[MAX_NOMBRE], bool tome_pokemon);
/*
*POST: Muestra la pantalla de victoria por pantalla una vez que termino la partida
*/
void mostrar_victoria_final();
/*
*PRE: Recibe el nombre del gimnasio actual
*POST: Muestra el menu de derrota por pantalla 
*/
void mostrar_menu_derrota(char nombre_gimnasio[MAX_NOMBRE]);
/*
*POST: Muestra la pantalla de derrota por pantalla una vez que termino la partida
*/
void mostrar_derrota_final(char nombre_gimnasio[MAX_NOMBRE]);
/*
*PRE: Recibe un personaje
*POST: Muestra el personaje por pantalla
*/
void mostrar_personaje(personaje_t* personaje);
/*
*PRE: Recibe 2 listas validas de pokemons
*POST: Muestra los pokemons en las listas por pantalla
*/
void mostrar_pokemons_jugador(lista_t* pokemons_batalla, lista_t* pokemons_obtenidos);
/*
*PRE: Recibe una lista valida de pokemons del lider
*POST: Muestra la lista de pokemons del lider por pantalla
*/
void mostrar_pokemons_lider(lista_t* pokemons_lider);
/*
*POST: Muestra la pantalla de error de carga por pantalla
*/
void mostrar_error_carga();


#endif /* MENUS_H */