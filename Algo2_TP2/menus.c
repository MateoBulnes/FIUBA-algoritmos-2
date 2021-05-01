#include "menus.h"





void mostrar_menu_inicio(){

	printf(AMARILLO"==============================================================================================\n"RESET); 
	printf(AMARILLO"====================================="RESET VERDE"  AVENTURA POKEMON  "RESET AMARILLO"=====================================\n"RESET);
	printf(BLANCO"\n\nBienvenido a aventura pokemon\n"RESET);
	printf(BLANCO"Presione una de las siguientes teclas para continuar...\n\n"RESET);

	printf(VERDE"[E]"RESET BLANCO" ---> cargar el archivo para el personaje principal\n"RESET);
	printf(VERDE"[A]"RESET BLANCO" ---> cargar el/los archivo/s para los gimnasios del juego\n"RESET);
	printf(VERDE"[I]"RESET BLANCO" ---> Iniciar la partida\n"RESET);
	printf(VERDE"[S]"RESET BLANCO" ---> Simular la partida\n"RESET);

	printf(AMARILLO"==============================================================================================\n"RESET);
}

void mostrar_ingreso_personaje(char ruta_personaje[MAX_RUTA]){
	printf(AMARILLO"==============================================================================================\n"RESET); 
	printf(AMARILLO"========================================"RESET VERDE"  PERSONAJE  "RESET AMARILLO"=========================================\n"RESET);

	printf(BLANCO"\n\nIngrese la ruta del archivo del personaje:\n"RESET);
	printf(AMARILLO"==============================================================================================\n"RESET);
	scanf("%s", ruta_personaje);
	system("clear");
}

void mostrar_opcion_gimnasios(char* tecla, char menu_actual[MAX_NOMBRE], char ruta_gimnasio[MAX_RUTA]){
	if(*tecla == 'A'){
		printf(AMARILLO"==============================================================================================\n"RESET); 
		printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"=========================================\n"RESET);
		printf(BLANCO"\n\nSeleccione como desea cargar sus gimnasios:\n"RESET);
		printf(VERDE"[U]"RESET BLANCO" ---> Un solo archivo con todos los gimnasios\n"RESET);
		printf(VERDE"[M]"RESET BLANCO" ---> Muchos archivos con 1 gimnasio cada uno\n"RESET);
		printf(AMARILLO"==============================================================================================\n"RESET);
		scanf(" %c", tecla);
		while(!es_tecla_valida(*tecla, menu_actual)){
			system("clear");
			printf(AMARILLO"==============================================================================================\n"RESET); 
			printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"=========================================\n"RESET);
			printf(BLANCO"\n\nEsa tecla no es valida, intentelo nuevamente\n"RESET);
			printf(VERDE"[U]"RESET BLANCO" ---> Un solo archivo con todos los gimnasios\n");
			printf(VERDE"[M]"RESET BLANCO" ---> Muchos archivos con 1 gimnasio cada uno\n");
			printf(AMARILLO"==============================================================================================\n"RESET);
			scanf(" %c", tecla);
		}
	}
	else if(*tecla == 'U' || *tecla == 'M'){
		printf(AMARILLO"==============================================================================================\n"RESET); 
		printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"=========================================\n"RESET);
		printf(BLANCO"\n\nIngrese la ruta para el archivo de los gimnasios:\n\n"RESET);
		printf(AMARILLO"==============================================================================================\n"RESET);
		scanf("%s", ruta_gimnasio);
	}
	system("clear");
}

void mostrar_menu_gimnasio(char nombre_gimnasio[MAX_NOMBRE]){
	printf(AMARILLO"==============================================================================================\n"RESET); 
	printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"=========================================\n"RESET);
	printf(BLANCO"\n\nHas llegado al gimnasio %s\n"RESET, nombre_gimnasio);
	printf(BLANCO"Presione una de las siguientes teclas para continuar...\n\n"RESET);

	printf(VERDE"[E]"RESET BLANCO" ---> mostrar jugador principal con sus pokemons\n"RESET);
	printf(VERDE"[G]"RESET BLANCO" ---> mostrar informacion del gimnasio actual\n"RESET);
	printf(VERDE"[C]"RESET BLANCO" ---> cambiar pokemons de batalla\n"RESET);
	printf(VERDE"[B]"RESET BLANCO" ---> iniciar batalla\n"RESET);
	printf(AMARILLO"==============================================================================================\n"RESET);

}
/*
*PRE: Recibe un id de batalla valido
*POST: Muestra una descripcion de la batalla dependiendo del id otorgado
*/
void determinar_descripcion_batalla(int id_batalla){
	printf(BLANCO"DESCRIPCION: "RESET);
	if(id_batalla == 1)
		printf(BLANCO"Gana el pokemon con mayor promedio de atributos\n"RESET);
	else if(id_batalla == 2){
		printf(BLANCO"Gana el pokemon elemental, si ambos lo son se sigue la tabla de elementos\n"RESET);
		printf(BLANCO"Tabla de elementos: "ROJO"FUEGO"RESET"-->"VERDE"TIERRA"RESET"-->"CELESTE"VIENTO"RESET"-->"AMARILLO"ELECTRICIDAD"RESET"-->"AZUL"AGUA"RESET"-->"ROJO"FUEGO"RESET"\n");
	}
	else if(id_batalla == 3)
		printf(BLANCO"Gana el pokemon que tenga mayor velocidad y ataque\n"RESET);
	else if(id_batalla == 4)
		printf(BLANCO"Gana el pokemon cuya inicial sea una vocal, si ambos cumplen, se sigue el alfabeto\n"RESET);
	else if(id_batalla == 5)
		printf(BLANCO"Gana el pokemon con menor velocidad y mayor defensa\n"RESET);
}

void mostrar_gimnasio(gimnasio_t* gimnasio){
	printf(AMARILLO"=================================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"============================================\n"RESET);
	printf(BLANCO"\nNombre: %s\n"RESET, gimnasio->nombre);
	printf(BLANCO"Dificultad: %i\n"RESET, gimnasio->dificultad);
	printf(BLANCO"Id batalla: %i\n"RESET, gimnasio->id_batalla);
	determinar_descripcion_batalla(gimnasio->id_batalla);
	printf(AMARILLO"=================================================================================================\n"RESET);
}

void mostrar_batalla(pokemon_t* pkm_personaje, pokemon_t* pkm_contrincante, int id_batalla, char nombre_personaje[MAX_NOMBRE], char nombre_contrincante[MAX_NOMBRE]){
	printf(AMARILLO"===============================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET VERDE"  BATALLA  "RESET AMARILLO"===========================================\n"RESET);
	printf(CELESTE"\nID BATALLA:"RESET BLANCO" %i\n\n"RESET, id_batalla);
	printf(VERDE"%s                                   VS                   %s\n"RESET, nombre_personaje, nombre_contrincante);
	printf(CELESTE"Pokemon "RESET ROJO"--->"RESET BLANCO" %-12s"RESET CELESTE"                                   Pokemon "RESET ROJO"---> "RESET BLANCO"%-10s\n"RESET, pkm_personaje->nombre, pkm_contrincante->nombre);
	printf(ROJO"        └-->"RESET CELESTE" Vel:"RESET BLANCO" %i                                                "RESET ROJO"└-->"RESET CELESTE" Vel: "RESET BLANCO"%i\n"RESET, pkm_personaje->velocidad, pkm_contrincante->velocidad);
	printf(ROJO"        └-->"RESET CELESTE" Def:"RESET BLANCO" %i                                                "RESET ROJO"└--> "RESET CELESTE"Def: "RESET BLANCO"%i\n"RESET, pkm_personaje->defensa, pkm_contrincante->defensa);
	printf(ROJO"        └-->"RESET CELESTE" Ataq:"RESET BLANCO" %i"RESET ROJO"                                               └--> "RESET CELESTE"Ataq: "RESET BLANCO"%i\n"RESET, pkm_personaje->ataque, pkm_contrincante->ataque);
	printf(ROJO"        └-->"RESET CELESTE" Elemento: "RESET BLANCO"%-12c"RESET ROJO"                                 └--> "RESET CELESTE"Elemento: "RESET BLANCO"%-12c\n\n"RESET, pkm_personaje->elemento, pkm_contrincante->elemento);
	printf(BLANCO"Presione "RESET VERDE"[N]"RESET BLANCO" para continuar...\n"RESET);
	printf(AMARILLO"===============================================================================================\n"RESET);
	char tecla;
	scanf(" %c", &tecla);
	system("clear");
}

void mostrar_batalla_ganada(char nombre_entrenador[MAX_NOMBRE]){
	printf(AMARILLO"===============================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET VERDE"  BATALLA  "RESET AMARILLO"===========================================\n"RESET);
	printf(BLANCO"\nBien hecho! has derrotado a %s\n"RESET, nombre_entrenador);
	printf(BLANCO"\nPresione la tecla "RESET VERDE"[N]"RESET BLANCO" para continuar...\n"RESET);
	printf(AMARILLO"===============================================================================================\n"RESET);
	char tecla;
	scanf(" %c", &tecla);
	system("clear");
}

void mostrar_menu_victoria(char nombre_gimnasio[MAX_NOMBRE], bool tome_pokemon){ //Solo se muestra cuando ya gane el gimnasio (no la batalla)
	printf(AMARILLO"==============================================================================================\n"RESET); 
	printf(AMARILLO"========================================="RESET VERDE"  VICTORIA  "RESET AMARILLO"=========================================\n"RESET);
	printf(BLANCO"\n\nFelicitaciones!!! has derrotado al gimnasio %s\n"RESET, nombre_gimnasio);
	printf(BLANCO"Presione una de las siguientes teclas para continuar...\n\n"RESET);
	if(!tome_pokemon)
		printf(VERDE"[T]"RESET BLANCO" ---> Toma prestado 1 de los pokemons del lider del gimnasio\n"RESET);
	printf(VERDE"[N]"RESET BLANCO" ---> Proximo gimnasio\n"RESET);
	printf(VERDE"[C]"RESET BLANCO" ---> cambiar pokemons de batalla\n"RESET);

	printf(AMARILLO"==============================================================================================\n"RESET);
}

void mostrar_victoria_final(){
	printf(AMARILLO"==============================================================================================\n"RESET); 
	printf(AMARILLO"========================================="RESET VERDE"  VICTORIA  "RESET AMARILLO"=========================================\n"RESET);
	printf(BLANCO"\n              Felicitaciones!!! Has vencido todos los gimnasios con exito\n"RESET);
	printf(BLANCO"                        Es un honor nombrarte MAESTRO POKEMON\n\n"RESET);
	printf("                                     _______________\n");
	printf("                                    "FOND_ROJO"|@@@@|"RESET FOND_BLANCO"     "RESET FOND_ROJO"|####|"RESET"\n");
	printf("                                    "FOND_ROJO"|@@@@|"RESET FOND_BLANCO"     "RESET FOND_ROJO"|####|"RESET"\n");
	printf("                                    "FOND_ROJO"|@@@@|"RESET FOND_BLANCO"     "RESET FOND_ROJO"|####|"RESET"\n");
	printf("                                    "ROJO"\\"RESET FOND_ROJO"@@@@|"RESET FOND_BLANCO"     "RESET FOND_ROJO"|####"RESET ROJO"/"RESET"\n");
	printf("                                     "ROJO"\\"RESET FOND_ROJO"@@@|"RESET FOND_BLANCO"     "RESET FOND_ROJO"|###"RESET ROJO"/"RESET"\n");
	printf("                                      "ROJO"`"RESET FOND_ROJO"@@|"RESET FOND_BLANCO"_____"RESET FOND_ROJO"|##"RESET ROJO"'"RESET"\n");
	printf("                                           "FOND_AMARILLO"(O)\n"RESET);
	printf("                                        "FOND_AMARILLO".-'''''-."RESET"\n");
	printf("                                      "FOND_AMARILLO".'  * * *  `."RESET"\n");
	printf("                                     "FOND_AMARILLO":  *       *  :"RESET"\n");
	printf("                                    "FOND_AMARILLO": ~  "RESET NEGRO FOND_AMARILLO"MAESTRO"RESET FOND_AMARILLO"  ~ :"RESET"\n");
	printf("                                    "FOND_AMARILLO": ~  "RESET NEGRO FOND_AMARILLO"POKEMON"RESET FOND_AMARILLO"  ~ :"RESET"\n");
	printf("                                     "FOND_AMARILLO":  *       *  :"RESET"\n");
	printf("                                      "FOND_AMARILLO"`.  * * *  .'"RESET"\n");
	printf("                                        "FOND_AMARILLO"`-.....-'"RESET"\n");
	printf(AMARILLO"\n==============================================================================================\n"RESET);
}

void mostrar_menu_derrota(char nombre_gimnasio[MAX_NOMBRE]){ 
	printf(AMARILLO"==============================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET ROJO"  DERROTA  "RESET AMARILLO"==========================================\n"RESET);
	printf(BLANCO"\n\nMejor suerte la proxima! Has sido derrotado en el gimnasio %s\n"RESET, nombre_gimnasio);
	printf(BLANCO"Presione una de las siguientes teclas para continuar...\n\n"RESET);

	printf(VERDE"[R]"RESET BLANCO" ---> Reintentar gimnasio\n"RESET);
	printf(VERDE"[C]"RESET BLANCO" ---> cambiar pokemons de batalla\n"RESET);
	printf(VERDE"[F]"RESET BLANCO" ---> Finalizar partida\n"RESET);

	printf(AMARILLO"==============================================================================================\n"RESET);
}

void mostrar_derrota_final(char nombre_gimnasio[MAX_NOMBRE]){
	printf(AMARILLO"==============================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET ROJO"  DERROTA  "RESET AMARILLO"==========================================\n"RESET);
	printf(BLANCO"\n\n           Desafortunadamente has sido derrotado en el gimnasio de %s\n"RESET, nombre_gimnasio);
	printf(BLANCO"                    Pero tu aventura pokemon recien esta comenzando!\n\n"RESET);
	printf(BLANCO"Hasta la proxima aventura...\n"RESET);
	printf(AMARILLO"==============================================================================================\n"RESET);
}



void mostrar_personaje(personaje_t* personaje){
	printf(AMARILLO"==============================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET VERDE"  PERSONAJE  "RESET AMARILLO"========================================\n"RESET);
	printf(CELESTE"\n\nNOMBRE:"RESET BLANCO" %s\n"RESET, personaje->nombre);
	printf(CELESTE"\nPOKEMONS DE BATALLA:\n"RESET);
	printf(NEGRO FOND_AMARILLO"POSICION  |NOMBRE        |VEL    |DEF    |ATA    |ELEMENTO    |"RESET"\n");
	for(size_t i = 0; i < lista_elementos(personaje->pokemons_batalla); i++){
		pokemon_t* pokemon = lista_elemento_en_posicion(personaje->pokemons_batalla, i);
		printf(NEGRO FOND_AMARILLO"   %i      |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
	}
	printf(CELESTE"\nPOKEMONS OBTENIDOS:\n"RESET);
	printf(NEGRO FOND_AMARILLO"POSICION  |NOMBRE        |VEL    |DEF    |ATA    |ELEMENTO    |"RESET"\n");
	for(size_t i = 0; i < lista_elementos(personaje->pokemons_obtenidos); i++){
		pokemon_t* pokemon = lista_elemento_en_posicion(personaje->pokemons_obtenidos, i);
		if(i < 10)
			printf(NEGRO FOND_AMARILLO"   %i      |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
		else 
			printf(NEGRO FOND_AMARILLO"   %i     |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
	}
	printf(AMARILLO"==============================================================================================\n"RESET);
}


void mostrar_pokemons_jugador(lista_t* pokemons_batalla, lista_t* pokemons_obtenidos){
	printf(AMARILLO"===============================================================================================\n"RESET);
	printf(AMARILLO"========================================="RESET VERDE"  CAMBIO  "RESET AMARILLO"============================================\n"RESET);
	printf(CELESTE"BATALLA:\n"RESET);
	printf(NEGRO FOND_AMARILLO"POSICION  |NOMBRE        |VEL    |DEF    |ATA    |ELEMENTO    |"RESET"\n");
	for(size_t i = 0; i < lista_elementos(pokemons_batalla); i++){
		pokemon_t* pokemon = lista_elemento_en_posicion(pokemons_batalla, i);
		printf(NEGRO FOND_AMARILLO"   %i      |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
	}
	printf(CELESTE"OBTENIDOS:\n"RESET);
	printf(NEGRO FOND_AMARILLO"POSICION  |NOMBRE        |VEL    |DEF    |ATA    |ELEMENTO    |"RESET"\n");
	for(size_t i = 0; i < lista_elementos(pokemons_obtenidos); i++){
		pokemon_t* pokemon = lista_elemento_en_posicion(pokemons_obtenidos, i);
		if(i < 10)
			printf(NEGRO FOND_AMARILLO"   %i      |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
		else 
			printf(NEGRO FOND_AMARILLO"   %i     |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
	}

	printf(AMARILLO"===============================================================================================\n"RESET);
}

void mostrar_pokemons_lider(lista_t* pokemons_lider){
	printf(AMARILLO"===============================================================================================\n"RESET);
	printf(AMARILLO"=========================================="RESET VERDE"  LIDER  "RESET AMARILLO"============================================\n"RESET);
	printf(CELESTE"POKEMONS LIDER:\n"RESET);
	printf(NEGRO FOND_AMARILLO"POSICION |NOMBRE        |VEL    |DEF    |ATA    |ELEMENTO    |"RESET"\n");
	for(size_t i = 0; i < lista_elementos(pokemons_lider); i++){
		pokemon_t* pokemon = lista_elemento_en_posicion(pokemons_lider, i);
		printf(NEGRO FOND_AMARILLO"   %i     |%-12s  |%-3i    |%-3i    |%-3i    |%-12c|"RESET"\n", i, pokemon->nombre, pokemon->velocidad, pokemon->defensa, pokemon->ataque, pokemon->elemento);
	}
	printf(BLANCO"Ingrese la posicion del pokemon que desea tomar prestado...\n"RESET);
	printf(AMARILLO"===============================================================================================\n"RESET);
}


void mostrar_error_carga(){
	printf(AMARILLO"==============================================================================================\n"RESET); 
	printf(AMARILLO"========================================="RESET VERDE"  GIMNASIO  "RESET AMARILLO"=========================================\n"RESET);
	printf(BLANCO"\n\nEl archivo que ingreso no es valido, intentelo nuevamente\n"RESET);
	printf(BLANCO"Ingrese la ruta para el archivo:\n\n"RESET);
	printf(AMARILLO"==============================================================================================\n"RESET);
}