#include "evento_pesca.h"
#include <stdlib.h>

#define FORMATO_LECTURA "%100[^;];%i;%i;%100[^\n]\n"
#define FORMATO_ESCRITURA "%s;%i;%i;%s\n"
#define MAX_POKEMONES 100
#define LECTURA_CORRECTA 4
#define ERROR -1

#define FOND_VERDE "\e[42m"
#define FOND_CELESTE "\e[46m"
#define AMARILLO "\033[1m\033[33m"
#define RESET "\e[0m"
#define BLANCO "\033[1m\033[37m"

/*
*PRE: recibe un pokemon valido, una cantidad inicializada y un puntero apuntanto a NULL
*POST: devuelve el puntero apuntando a un vector que tiene un pokemon mas que antes
*/
pokemon_t* agregar_pokemon(pokemon_t* pokemones, int* cantidad, pokemon_t pokemon_a_agregar){
	pokemon_t* nuevos_pokemon = realloc(pokemones, sizeof(pokemon_t) * (size_t)(*cantidad));
	if(nuevos_pokemon == NULL){ 
		(*cantidad)--;
		return pokemones;
	}
	pokemones = nuevos_pokemon; 
	*(pokemones + ((*cantidad)-1)) = pokemon_a_agregar; 
	return pokemones; 
}

arrecife_t* crear_arrecife(const char* ruta_archivo){

	FILE* archivo_arrecife = fopen(ruta_archivo, "r");
	if(archivo_arrecife == NULL){
		printf("No se encontro el archivo solicitado\n");
		return NULL;
	}
	arrecife_t* arrecife = malloc(sizeof(arrecife_t));
	if(arrecife == NULL){
		fclose(archivo_arrecife);
		return NULL;
	}

	pokemon_t pokemon_aux;
	arrecife->cantidad_pokemon = 0;
	arrecife->pokemon = NULL;

	int leidos = fscanf(archivo_arrecife, FORMATO_LECTURA, pokemon_aux.especie, &(pokemon_aux.velocidad), &(pokemon_aux.peso), pokemon_aux.color);
	while(leidos == LECTURA_CORRECTA){
		(arrecife->cantidad_pokemon)++;
		arrecife->pokemon = agregar_pokemon(arrecife->pokemon, &(arrecife->cantidad_pokemon), pokemon_aux); 
		leidos = fscanf(archivo_arrecife, FORMATO_LECTURA, pokemon_aux.especie, &(pokemon_aux.velocidad), &(pokemon_aux.peso), pokemon_aux.color);
	}

	fclose(archivo_arrecife);
	if(arrecife->cantidad_pokemon <= 0){
		free(arrecife);
		return NULL;
	}
	return arrecife; 
}

acuario_t* crear_acuario(){
	acuario_t* acuario = malloc(sizeof(acuario_t)); 
	if(acuario == NULL){
		printf("No se pudo crear el acuario\n");
		return NULL;
	}
	acuario->pokemon = NULL; 
	acuario->cantidad_pokemon = 0; 

	return acuario;
}
/*
*PRE: Recibe un puntero a un vector de pokemones valido y la cantidad a agrandar
*POST: Devuelve el puntero a un vector de pokemones que ahora es de tamaño mas chico, si hubo un error devuelve el puntero al vector sin modificaciones
*/
pokemon_t* reducir_arrecife(pokemon_t* pokemones, int cantidad){
	pokemon_t* nuevo_pokemon = realloc(pokemones, sizeof(pokemon_t) * (size_t)(cantidad-1));
	if(nuevo_pokemon == NULL)
		return pokemones;
	pokemones = nuevo_pokemon;
	return pokemones;
}

/*
*PRE: Recibe un puntero a un arrecife valido, un puntero a una funcion de seleccion, la cantidad de pokemons a seleccionar y un vector auxiliar de pokemons
*POST:  el vector de pokemones del arrecife se reduce y el vector auxiliar de pokemones ahora tiene los pokemones que van al acuario
*/
void retirar_pokemones(arrecife_t* arrecife, bool (*seleccionar_pokemon)(pokemon_t*), int cant_seleccion, pokemon_t pokemones_a_trasladar[MAX_POKEMONES]){
	int j = 0, i = 0;
	int cant_trasladados = 0;

	while((i < arrecife->cantidad_pokemon) && (cant_trasladados < cant_seleccion)){
		if(seleccionar_pokemon(arrecife->pokemon + i) == true){
			pokemones_a_trasladar[j] = arrecife->pokemon[i];
			arrecife->pokemon[i] = arrecife->pokemon[arrecife->cantidad_pokemon - 1];
			arrecife->pokemon = reducir_arrecife(arrecife->pokemon, arrecife->cantidad_pokemon);
			(arrecife->cantidad_pokemon)--;
			cant_trasladados++;
			j++;
		}
		else  
			i++;
	}
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){

	int cant_pokemon_validos = 0;

	for(int i = 0; i < arrecife->cantidad_pokemon; i++){ 
		if(seleccionar_pokemon(arrecife->pokemon + i) == true)
			cant_pokemon_validos++;
	}
	if(cant_pokemon_validos >= cant_seleccion){
		pokemon_t pokemones_a_trasladar[MAX_POKEMONES];
		retirar_pokemones(arrecife, seleccionar_pokemon, cant_seleccion, pokemones_a_trasladar); 
		for(int i = 0; i < cant_seleccion; i++){
			(acuario->cantidad_pokemon)++; 
			acuario->pokemon = agregar_pokemon(acuario->pokemon, &(acuario->cantidad_pokemon), pokemones_a_trasladar[i]); 
		}
	}
	else{
		printf("La cantidad de pokemones de esa especie en el arrecife es menor a \nla solicitada, no se pudo realizar el traslado\n");
		printf("=======================================================================================================\n");
		return ERROR; 
	}
	return 0;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
	for(int i = 0; i < arrecife->cantidad_pokemon; i++){
		mostrar_pokemon(arrecife->pokemon + i);
	}
	printf("=======================================================================================================\n");
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo){
	
	FILE* registro_acuario = fopen(nombre_archivo, "w");
	if(nombre_archivo == NULL){
		printf("No se pudo acceder al archivo solicitado\n");
		return ERROR;
	}

	for(int i = 0; i < acuario->cantidad_pokemon; i++){
		fprintf(registro_acuario, FORMATO_ESCRITURA, acuario->pokemon[i].especie, acuario->pokemon[i].velocidad, acuario->pokemon[i].peso, acuario->pokemon[i].color);
	}

	fclose(registro_acuario);
	return 0;
}

void liberar_acuario(acuario_t* acuario){ 
	free(acuario->pokemon);
	free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife){
	if(arrecife->cantidad_pokemon > 0)
		free(arrecife->pokemon);
	free(arrecife);
}
