#include "juego.h"
#include "menus.h"
#include <time.h>


int main(){

	srand ((unsigned)time(NULL));
	char tecla = 'N'; 
	juego_t juego;
	inicializar_juego(&juego);
	char menu_actual[MAX_NOMBRE];
	strcpy(menu_actual, "inicio");
	bool finalizo_partida = false, cargue_personaje = false, simulando = false;
	
	while(!finalizo_partida){
		determinar_accion(&juego, menu_actual, tecla, &finalizo_partida, &cargue_personaje, &simulando);
	}
	heap_destruir(juego.gimnasios);
	destruir_personaje(juego.personaje);
}