#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "evento_pesca.h"

const char PRIMERA_SELECCION = 0, SEGUNDA_SELECCION = 1, TERCERA_SELECCION = 2, CUARTA_SELECCION = 3, QUINTA_SELECCION = 4;
#define MAX_SELECCIONES 5
#define MAX_FUNCIONES 5
#define MAX_NOMBRE 50
#define LISTA 'L'
#define CARTAS 'C'
#define MIN_VELOCIDAD_ATLETA 30
#define MIN_VELOCIDAD_EN_AGUA 75
#define MAX_PESO_ATLETA 50
#define MIN_PESO_CHOCOLATERO 60
#define COLOR_SIMPSON "amarillo"
#define COLOR_CHOCOLATE "marron" 

#define RESET "\e[0m"
#define BLANCO "\033[1m\033[37m"
#define FOND_ROJO "\e[41m"
#define FOND_VERDE "\e[42m"
#define FOND_CELESTE "\e[46m"
#define FOND_ROSA "\e[45m"
#define AMARILLO "\033[1m\033[33m"
#define ROJO "\033[1m\033[31m"
#define VERDE "\033[1m\033[32m"
#define AZUL "\033[1m\033[34m"
#define NEGRO "\033[0m\033[30m"
#define ROSA "\033[1m\033[35m"

/*
(para todas las funciones de seleccion y de mostrar pokemon)--> PRE: recibe un puntero a un pokemon valido
*/
bool es_color_primario(pokemon_t* pokemon){
	return((strcmp(pokemon->color, "amarillo") == 0) || (strcmp(pokemon->color, "rojo") == 0) || (strcmp(pokemon->color, "azul") == 0));
}

bool es_atleta(pokemon_t* pokemon){ // el pokemon debe tener velocidad > 30 y peso menor a 50
	return((pokemon->velocidad >= MIN_VELOCIDAD_ATLETA) && (pokemon->peso <= MAX_PESO_ATLETA));
}

bool tiene_descendencia_simpson(pokemon_t* pokemon){ // el pokemon debe ser de color amarillo, y su especie debe empezar con "s"
	return((strcmp(pokemon->color, COLOR_SIMPSON) == 0) && (pokemon->especie[0] == 'S'));
}

bool esta_comodo_en_agua(pokemon_t* pokemon){ // se considera comodo en el agua si su color es azul, su especie empieza con a (de agua), y su velocidad es >= 75 (se mueve con facilidad) 
	return((strcmp(pokemon->color, "azul") == 0) && (pokemon->especie[0] == 'A') && (pokemon->velocidad >= MIN_VELOCIDAD_EN_AGUA));
}

bool es_amante_de_chocolate(pokemon_t* pokemon){ // el pokemon es amante del chocolate si su especie empieza con c, es de color marron, y es pesado (>= 60) 
	return((pokemon->peso >= MIN_PESO_CHOCOLATERO) && (strcmp(pokemon->color, COLOR_CHOCOLATE) == 0) && (pokemon->especie[0] == 'C'));
}
// POST: imprime los pokemon en forma de lista
void mostrar_en_lista(pokemon_t* pokemon){
	printf(FOND_ROJO BLANCO"|%12s|%12i|%12i|%12s|"RESET"\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
} 
/*POST: imprime por pantalla un pokemon en forma de carta*/
void mostrar_cartas(pokemon_t* pokemon){
	
	printf(VERDE"┌----------------------┐"RESET"\n");
	printf(VERDE"|"RESET" "AMARILLO"%-21s|"RESET"\n", pokemon->especie);
	printf(VERDE"|"RESET"       "BLANCO"Velocidad:"RESET" "ROJO"%4i"RESET VERDE"|"RESET"\n", pokemon->velocidad);
	printf(VERDE"|"RESET"       "BLANCO"Peso:"RESET" "VERDE"%9i"RESET VERDE"| "RESET"\n", pokemon->peso);
	printf(VERDE"|"RESET"       "BLANCO"Color:"RESET" "AZUL"%8s"RESET VERDE"|"RESET"\n", pokemon->color);
	printf(VERDE"└----------------------┘"RESET"\n\n");
}
// POST: imprime por pantalla un pokemon simulando la famosa pokedex
void mostrar_pokedex(pokemon_t* pokemon){
	printf(NEGRO FOND_ROJO"                    POKEDEX                       "RESET"\n");
	printf(FOND_ROJO"                                                  "RESET"\n");
	printf(FOND_ROJO"  "RESET NEGRO FOND_CELESTE"ESPECIE:                "RESET FOND_ROJO"  "RESET NEGRO FOND_CELESTE"Velocidad --> %6i"RESET FOND_ROJO"  "RESET"\n", pokemon->velocidad);
	printf(FOND_ROJO"  "RESET NEGRO FOND_CELESTE"        %-16s"RESET FOND_ROJO"  "RESET NEGRO FOND_CELESTE"Peso --> %11i"RESET FOND_ROJO"  "RESET"\n", pokemon->especie, pokemon->peso);
	printf(FOND_ROJO"  "RESET FOND_CELESTE"                        "RESET FOND_ROJO"  "RESET NEGRO FOND_CELESTE"Habitat --> Arrecife"RESET FOND_ROJO"  "RESET"\n");
	printf(FOND_ROJO"  "RESET NEGRO FOND_CELESTE"*volver <--             "RESET FOND_ROJO"  "RESET NEGRO FOND_CELESTE"Color --> %10s"RESET FOND_ROJO"  "RESET"\n", pokemon->color);
	printf(FOND_ROJO"                                                  "RESET"\n\n");
}
// POST: imprime por pantalla un pokemon en forma de perfiles de instagram
void mostrar_pokegram(pokemon_t* pokemon){
	// Por si no se entiende lo de abajo seria el logo de instagram
	printf(FOND_ROSA"┌--.┐"RESET"\n");
	printf(FOND_ROSA"| O |  POKEGRAM                                                                                        "RESET"\n");
	printf(FOND_ROSA"└---┘"RESET"\n");
	printf("PERFIL:\n");
	printf(ROSA"\tNombre de usuario:"RESET" %s\n", pokemon->especie);
	printf(ROSA"\tUbicacion:"RESET" Arrecifes unidos\n");
	printf(ROSA"\tPeso en cuarentena:"RESET" %i\n", pokemon->peso);
	printf(ROSA"\tVelocidad de scrolleo en la app:"RESET" %i\n", pokemon->velocidad);
	printf(ROSA"\tColor favorito:"RESET" %s\n", pokemon->color);
}
 // POST: imprime un pokemon de forma anidada
void mostrar_anidado(pokemon_t* pokemon){
	printf(AMARILLO"ARRECIFE:\n"RESET);
	printf(VERDE"\tESPECIE:"RESET" %s\n", pokemon->especie);
	printf(ROJO"\t\tVELOCIDAD:"RESET" %i\n", pokemon->velocidad);
	printf(ROJO"\t\tPESO:"RESET" %i\n", pokemon->peso);
	printf(ROJO"\t\tCOLOR:"RESET" %s\n", pokemon->color);
}

/*
*PRE: Recibe un string vacio y un numero que representa la seleccion que se esta usando
*POST: Escribe una categoria en el string dependiendo del numero de seleccion 
*/
void definir_nombre(char nombre_seleccion[MAX_NOMBRE], int num_seleccion){
	if(num_seleccion == PRIMERA_SELECCION)
		strcpy(nombre_seleccion, "Colores primarios");
	else if(num_seleccion == SEGUNDA_SELECCION)
		strcpy(nombre_seleccion, "Descendencia Simpson");
	else if(num_seleccion == TERCERA_SELECCION)
		strcpy(nombre_seleccion, "Comodidad en agua");
	else if(num_seleccion == CUARTA_SELECCION)
		strcpy(nombre_seleccion, "Amante del chocolate");
	else if(num_seleccion == QUINTA_SELECCION)
		strcpy(nombre_seleccion, "Atletas");
}
/*POST: Imprime por pantalla los titulos del programa*/
void mostrar_titulos(int num_seleccion){
	char nombre_seleccion[MAX_NOMBRE];
	definir_nombre(nombre_seleccion, num_seleccion);
	printf(FOND_CELESTE BLANCO"Seleccion n°%i ----> %s"RESET"\n", num_seleccion+1, nombre_seleccion);
	if(num_seleccion == 0){
		printf(FOND_VERDE"  |     ESPECIE|   VELOCIDAD|        PESO|       COLOR|"RESET"\n");
	}
}

int main(int argc, char* argv[]){
	
	int cant_seleccion[MAX_SELECCIONES] = {7, 2, 8, 3, 4};
	int i = 0; 
	bool (*funciones_seleccion[MAX_FUNCIONES])(pokemon_t*) = {es_color_primario, tiene_descendencia_simpson, esta_comodo_en_agua, es_amante_de_chocolate, es_atleta};
	void (*mostrar_pokemon[MAX_FUNCIONES])(pokemon_t*) = {mostrar_en_lista, mostrar_cartas, mostrar_pokedex, mostrar_pokegram, mostrar_anidado};

	if(argc == 1){
		printf("Debe introducir la ruta del archivo con los pokemon del arrecife, intentelo nuevamente\n");
		return 0;
	}
	
	arrecife_t* arrecife = crear_arrecife(argv[1]);
	acuario_t* acuario = crear_acuario();
	
	if((arrecife != NULL) && (acuario != NULL)){
		while(i < MAX_FUNCIONES){
			trasladar_pokemon(arrecife, acuario, funciones_seleccion[i], cant_seleccion[i]);
			mostrar_titulos(i);
			censar_arrecife(arrecife, mostrar_pokemon[i]);
			i++;
		}
		guardar_datos_acuario(acuario, "acuario.txt");
		liberar_arrecife(arrecife);
		liberar_acuario(acuario);
	}
	else if(arrecife != NULL)
		liberar_arrecife(arrecife);
	else if(acuario != NULL)
		liberar_acuario(acuario);

	return 0;
}