#include "batallas.h"
#include "juego.h"

const char FUEGO = 'F', AGUA = 'A', TIERRA = 'T', VIENTO = 'V', ELECTRICIDAD = 'E';
#define PKM_1 1
#define PKM_2 -1



//teniendo en cuenta que pkm_1 es el del personaje, y pkm_2 es el del contrincante

//FUNCION 1 ---> GANA EL POKEMON CON MAYOR PROMEDIO DE ATRIBUTOS
/*
*PRE: Recibe un puntero a un pokemon
*POST: Devuelve el promedio entre los 3 atributos del pokemon
*/
int promedio_atributos(void* pkm){
	return(((*(pokemon_t*)pkm).velocidad + (*(pokemon_t*)pkm).defensa + (*(pokemon_t*)pkm).ataque) / 3);
}

int funcion_batalla_1(void* pkm_1, void* pkm_2){
	if(promedio_atributos(pkm_1) >= promedio_atributos(pkm_2))
		return PKM_1;
	return PKM_2;
}
// FUNCION 2 ---> GANA EL POKEMON QUE TENGA ELEMENTO ELEMENTAL, EN CASO DE QUE AMBOS LO SEAN, SE RESUELVE CON LA TABLA DE ELEMENTOS
/*
*PRE: Recibe un caracter representando un elemento
*POST: Devuelve true si el elemento es elemental, y false en caso contrario
*/
bool es_elemental(char elemento){ //Los pokemons elementales son --> fuego / agua / tierra / viento / electricidad
	return(elemento == FUEGO || elemento == AGUA || elemento == TIERRA || elemento == VIENTO || elemento == ELECTRICIDAD);
}
/*
*PRE: Recibe 2 elementos
*POST: Devuelve true si el elemento 1 es ganador, en caso contrario devuelve false
*/
bool gano_elemento_1(char elemento_1, char elemento_2){
	return((elemento_1 == FUEGO && elemento_2 == TIERRA) || (elemento_1 == TIERRA && elemento_2 == VIENTO) || (elemento_1 == VIENTO && elemento_2 == ELECTRICIDAD) || (elemento_1 == ELECTRICIDAD && elemento_2 == AGUA) || (elemento_1 == AGUA && elemento_2 == FUEGO) ||  (elemento_1 == elemento_2));
}
/*
*PRE: Recibe 2 elementos
*POST: Devuelve 1 si el elemento 1 gano, caso contrario devuelve -1
*/
int ganador_por_tabla_elementos(char elemento_1, char elemento_2){
	if(gano_elemento_1(elemento_1, elemento_2))
		return PKM_1;
	else
		return PKM_2;

}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
	if(es_elemental((*(pokemon_t*)pkm_1).elemento) && !es_elemental((*(pokemon_t*)pkm_2).elemento))
		return PKM_1;
	else if(!es_elemental((*(pokemon_t*)pkm_1).elemento) && es_elemental((*(pokemon_t*)pkm_2).elemento))
		return PKM_2;
	else if(!es_elemental((*(pokemon_t*)pkm_1).elemento) && !es_elemental((*(pokemon_t*)pkm_2).elemento))
		return PKM_1;
	else
		return(ganador_por_tabla_elementos((*(pokemon_t*)pkm_1).elemento, (*(pokemon_t*)pkm_2).elemento));
}

// FUNCION 3 ---> GANA EL POKEMON MAS AGRESIVO, ES DECIR, EL QUE TENGA MAYOR VELOCIDAD Y ATAQUE
/*
*PRE: Recibe 2 punteros a pokemons
*POST: Devuelve true si el pokemon 1 es mas agresivo, y false si no lo es
*/
bool es_pokemon_agresivo(void* pkm_1, void* pkm_2){
	return(((*(pokemon_t*)pkm_1).velocidad >= (*(pokemon_t*)pkm_2).velocidad) && ((*(pokemon_t*)pkm_1).ataque >= (*(pokemon_t*)pkm_2).ataque));
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
	if(es_pokemon_agresivo(pkm_1, pkm_2))
		return PKM_1;
	return PKM_2;
}
// FUNCION 4 ---> GANA EL POKEMON CUYO NOMBRE TENGA DE INICIAL UNA VOCAL, SI AMBOS CUMPLEN ESTO, SE SOLUCIONA POR ORDEN ALFABETICO
/*
*PRE: Recibe el nombre de un pokemon
*POST: Devuelve true si la inicial del nombre es una vocal, en caso contrario devuelve false
*/
bool inicial_es_vocal(char nombre_pkm[MAX_NOMBRE]){
	return(nombre_pkm[0] == 'A' || nombre_pkm[0] == 'E' || nombre_pkm[0] == 'I' || nombre_pkm[0] == 'O' || nombre_pkm[0] == 'U');
}
/*
*PRE: Recibe 2 iniciales
*POST: Devuelve 1 si la inicial 1 es menor o igual, y -1 si la inicial 2 es menor
*/
int mayor_vocal(char inicial_1, char inicial_2){
	if(inicial_1 <= inicial_2)
		return PKM_1;
	return PKM_2;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
	if(inicial_es_vocal((*(pokemon_t*)pkm_1).nombre) && !inicial_es_vocal((*(pokemon_t*)pkm_2).nombre))
		return 1;
	else if(inicial_es_vocal((*(pokemon_t*)pkm_1).nombre) && inicial_es_vocal((*(pokemon_t*)pkm_2).nombre)){
		int ganador = mayor_vocal((*(pokemon_t*)pkm_1).nombre[0], (*(pokemon_t*)pkm_2).nombre[0]);
		return ganador;
	}
	else
		return PKM_1;
}

// FUNCION 5 ---> GANA EL POKEMON MAS DEFENSIVO, ES DECIR, EL POKEMON CON MENOR VELOCIDAD Y MAYOR DEFENSA
/*
PRE: Recibe 2 punteros a pokemons
POST: Devuelve true si el pokemon 1 es mas defensivo, en caso contrario devuelve false
*/
bool es_pokemon_defensivo(void* pkm_1, void* pkm_2){
	return(((*(pokemon_t*)pkm_1).velocidad <= (*(pokemon_t*)pkm_2).velocidad) && ((*(pokemon_t*)pkm_1).defensa >= (*(pokemon_t*)pkm_2).defensa));
}
int funcion_batalla_5(void* pkm_1, void* pkm_2){
	if(es_pokemon_defensivo(pkm_1, pkm_2))
		return PKM_1;
	return PKM_2;

}