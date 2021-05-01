#include "menus.h"

#define MAX_ENTRENADORES 10
#define MAX_POKEMON 50
const char GIMNASIO = 'G', ENTRENADOR = 'E', LIDER = 'L', POKEMON = 'P';
const char CARGAR_PERSONAJE = 'E', CARGAR_GIMNASIOS = 'A', INICIAR = 'I', SIMULAR = 'S', ARCHIVO_UNICO = 'U', MULTIPLES_ARCHIVOS = 'M';
const char MOSTRAR_PERSONAJE = 'E', MOSTRAR_GIMNASIO = 'G', CAMBIAR_POKEMON = 'C', BATALLAR = 'B';
const char SIGUIENTE = 'N', TOMAR_POKEMON = 'T', REINTENTAR = 'R', FINALIZAR = 'F';
#define FORMATO_LECTURA_GIMNASIO "%[^;];%i;%i\n"
#define FORMATO_LECTURA_ENTRENADOR "%[^\n]\n"
#define FORMATO_LECTURA_POKEMON "%[^;];%i;%i;%i\n"
#define EXITO 0
#define ERROR -1
#define PKM_PERSONAJE 1
#define PKM_RIVAL -1
#define MAX_PUNTOS_EXTRA 63
#define GANO 0
#define PERDIO -1

//CARGAR GIMNASIOS
/*
*PRE: Recibe una letra representando el tipo de dato a leer
*POST: Devuelve true si la letra es valida y false si no lo es
*/
bool es_dato_valido(char letra){
	return((letra == GIMNASIO) || (letra == ENTRENADOR) || (letra == LIDER) || (letra == POKEMON));
}
/*
*PRE: Recibe 2 caracteres, el primero es el tipo de dato recien leido, y el segundo el que se leyo antes
*POST: Devuelve true si encontre un entrenador sin pokemons y false si no lo encontre
*/
bool encontre_entrenador_vacio(char tipo_dato_actual, char tipo_dato_anterior){
	return((tipo_dato_anterior == LIDER && tipo_dato_actual == ENTRENADOR) || (tipo_dato_anterior == ENTRENADOR && tipo_dato_actual == ENTRENADOR));
}
/*
*PRE: Recibe 2 caracteres, el primero es el tipo de dato recien leido, y el segundo el que se leyo antes
*POST: Devuelve true si encontre un gimnasio sin entrenadores ni pokemons, y false si no lo encontre 
*/
bool encontre_gimnasio_vacio(char tipo_dato_actual, char tipo_dato_anterior){
	return(tipo_dato_actual == GIMNASIO && tipo_dato_anterior == GIMNASIO);
}
/*
*PRE: Recibe 2 pokemons validos
*POST: Devuelve true si los pokemons son iguales, y false si no lo son
*/
bool es_pokemon_repetido(pokemon_t* ultimo_pokemon, pokemon_t* pokemon_leido){
	return(ultimo_pokemon == pokemon_leido);
}
/*
*PRE: Recibe el gimnasio, entrenador y pokemon actual, el tipo de dato y leidos
*POST: Libera la mayor cantidad de memoria reservada posible, dependiendo del caso (tipo de dato)
*/
void accion_por_fallo(gimnasio_t* gimnasio, entrenador_t* entrenador, pokemon_t* pokemon, char tipo_dato, int* leidos){
	
	if(tipo_dato == ENTRENADOR || tipo_dato == LIDER){
		if(pokemon && !es_pokemon_repetido((pokemon_t*)(*(entrenador_t*)gimnasio->entrenadores->nodo_fin->elemento).pokemons->nodo_fin->elemento, pokemon)) 
			free(pokemon); 

		if(entrenador){
			if(entrenador->pokemons)
				lista_destruir(entrenador->pokemons);
			free(entrenador); 
		}

		nodo_t* aux = gimnasio->entrenadores->nodo_inicio;
		size_t cant_entrenadores = lista_elementos(gimnasio->entrenadores);
		while(cant_entrenadores > 0){
			if((*(entrenador_t*)aux->elemento).pokemons)
				lista_destruir((*(entrenador_t*)aux->elemento).pokemons);
			aux = aux->siguiente;
			cant_entrenadores--;
		} 
	}

	lista_destruir(gimnasio->entrenadores);
	free(gimnasio);
	*leidos = -1;
}
/*
*PRE: Recibe un archivo abierto para lectura, y un entrenador sin inicializar
*POST: Devuelve la cantidad de elementos leidos en la linea del archivo
*/
int leer_entrenador(FILE* archivo_gimnasio, entrenador_t* entrenador_leido){
	return(fscanf(archivo_gimnasio, FORMATO_LECTURA_ENTRENADOR, entrenador_leido->nombre));
}
/*
*PRE: Recibe un archivo abierto para lectura y la variable leidos
*POST: Devuelve un entrenador inicializado con todos sus campos
*/
entrenador_t* crear_entrenador(FILE* archivo_gimnasio, int* leidos){
	entrenador_t* entrenador = malloc(sizeof(entrenador_t)); 
	if(!entrenador){
		fclose(archivo_gimnasio);
		return NULL;
	}
	*leidos = leer_entrenador(archivo_gimnasio, entrenador);
	entrenador->pokemons = lista_crear();
	return entrenador;
}
/*
*POST: Devuelve un elemento al azar
*/
char asignar_elemento(){
	char elementos[MAX_ELEMENTOS] = {'F', 'A', 'T', 'V', 'E', 'N', 'B', 'H', 'P'};
	int pos = rand() % 9;
	return elementos[pos];
}
/*
*PRE: Recibe un archivo abierto para lectura, y un pokemon sin inicializar
*POST: Devuelve la cantidad de elementos leidos en la linea del archivo
*/
int leer_pokemon(FILE* archivo_gimnasio, pokemon_t* pokemon_leido){
	return(fscanf(archivo_gimnasio, FORMATO_LECTURA_POKEMON, pokemon_leido->nombre, &(pokemon_leido->velocidad), &(pokemon_leido->ataque), &(pokemon_leido->defensa)));
}
/*
*PRE: Recibe un archivo abierto para lectura y la variable leidos
*POST: Devuelve un pokemon inicializado en todos sus campos
*/
pokemon_t* crear_pokemon(FILE* archivo, int* leidos){
	pokemon_t* pokemon = calloc(1, sizeof(pokemon_t));
	if(!pokemon){
		fclose(archivo);
		return NULL;
	}
	*leidos = leer_pokemon(archivo, pokemon);
	pokemon->elemento = asignar_elemento();
	
	return pokemon;
}
/*
*PRE: Recibe un archivo abierto para lectura, un gimnasio sin inicializar, un booleano y un caracter indicando el tipo de dato
*POST: Devuelve la cantidad de elementos leidos en la linea del archivo
*/
int leer_gimnasio(FILE* archivo_gimnasio, gimnasio_t* gimnasio_leido, bool* es_primer_gimnasio, char* tipo_dato){
	if(*es_primer_gimnasio){
		*es_primer_gimnasio = false;
		return(fscanf(archivo_gimnasio, "%c;%[^;];%i;%i\n", tipo_dato, gimnasio_leido->nombre, &(gimnasio_leido->dificultad), &(gimnasio_leido->id_batalla)));
	}
	return(fscanf(archivo_gimnasio, FORMATO_LECTURA_GIMNASIO, gimnasio_leido->nombre, &(gimnasio_leido->dificultad), &(gimnasio_leido->id_batalla)));
}
/*
*PRE: Recibe un archivo abierto para lectura, la variable leidos, un booleando y un caracter
*POST: Devuelve un gimnasio con todos sus campos inicializados
*/
gimnasio_t* crear_gimnasio(FILE* archivo_gimnasio, int* leidos, bool* es_primer_gimnasio, char* tipo_dato){
	gimnasio_t* gimnasio = calloc(1, sizeof(gimnasio_t)); // Luego reservo memoria para un nuevo gimnasio y lo leo creando tambien su lista de entrenadores
	if(!gimnasio){
		fclose(archivo_gimnasio);
		return NULL;
	}
	*leidos = leer_gimnasio(archivo_gimnasio, gimnasio, es_primer_gimnasio, tipo_dato);
	gimnasio->entrenadores = lista_crear();
	if(gimnasio->id_batalla > 5 || gimnasio->id_batalla <= 0)
		gimnasio->id_batalla = rand() % 6;
	return gimnasio;
}
/*
*PRE: Recibe un archivo abierto para lectura y un caracter
*POST: Devuelve la cantidad de elementos que se leyeron
*/
int leer_tipo_dato(FILE* archivo, char* tipo_dato){
	return(fscanf(archivo, "%c;", tipo_dato));
}

int cargar_gimnasios(heap_t* grupo_gimnasios, char* ruta_archivo){
	FILE* archivo_gimnasio = fopen(ruta_archivo, "r");
	if(!archivo_gimnasio)
		return ERROR;

	char tipo_dato = GIMNASIO, tipo_dato_anterior = GIMNASIO;
	int cant_pok_leidos = 0, leidos = 0;
	bool fallo = false, es_primer_gimnasio = true, hay_gyms_cargados = false;
	
	entrenador_t* entrenador_leido = NULL;
	pokemon_t* pokemon_leido = NULL;
	pokemon_t pkm_salteado;
	gimnasio_t* gimnasio_leido = crear_gimnasio(archivo_gimnasio, &leidos, &es_primer_gimnasio, &tipo_dato);
	
	if(leidos > 0 && es_dato_valido(tipo_dato)){
		while(leidos > 0 && es_dato_valido(tipo_dato)){
			leidos = leer_tipo_dato(archivo_gimnasio, &tipo_dato);
			
			if(tipo_dato == GIMNASIO){ 
				if(!encontre_gimnasio_vacio(tipo_dato, tipo_dato_anterior)){
					lista_apilar(gimnasio_leido->entrenadores, entrenador_leido); 
					heap_insertar(grupo_gimnasios, gimnasio_leido);
					cant_pok_leidos = 0;
					gimnasio_leido = crear_gimnasio(archivo_gimnasio, &leidos, &es_primer_gimnasio, &tipo_dato);
				}
				else{
					accion_por_fallo(gimnasio_leido, entrenador_leido, pokemon_leido, tipo_dato, &leidos);
					fallo = true;
					if(grupo_gimnasios->tope > 0)
						hay_gyms_cargados = true;
				}
			}

			else if(tipo_dato == ENTRENADOR || tipo_dato == LIDER){
				if(!encontre_entrenador_vacio(tipo_dato, tipo_dato_anterior)){ 
					if(cant_pok_leidos > 0)
						lista_apilar(gimnasio_leido->entrenadores, entrenador_leido); 
					entrenador_leido = crear_entrenador(archivo_gimnasio, &leidos);
					cant_pok_leidos = 0;
				}
				else{
					accion_por_fallo(gimnasio_leido, entrenador_leido, pokemon_leido, tipo_dato, &leidos);
					fallo = true;
				}
			}

			else if((tipo_dato == POKEMON) && (leidos > 0)){ 
				if(cant_pok_leidos < 6){
					pokemon_leido = crear_pokemon(archivo_gimnasio, &leidos);
					lista_insertar(entrenador_leido->pokemons, pokemon_leido); 
					cant_pok_leidos++;
				}
				else
					leidos = leer_pokemon(archivo_gimnasio, &pkm_salteado);
			}

			else if(leidos <= 0 && !fallo){ 
				lista_apilar(gimnasio_leido->entrenadores, entrenador_leido); 
				heap_insertar(grupo_gimnasios, gimnasio_leido);
			}

			tipo_dato_anterior = tipo_dato;
		}

		if(!es_dato_valido(tipo_dato)){
			accion_por_fallo(gimnasio_leido, entrenador_leido, pokemon_leido, tipo_dato, &leidos);
			fallo = true;
		}
	}
	else{ 
		accion_por_fallo(gimnasio_leido, entrenador_leido, pokemon_leido, tipo_dato, &leidos);
		fallo = true;
	}
	fclose(archivo_gimnasio);

	if(fallo && !hay_gyms_cargados)
		return ERROR;
	return EXITO;
}
// DESTRUIR PERSONAJE
/*
*PRE: Recibe una lista de pokemons valida
*POST: Libera la memoria reservada para la lista
*/
void destruir_pokemons_batalla(lista_t* pokemons_batalla){ // los elementos (pokemons) de esta lista ya fueron liberados cuando destrui la otra, entonces solo libero los 6 nodos (siempre 6)
	for(int i = 0; i < 6; i++){
		lista_borrar(pokemons_batalla);
	}
	free(pokemons_batalla);
}

void destruir_personaje(personaje_t* personaje){
	lista_destruir(personaje->pokemons_obtenidos);
	destruir_pokemons_batalla(personaje->pokemons_batalla);
	free(personaje);
}

// CARGAR PERSONAJE
/*
*POST: Devuelve un personaje con todos sus campos inicializados
*/
personaje_t* crear_personaje(){
	personaje_t* personaje = calloc(1, sizeof(personaje_t));
	if(!personaje){
		return NULL;
	}
	personaje->pokemons_batalla = lista_crear();
	personaje->pokemons_obtenidos = lista_crear();

	return personaje;
}
/*
*PRE: Recibe un archivo abierto para lectura, un personaje y un caracter
*POST: Devuelve la cantidad de elementos que se leyeron
*/
int leer_personaje(FILE* archivo_personaje, personaje_t* personaje_leido, char* tipo_dato){
	return(fscanf(archivo_personaje, "%c;%[^\n]\n", tipo_dato, personaje_leido->nombre));
}
personaje_t* cargar_personaje(char* ruta_archivo){
	FILE* archivo_personaje = fopen(ruta_archivo, "r");
	if(!archivo_personaje)
		return NULL;

	personaje_t* personaje_leido = crear_personaje();
	pokemon_t* pokemon_leido = NULL;
	int cant_pokemons_leidos = 0;

	char tipo_dato;
	int leidos = leer_personaje(archivo_personaje, personaje_leido, &tipo_dato);

	if(leidos > 0 && es_dato_valido(tipo_dato)){
		while(leidos > 0 && es_dato_valido(tipo_dato)){
			leidos = leer_tipo_dato(archivo_personaje, &tipo_dato);
			if(leidos > 0 && es_dato_valido(tipo_dato)){
				pokemon_leido = crear_pokemon(archivo_personaje, &leidos);
				if(cant_pokemons_leidos < 6){
					lista_insertar(personaje_leido->pokemons_batalla, pokemon_leido);
					lista_insertar(personaje_leido->pokemons_obtenidos, pokemon_leido);
				}
				else if(cant_pokemons_leidos >= 6)
					lista_insertar(personaje_leido->pokemons_obtenidos, pokemon_leido);
				cant_pokemons_leidos++;
			}
		}
	}
	if((leidos <= 0 || !es_dato_valido(tipo_dato)) && !pokemon_leido)
		destruir_personaje(personaje_leido);
	fclose(archivo_personaje);
	return personaje_leido;
}

// COMPARADOR Y DESTRUCTOR DE HEAP
/*
*PRE: Recibe 2 elementos validos
*POST: Devuelve 1 si el elemento_1 es menor al elemento_2, en caso contrario devuelve -1
*/
int comparador_gimnasios(void* elemento_1, void* elemento_2){
	if((*(gimnasio_t*)elemento_1).dificultad < (*(gimnasio_t*)elemento_2).dificultad)
		return 1;
	return -1;
}
/*
*PRE: Recibe un elemento valido
*POST: Libera toda la memoria reservada para el gimnasio y sus campos
*/
void destructor_gimnasios(void* gimnasio){
	size_t cant_entrenadores = lista_elementos((*(gimnasio_t*)gimnasio).entrenadores);
	nodo_t* aux = ((nodo_t*)(*(gimnasio_t*)gimnasio).entrenadores->nodo_inicio);
	while(cant_entrenadores > 0){
		if((*(entrenador_t*)aux->elemento).pokemons)
				lista_destruir((*(entrenador_t*)aux->elemento).pokemons);
			aux = aux->siguiente;
			cant_entrenadores--;
	}
	lista_destruir((*(gimnasio_t*)gimnasio).entrenadores);
	free(gimnasio);
}



// INICIALIZADOR DE JUEGO
void inicializar_juego(juego_t* juego){
	int (*heap_comparador)(void* elemento_1, void* elemento_2) = comparador_gimnasios;
	void (*heap_destructor)(void* elemento) = destructor_gimnasios;
	juego->gimnasios = crear_heap(heap_comparador, heap_destructor);
	juego->personaje = NULL;
}

// CAMBIAR POKEMONS
/*
*PRE: Recibe 2 listas validas de pokemons y 2 posiciones 
*POST: devuelve true si el intercambio es valido. En caso contrario devolvera false
*/
bool es_intercambio_valido(lista_t* pokemons_batalla, size_t pos_batalla, lista_t* pokemons_obtenidos, size_t pos_obtenidos){
	if(pos_batalla > lista_elementos(pokemons_batalla) || pos_obtenidos > lista_elementos(pokemons_obtenidos)){
		printf(BLANCO"La posicion ingresada no existe\n"RESET);
		return false;
	}
	if(lista_elemento_en_posicion(pokemons_batalla, pos_batalla) == lista_elemento_en_posicion(pokemons_obtenidos, pos_obtenidos)){
		printf(BLANCO"No se puede intercambiar un pokemon con si mismo\n"RESET);
		return false;
	}
	return true;
}
void cambiar_pokemons(lista_t* pokemons_batalla, lista_t* pokemons_obtenidos){
	size_t pos_batalla, pos_obtenidos;

	mostrar_pokemons_jugador(pokemons_batalla, pokemons_obtenidos);

	printf(BLANCO"Ingrese la posicion del pokemon que desea quitar de la lista de batalla\n"RESET);
	scanf("%u", &pos_batalla);
	printf(BLANCO"Ingrese la posicion del pokemon que desea agregar de la lista de obtenidos\n"RESET);
	scanf("%u", &pos_obtenidos);
	system("clear");
	while(!es_intercambio_valido(pokemons_batalla, pos_batalla, pokemons_obtenidos, pos_obtenidos)){
		printf(BLANCO"El intercambio que selecciono es invalido, intentelo nuevamente\n"RESET);
		mostrar_pokemons_jugador(pokemons_batalla, pokemons_obtenidos);
		printf(BLANCO"Ingrese la posicion del pokemon que desea quitar de la lista de batalla\n"RESET);
		scanf("%u", &pos_batalla);
		printf(BLANCO"Ingrese la posicion del pokemon que desea agregar de la lista de obtenidos\n"RESET);
		scanf("%u", &pos_obtenidos);
	}

	lista_borrar_de_posicion(pokemons_batalla, pos_batalla);
	pokemon_t* pokemon_agregar = lista_elemento_en_posicion(pokemons_obtenidos, pos_obtenidos);
	lista_insertar(pokemons_batalla, pokemon_agregar);
	system("clear");

	mostrar_pokemons_jugador(pokemons_batalla, pokemons_obtenidos);
	char letra;
	scanf(" %c", &letra);
	system("clear");
}


// BATALLAS
/*
*PRE: Recibe 2 posiciones, una cantidad de pokemons y un booleano
*POST: Devuelve true si termino la batalla y false si no termino
*/
bool termino_la_batalla(size_t posicion_pers, size_t posicion_cont, size_t cant_pok_cont, bool* gano_personaje){
	if(posicion_pers >= 6)
		return true;
	else if(posicion_cont >= 6 || cant_pok_cont == 0){
		*gano_personaje = true;
		return true;
	}
	return false;
}
/*
*PRE: Recibe 2 pokemons inicializados y un id de batalla
*POST: Devuelve 1 si el ganador es el pkm_1 y -1 si el ganador es el pkm_2
*/
int determinar_funcion_batalla(pokemon_t* pkm_1, pokemon_t* pkm_2, int id_batalla){
	int ganador = 1;

	if(id_batalla == 1)
		ganador = funcion_batalla_1(pkm_1, pkm_2);
	else if(id_batalla == 2)
		ganador = funcion_batalla_2(pkm_1, pkm_2);
	else if(id_batalla == 3)
		ganador = funcion_batalla_3(pkm_1, pkm_2);
	else if(id_batalla == 4)
		ganador = funcion_batalla_4(pkm_1, pkm_2);
	else
		ganador = funcion_batalla_5(pkm_1, pkm_2);
	return ganador;
}
/*
*PRE: Recibe un pokemon inicializado
*POST: Aumenta 1 punto a todos los atributos del pokemon
*/
void mejorar_atributos(pokemon_t* pokemon){
	if(pokemon->cant_mejoras < MAX_PUNTOS_EXTRA){
		(pokemon->velocidad)++;
		(pokemon->defensa)++;
		(pokemon->ataque)++;
		(pokemon->cant_mejoras)++;
	}
}

int batallar(personaje_t* personaje, lista_t* entrenadores, int id_batalla, bool simulando){
	bool perdio_gimnasio = false;
	size_t cant_entrenadores = lista_elementos(entrenadores);

	while(cant_entrenadores > 0 && !perdio_gimnasio){
		entrenador_t* entrenador_actual = lista_tope(entrenadores);
		size_t cant_pok_cont = lista_elementos(entrenador_actual->pokemons);

		bool gano_personaje = false;
		size_t posicion_pers = 0, posicion_cont = 0;

		pokemon_t* pokemon_personaje_actual = lista_elemento_en_posicion(personaje->pokemons_batalla, posicion_pers);
		pokemon_t* pokemon_contrincante_actual = lista_elemento_en_posicion(entrenador_actual->pokemons, posicion_cont);
		while(!termino_la_batalla(posicion_pers, posicion_cont, cant_pok_cont, &gano_personaje)){
			if(!simulando)
				mostrar_batalla(pokemon_personaje_actual, pokemon_contrincante_actual, id_batalla, personaje->nombre, entrenador_actual->nombre);
			int ganador = determinar_funcion_batalla(pokemon_personaje_actual, pokemon_contrincante_actual, id_batalla); 
			if(ganador == PKM_PERSONAJE){
				posicion_cont++;
				cant_pok_cont--;
				mejorar_atributos(pokemon_personaje_actual);
				if(posicion_cont < 6 && cant_pok_cont > 0)
					pokemon_contrincante_actual = lista_elemento_en_posicion(entrenador_actual->pokemons, posicion_cont);
			}
			else if(ganador == PKM_RIVAL){
				posicion_pers++;
				if(posicion_pers < 6)
					pokemon_personaje_actual = lista_elemento_en_posicion(personaje->pokemons_batalla, posicion_pers);
			}
		}
		if(gano_personaje == true){
			if(!simulando)
				mostrar_batalla_ganada(entrenador_actual->nombre);
			if(cant_entrenadores > 1 || simulando == true){ 
				lista_destruir(entrenador_actual->pokemons); 
				free(entrenador_actual);
				lista_desapilar(entrenadores); 
			}
			cant_entrenadores--;
		}
		else
			perdio_gimnasio = true;
	}
	if(perdio_gimnasio == true)
		return PERDIO;

	return GANO;
}
/*
*PRE: Recibe una posicion y una cantidad de pokemons
*POST: Devuelve true si la posicion es valida, en caso contrario devuelve false
*/
bool es_pos_valida(size_t pos_ingresada, size_t cant_pokemons){
	return(pos_ingresada < cant_pokemons);
}

void tomar_pokemon(entrenador_t* lider, lista_t* pokemons_obtenidos){
	size_t pos = 0;
	mostrar_pokemons_lider(lider->pokemons);
	scanf("%u", &pos);
	while(!es_pos_valida(pos, lista_elementos(lider->pokemons))){
		printf("La posicion ingresada no es correcta, intentelo nuevamente\n");
		mostrar_pokemons_lider(lider->pokemons);
		scanf("%u", &pos);
	}

	pokemon_t* pokemon_agregar = lista_elemento_en_posicion(lider->pokemons, pos);
	lista_insertar(pokemons_obtenidos, pokemon_agregar);
	lista_borrar_de_posicion(lider->pokemons, pos); // elimino el pokemon de la lista del lider
}



// FLUJO DE JUEGO

bool es_tecla_valida(char tecla, char menu_actual[MAX_NOMBRE]){
	if(strcmp(menu_actual, "inicio") == 0)
		return(tecla == CARGAR_PERSONAJE || tecla == CARGAR_GIMNASIOS || tecla == INICIAR || tecla == SIMULAR || tecla == ARCHIVO_UNICO || tecla == MULTIPLES_ARCHIVOS);
	else if(strcmp(menu_actual, "gimnasio") == 0)
		return(tecla == MOSTRAR_PERSONAJE || tecla == MOSTRAR_GIMNASIO || tecla == CAMBIAR_POKEMON || tecla == BATALLAR);
	return false;
}
/*
*PRE: Recibe una tecla presionada, la cantidad de gimnasios y un booleano
*POST: Devuelve true si hay archivos cargados, en caso contrario devuelve false
*/
bool cargue_archivos(char tecla, size_t cant_gimnasios, bool cargue_personaje){
	if(tecla == CARGAR_GIMNASIOS && cant_gimnasios > 0){ // quiere cargar un archivo de gimnasios pero ya los cargo 
		printf("Ya cargo los gimnasios\n");
		return true;
	}
	if(tecla == CARGAR_PERSONAJE && cargue_personaje){
		printf("No se puede cargar el personaje mas de 1 vez\n");
		return true;
	}
	if((tecla == INICIAR || tecla == SIMULAR) && (!cargue_personaje || cant_gimnasios == 0)){
		printf("No puede iniciar la partida sin haber cargado el personaje y los gimnasios\n");
		return true;
	}
	return false;
}
/*
*PRE: Recibe un juego inicializado, una ruta del archivo de gimnasios y el resultado
*POST: muestra mensaje de error y vuelve a tratar de cargar el gimnasio
*/
void error_carga_gimnasio(juego_t* juego, char ruta_gimnasios[MAX_RUTA], int* resultado){
	mostrar_error_carga();
	scanf("%s", ruta_gimnasios);
	system("clear");
	*resultado = cargar_gimnasios(juego->gimnasios, ruta_gimnasios);
}
/*
*PRE: Recibe un juego inicializado y una ruta al archivo de personaje
*POST: muestra mensaje de error y vuelve a tratar de cargar el personaje
*/
void error_carga_personaje(juego_t* juego, char ruta_personaje[MAX_RUTA]){
	mostrar_error_carga();
	scanf("%s", ruta_personaje);
	system("clear");
	juego->personaje = cargar_personaje(ruta_personaje);
}

/*
*PRE: Recibe un juego inicializado, una tecla, el menu actual y 2 booleanos
*POST: Realiza una accion del menu de inicio dependiendo de la tecla ingresada
*/
void accion_inicio(juego_t* juego, char tecla, char menu_actual[MAX_NOMBRE], bool* cargue_personaje, bool* simulando){ // falta la opcion de simular y chequeos
	char ruta_personaje[MAX_RUTA], ruta_gimnasios[MAX_RUTA];
	int cant_archivos = 0;

	scanf(" %c", &tecla); // NO PUEDO INGRESAR UNA TECLA CUALQUIERA, SI YA CARGUE ALGUNO DE LOS 2 ARCHIVOS NO PUEDO VOLVER A TOCAR LA TECLA
	while(!es_tecla_valida(tecla, menu_actual) || cargue_archivos(tecla, juego->gimnasios->tope, *cargue_personaje)){
		printf(BLANCO"Esa tecla no es valida, intentelo nuevamente\n"RESET);
		scanf(" %c", &tecla);
	}
	system("clear");

	if(tecla == CARGAR_PERSONAJE){
		mostrar_ingreso_personaje(ruta_personaje);
		juego->personaje = cargar_personaje(ruta_personaje);
		while(!(juego->personaje)){
			error_carga_personaje(juego, ruta_personaje);
		}
		*cargue_personaje = true;
		system("clear");
	}

	else if(tecla == CARGAR_GIMNASIOS){
		mostrar_opcion_gimnasios(&tecla, menu_actual, ruta_gimnasios);
		int resultado;
		if(tecla == ARCHIVO_UNICO){
			mostrar_opcion_gimnasios(&tecla, menu_actual, ruta_gimnasios);
			resultado = cargar_gimnasios(juego->gimnasios, ruta_gimnasios);
			while(resultado == ERROR){
				error_carga_gimnasio(juego, ruta_gimnasios, &resultado);
			}
		}
		else if(tecla == MULTIPLES_ARCHIVOS){
			printf(AMARILLO"==============================================================================================\n"RESET); 
			printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"=========================================\n"RESET);
			printf(BLANCO"\n\nIngrese la cantidad de archivos que desea ingresar...\n"RESET);
			printf(AMARILLO"==============================================================================================\n"RESET);
			scanf("%i", &cant_archivos);
			system("clear");
			for(int i = 0; i < cant_archivos; i++){
				mostrar_opcion_gimnasios(&tecla, menu_actual, ruta_gimnasios);
				resultado = cargar_gimnasios(juego->gimnasios, ruta_gimnasios);
				while(resultado == ERROR){
					error_carga_gimnasio(juego, ruta_gimnasios, &resultado);
				}
			}
		}
		system("clear");
	}
	else if(tecla == INICIAR){
		strcpy(menu_actual, "gimnasio");
	}
	else if(tecla == SIMULAR){
		*simulando = true;
		strcpy(menu_actual, "batalla");
	}
}
/*
*PRE: Recibe un juego inicializado, el gimnasio actual, una tecla y el menu actual
*POST: Realiza una accion del menu de gimnasio dependiendo de la tecla ingresada
*/
void accion_gimnasio(juego_t* juego, gimnasio_t* gimnasio_actual, char tecla, char menu_actual[MAX_NOMBRE]){

	scanf(" %c", &tecla);
	while(!es_tecla_valida(tecla, menu_actual)){
		printf("Esa tecla no es valida, intentelo nuevamente\n");
		scanf(" %c", &tecla);
	}
	system("clear");

	if(tecla == MOSTRAR_PERSONAJE){
		mostrar_personaje(juego->personaje);
		scanf(" %c", &tecla);
		system("clear");
	}
	else if(tecla == MOSTRAR_GIMNASIO){
		mostrar_gimnasio(gimnasio_actual);
		scanf(" %c", &tecla);
		system("clear");
	}
	else if(tecla == CAMBIAR_POKEMON){
		cambiar_pokemons(juego->personaje->pokemons_batalla, juego->personaje->pokemons_obtenidos);
	}
	else if(tecla == BATALLAR){
		strcpy(menu_actual, "batalla");
	}
}
/*
*PRE: Recibe un juego inicializado, el gimnasio actual, una tecla, el menu actual y un booleano
*POST: Realiza una accion del menu de victoria dependiendo de la tecla ingresada
*/
void accion_victoria(juego_t* juego, gimnasio_t* gimnasio_actual, char tecla, char menu_actual[MAX_NOMBRE], bool* tome_pokemon){
	scanf(" %c", &tecla);
	system("clear");

	if(tecla == TOMAR_POKEMON){
		tomar_pokemon(lista_elemento_en_posicion(gimnasio_actual->entrenadores, 0), juego->personaje->pokemons_obtenidos);
		*tome_pokemon = true;
		system("clear");
		mostrar_menu_victoria(gimnasio_actual->nombre, *tome_pokemon);
		accion_victoria(juego, gimnasio_actual, tecla, menu_actual, tome_pokemon);
	}
	else if(tecla == CAMBIAR_POKEMON){
		cambiar_pokemons(juego->personaje->pokemons_batalla, juego->personaje->pokemons_obtenidos);
		mostrar_menu_victoria(gimnasio_actual->nombre, *tome_pokemon);
		accion_victoria(juego, gimnasio_actual, tecla, menu_actual, tome_pokemon);
	}
	else if(tecla == SIGUIENTE){
		strcpy(menu_actual, "gimnasio");
		eliminar_raiz(juego->gimnasios);
	}
}
/*
*PRE: Recibe un juego inicializado, el gimnasio actual, una tecla, el menu actual y un booleano
*POST: Realiza una accion del menu de derrota dependiendo de la tecla ingresada
*/
void accion_derrota(juego_t* juego, gimnasio_t* gimnasio_actual, char tecla, char menu_actual[MAX_NOMBRE], bool* finalizo_partida){
	scanf(" %c", &tecla);
	system("clear");

	if(tecla == CAMBIAR_POKEMON){
		cambiar_pokemons(juego->personaje->pokemons_batalla, juego->personaje->pokemons_obtenidos);
		system("clear");
		mostrar_menu_derrota(gimnasio_actual->nombre);
		accion_derrota(juego, gimnasio_actual, tecla, menu_actual, finalizo_partida);
	}
	else if(tecla == REINTENTAR){

	}
	else if(tecla == FINALIZAR){
		*finalizo_partida = true; 
		mostrar_derrota_final(gimnasio_actual->nombre);
	}
}

void determinar_accion(juego_t* juego, char menu_actual[MAX_NOMBRE], char tecla, bool* finalizo_partida, bool* cargue_personaje, bool* simulando){
	bool tome_pokemon = false;

	if(strcmp(menu_actual, "inicio") == 0){
		mostrar_menu_inicio();
		accion_inicio(juego, tecla, menu_actual, cargue_personaje, simulando);
	}
	gimnasio_t* gimnasio_actual = elemento_raiz(juego->gimnasios);
	if(strcmp(menu_actual, "gimnasio") == 0){
		if(!gimnasio_actual){
			mostrar_victoria_final();
			*finalizo_partida = true;
			return;
		}
		if(!(*simulando)){
			mostrar_menu_gimnasio(gimnasio_actual->nombre);
			accion_gimnasio(juego, gimnasio_actual, tecla, menu_actual);
		}
		else
			strcpy(menu_actual, "batalla");
	}
	if(strcmp(menu_actual, "batalla") == 0){
		int resultado = batallar(juego->personaje, gimnasio_actual->entrenadores, gimnasio_actual->id_batalla, *simulando);
		system("clear");
		if(resultado == GANO && !(*simulando)){ 
			mostrar_menu_victoria(gimnasio_actual->nombre, tome_pokemon);
			accion_victoria(juego, gimnasio_actual, tecla, menu_actual, &tome_pokemon);
		}
		else if(resultado == GANO && *simulando){ 
			strcpy(menu_actual, "gimnasio");
			eliminar_raiz(juego->gimnasios);
		}
		else if(resultado == PERDIO && !(*simulando)){ 
			mostrar_menu_derrota(gimnasio_actual->nombre);
			accion_derrota(juego, gimnasio_actual, tecla, menu_actual, finalizo_partida);
		}
		else{
			mostrar_derrota_final(gimnasio_actual->nombre);
			*finalizo_partida = true;
		}
	}
}