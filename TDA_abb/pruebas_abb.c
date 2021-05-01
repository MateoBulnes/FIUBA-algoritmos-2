#include <stdio.h>
#include "abb.h"
#include "pa2mm.h"

#define MAX_ELEMENTOS 10
#define ERROR -1

int comparador_insercion(void* elemento_1, void* elemento_2){
	if((*(int*)elemento_1) < (*(int*)elemento_2))
		return -1;
	return 1;
}
int comparador_busqueda(void* elemento_1, void* elemento_2){
	if((*(int*)elemento_1) == (*(int*)elemento_2))
		return 0;
	if((*(int*)elemento_1) > (*(int*)elemento_2))
		return 1;
	return -1;
}

void probar_creacion_arbol(){
	abb_t* un_arbol = NULL;
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_insercion;
	
	pa2m_afirmar((un_arbol = arbol_crear(abb_comparador, NULL)) != NULL, "Puedo crear un arbol");
	
	arbol_destruir(un_arbol);
}

void probar_insercion(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_insercion;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elemento = 5, segundo = 6, tercero = 7, cuarto = 4;

	pa2m_afirmar(arbol_insertar(un_arbol, &elemento) == 0, "Puedo insertar un elemento en un arbol vacio");
	pa2m_afirmar(un_arbol->nodo_raiz->elemento == &elemento, "El elemento insertado es el correspondiente");
	pa2m_afirmar(arbol_insertar(un_arbol, &segundo) == 0, "Puedo insertar un segundo elemento a la derecha de la raiz");
	pa2m_afirmar(un_arbol->nodo_raiz->derecha->elemento == &segundo, "El elemento insertado es el correspondiente");
	pa2m_afirmar(arbol_insertar(un_arbol, &tercero) == 0, "Puedo insertar un tercer elemento en el arbol");
	pa2m_afirmar(un_arbol->nodo_raiz->derecha->derecha->elemento == &tercero, "El elemento insertado es el correspondiente");
	pa2m_afirmar(arbol_insertar(un_arbol, &cuarto) == 0, "Puedo insertar un cuarto elemento a la izquierda de la raiz");
	pa2m_afirmar(un_arbol->nodo_raiz->izquierda->elemento == &cuarto, "El elemento insertado es el correspondiente");
	
	arbol_destruir(un_arbol);
}

void probar_eliminacion(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {10, 11, 15, 7, 8, 4, 5, 6};
	int elemento = 15, segundo_elemento = 5, tercer_elemento = 7, raiz = 10; 
	int* array[MAX_ELEMENTOS];
	size_t tamanio = 10;

	for(int i = 0; i < 8; i++){
		arbol_insertar(un_arbol, &(elementos[i]));
	}
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 8, "El arbol tiene 8 elementos");

	pa2m_afirmar(arbol_borrar(un_arbol, &elemento) == 0, "Puedo eliminar un nodo sin hijos");
	pa2m_afirmar(arbol_buscar(un_arbol, &elemento) == NULL, "El elemento fue eliminado correctamente");
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 7, "El arbol tiene 7 elementos");

	pa2m_afirmar(arbol_borrar(un_arbol, &segundo_elemento) == 0, "Puedo eliminar un nodo con 1 hijo");
	pa2m_afirmar(arbol_buscar(un_arbol, &segundo_elemento) == NULL, "El elemento fue eliminado correctamente");
	pa2m_afirmar(*(int*)(un_arbol->nodo_raiz->izquierda->izquierda->derecha->elemento) == 6, "El nodo que lo reemplaza es su hijo");
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 6, "El arbol tiene 6 elementos");

	pa2m_afirmar(arbol_borrar(un_arbol, &tercer_elemento) == 0, "Puedo eliminar un nodo con 2 hijos");
	pa2m_afirmar(arbol_buscar(un_arbol, &tercer_elemento) == NULL, "El elemento fue eliminado correctamente");
	pa2m_afirmar(*(int*)un_arbol->nodo_raiz->izquierda->elemento == 6, "El elemento que lo reemplaza es el predecesor inorden");
	pa2m_afirmar(*(int*)un_arbol->nodo_raiz->izquierda->izquierda->elemento == 4 && *(int*)un_arbol->nodo_raiz->izquierda->derecha->elemento == 8, "Los hijos despues del reemplazo son los correspondientes");
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 5, "El arbol tiene 5 elementos");
	
	pa2m_afirmar(arbol_borrar(un_arbol, &raiz) == 0, "Puedo eliminar la raiz del arbol");
	pa2m_afirmar(arbol_buscar(un_arbol, &raiz) == NULL, "El elemento fue eliminado correctamente");
	pa2m_afirmar(*(int*)un_arbol->nodo_raiz->elemento == 8, "El elemento que lo reemplaza es el predecesor inorden");
	pa2m_afirmar(*(int*)un_arbol->nodo_raiz->izquierda->elemento == 6 && *(int*)un_arbol->nodo_raiz->derecha->elemento == 11, "Los hijos despues del reemplazo son los correspondientes");
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 4, "El arbol tiene 4 elementos");
	arbol_borrar(un_arbol, &elementos[4]);
	arbol_borrar(un_arbol, &elementos[7]);
	arbol_borrar(un_arbol, &elementos[5]);
	arbol_borrar(un_arbol, &elementos[1]);
	pa2m_afirmar(arbol_vacio(un_arbol), "Puedo eliminar todos los elementos del arbol y el arbol queda vacio");
	
	arbol_destruir(un_arbol);
}

void probar_busqueda(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {5, 6, 7, 4};
	int elemento_raiz = 5, elemento_izq = 4, elemento_der = 6, ultimo_elemento = 7, elemento_inexistente = 10;

	for(int i = 0; i < 4; i++){
		arbol_insertar(un_arbol, &(elementos[i]));
	}
	
	pa2m_afirmar((*(int*)arbol_buscar(un_arbol, &elemento_raiz)) == elemento_raiz, "Puedo buscar la raiz del arbol");
	pa2m_afirmar((*(int*)arbol_buscar(un_arbol, &elemento_izq)) == elemento_izq, "Puedo buscar el elemento a la izquierda de la raiz");
	pa2m_afirmar((*(int*)arbol_buscar(un_arbol, &elemento_der)) == elemento_der, "Puedo buscar el elemento a la derecha de la raiz");
	pa2m_afirmar((*(int*)arbol_buscar(un_arbol, &ultimo_elemento)) == ultimo_elemento, "Puedo buscar el ultimo elemento del arbol");
	pa2m_afirmar(arbol_buscar(un_arbol, &elemento_inexistente) == NULL, "Buscar un elemento que no esta en el arbol devuelve error");
	pa2m_afirmar((*(int*)arbol_raiz(un_arbol)) == elemento_raiz, "Puedo pedir la raiz del arbol");

	arbol_destruir(un_arbol);
}

void probar_recorrido_inorden(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {5, 6, 7, 4};
	int* array[MAX_ELEMENTOS];
	size_t tamanio = 5;

	for(int i = 0; i < 4; i++){
		arbol_insertar(un_arbol, &(elementos[i]));
	}
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 4, "Recorri la cantidad de elementos esperados");
	pa2m_afirmar((*array[0]) == 4 && (*array[1]) == 5 && (*array[2]) == 6 && (*array[3]) == 7, "El orden de los elementos recorridos es el correspondiente");
	tamanio = 3;
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 3, "Recorri el arbol hasta el 3° elemento y la cantidad es la esperada");
	pa2m_afirmar((*array[0]) == 4 && (*array[1]) == 5 && (*array[2]) == 6 , "El orden de los elementos recorridos es el correspondiente");
	tamanio = 8;
	pa2m_afirmar(arbol_recorrido_inorden(un_arbol, (void**)array, tamanio) == 4, "Pido recorrer mas elementos de los que hay en el arbol y la cantidad es la esperada");
	pa2m_afirmar((*array[0]) == 4 && (*array[1]) == 5 && (*array[2]) == 6 && (*array[3]) == 7, "El orden de los elementos recorridos es el correspondiente");
	
	arbol_destruir(un_arbol);
}
void probar_recorrido_preorden(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {5, 6, 7, 4};
	int* array[MAX_ELEMENTOS];
	size_t tamanio = 5;

	for(int i = 0; i < 4; i++){
		arbol_insertar(un_arbol, &(elementos[i]));
	}
	
	pa2m_afirmar(arbol_recorrido_preorden(un_arbol, (void**)array, tamanio) == 4, "Recorri la cantidad de elementos en el arbol");
	pa2m_afirmar((*array[0]) == 5 && (*array[1]) == 4 && (*array[2]) == 6 && (*array[3]) == 7, "El orden de los elementos recorridos es el correspondiente");
	tamanio = 3;
	pa2m_afirmar(arbol_recorrido_preorden(un_arbol, (void**)array, tamanio) == 3, "Recorri el arbol hasta llenar el array con 3 elementos");
	pa2m_afirmar((*array[0]) == 5 && (*array[1]) == 4 && (*array[2]) == 6 , "El orden de los elementos recorridos es el correspondiente");
	tamanio = 9;
	pa2m_afirmar(arbol_recorrido_preorden(un_arbol, (void**)array, tamanio) == 4, "Pido recorrer mas elementos de los que hay en el arbol y la cantidad es la esperada");
	pa2m_afirmar((*array[0]) == 5 && (*array[1]) == 4 && (*array[2]) == 6 && (*array[3]) == 7, "El orden de los elementos recorridos es el correspondiente");


	arbol_destruir(un_arbol);
}

void probar_recorrido_postorden(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {5, 6, 7, 4};
	int* array[MAX_ELEMENTOS];
	size_t tamanio = 5;

	for(int i = 0; i < 4; i++){
		arbol_insertar(un_arbol, &(elementos[i]));
	}
	pa2m_afirmar(arbol_recorrido_postorden(un_arbol, (void**)array, tamanio) == 4, "Recorri la cantidad de elementos en el arbol");
	pa2m_afirmar((*array[0]) == 4 && (*array[1]) == 7 && (*array[2]) == 6 && (*array[3]) == 5, "El orden de los elementos recorridos es el correspondiente");
	tamanio = 3;
	pa2m_afirmar(arbol_recorrido_postorden(un_arbol, (void**)array, tamanio) == 3, "Recorri el arbol hasta llenar el array con 3 elementos");
	pa2m_afirmar((*array[0]) == 4 && (*array[1]) == 7 && (*array[2]) == 6 , "El orden de los elementos recorridos es el correspondiente");
	tamanio = 9;
	pa2m_afirmar(arbol_recorrido_postorden(un_arbol, (void**)array, tamanio) == 4, "Pido recorrer mas elementos de los que hay en el arbol y la cantidad es la esperada");
	pa2m_afirmar((*array[0]) == 4 && (*array[1]) == 7 && (*array[2]) == 6 && (*array[3]) == 5, "El orden de los elementos recorridos es el correspondiente");


	arbol_destruir(un_arbol);
}

typedef struct extras{
	int* elementos[MAX_ELEMENTOS];
	int cant_llamadas;
}extra_t;

bool recorrer_abb_completo(void* elemento, void* extra){
    if(elemento && extra){
    	((*(extra_t*)extra).cant_llamadas)++;
    	(*(extra_t*)extra).elementos[((*(extra_t*)extra).cant_llamadas)-1] = elemento;
    }
    return false;
}
bool recorrer_hasta_7(void* elemento, void* extra){
	if(elemento && extra)
		((*(extra_t*)extra).cant_llamadas)++;
	if(*(int*)elemento == 7){
		(*(extra_t*)extra).elementos[((*(extra_t*)extra).cant_llamadas)-1] = elemento;
		return true;
	}
	return false;
}
bool recorri_orden_correcto(int* elementos[MAX_ELEMENTOS], int recorrido){
	if(recorrido == ABB_RECORRER_INORDEN)
		return(*elementos[0] == 4 && *elementos[1] == 5 && *elementos[2] == 6 && *elementos[3] == 7 && *elementos[4] == 8 && *elementos[5] == 10 && *elementos[6] == 11 && *elementos[7] == 15);
	else if(recorrido == ABB_RECORRER_PREORDEN)
		return(*elementos[0] == 10 && *elementos[1] == 7 && *elementos[2] == 4 && *elementos[3] == 5 && *elementos[4] == 6 && *elementos[5] == 8 && *elementos[6] == 11 && *elementos[7] == 15);
	else
		return(*elementos[0] == 6 && *elementos[1] == 5 && *elementos[2] == 4 && *elementos[3] == 8 && *elementos[4] == 7 && *elementos[5] == 15 && *elementos[6] == 11 && *elementos[7] == 10);
}
void probar_iterador_inorden(abb_t* un_arbol, extra_t extra){
	extra.cant_llamadas = 0;
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_INORDEN, recorrer_abb_completo, &extra) == 8, "Recorro todos los elementos, devuelve la cantidad de elementos esperada");
	pa2m_afirmar(extra.cant_llamadas == 8, "Se invoco a la funcion la cantidad de veces esperada");
	pa2m_afirmar(recorri_orden_correcto(extra.elementos, ABB_RECORRER_INORDEN), "Se recorrieron los elementos en el orden correcto");
	extra.cant_llamadas = 0;
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_INORDEN, recorrer_hasta_7, &extra) == 4, "cuando la funcion devuelve true, se corta la iteracion, devuelve la cantidad de elementos esperada");
	pa2m_afirmar(extra.cant_llamadas == 4, "Se invoco a la funcion la cantidad de veces esperada");
	pa2m_afirmar(*extra.elementos[0] == 4 && *extra.elementos[1] == 5 && *extra.elementos[2] == 6 && *extra.elementos[3] == 7, "Se recorrieron los elementos en el orden correcto");
}
void probar_iterador_preorden(abb_t* un_arbol, extra_t extra){
	extra.cant_llamadas = 0;
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_PREORDEN, recorrer_abb_completo, &extra) == 8, "Recorro todos los elementos, devuelve la cantidad de elementos esperada");
	pa2m_afirmar(extra.cant_llamadas == 8, "Se invoco a la funcion la cantidad de veces esperada");
	pa2m_afirmar(recorri_orden_correcto(extra.elementos, ABB_RECORRER_PREORDEN), "Se recorrieron los elementos en el orden correcto");
	extra.cant_llamadas = 0;
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_PREORDEN, recorrer_hasta_7, &extra) == 2, "cuando la funcion devuelve true, se corta la iteracion, devuelve la cantidad de elementos esperada");
	pa2m_afirmar(extra.cant_llamadas == 2, "Se invoco a la funcion la cantidad de veces esperada");
	pa2m_afirmar(*extra.elementos[0] == 10 && *extra.elementos[1] == 7, "Se recorrieron los elementos en el orden correcto");
}
void probar_iterador_postorden(abb_t* un_arbol, extra_t extra){
	extra.cant_llamadas = 0;
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_POSTORDEN, recorrer_abb_completo, &extra) == 8, "Recorro todos los elementos, devuelve la cantidad de elementos esperada");
	pa2m_afirmar(extra.cant_llamadas == 8, "Se invoco a la funcion la cantidad de veces esperada");
	pa2m_afirmar(recorri_orden_correcto(extra.elementos, ABB_RECORRER_POSTORDEN), "Se recorrieron los elementos en el orden correcto");
	extra.cant_llamadas = 0;
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_POSTORDEN, recorrer_hasta_7, &extra) == 5, "cuando la funcion devuelve true, se corta la iteracion, devuelve la cantidad de elementos esperada");
	pa2m_afirmar(extra.cant_llamadas == 5, "Se invoco a la funcion la cantidad de veces esperada");
	pa2m_afirmar(*extra.elementos[0] == 6 && *extra.elementos[1] == 5 && *extra.elementos[2] == 4 && *extra.elementos[3] == 8 && *extra.elementos[4] == 7, "Se recorrieron los elementos en el orden correcto");
}
void probar_iterador(){
	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {10, 11, 15, 7, 8, 4, 5, 6};
	extra_t extra;

	for(int i = 0; i < 8; i++){
		arbol_insertar(un_arbol, &(elementos[i]));
	}
	pa2m_nuevo_grupo("ITERADOR INORDEN");
	probar_iterador_inorden(un_arbol, extra);
	pa2m_nuevo_grupo("ITERADOR PREORDEN");
	probar_iterador_preorden(un_arbol, extra);
	pa2m_nuevo_grupo("ITERADOR POSTORDEN");
	probar_iterador_postorden(un_arbol, extra);

	arbol_destruir(un_arbol);
}

void destruir_elemento(int* elemento){
	free(elemento);
}
void destructor(void* elemento){
	if(!elemento)
		return;
	destruir_elemento((int*)elemento);
}

void probar_arbol_NULL(){
	int elemento = 5;
	pa2m_afirmar(arbol_insertar(NULL, &elemento) == ERROR, "Insertar un elemento en un arbol nulo devuelve error");
	pa2m_afirmar(arbol_buscar(NULL, &elemento) == NULL, "Buscar un elemento en un arbol nulo devuelve error");
	pa2m_afirmar(arbol_borrar(NULL, &elemento) == ERROR, "Borrar un elemento en un arbol nulo devuelve error");
	pa2m_afirmar(arbol_vacio(NULL) == true, "Un arbol nulo es vacio");
	pa2m_afirmar(arbol_raiz(NULL) == NULL, "La raiz de un arbol nulo es NULL");
	pa2m_afirmar(abb_con_cada_elemento(NULL, ABB_RECORRER_POSTORDEN, recorrer_abb_completo, NULL) == 0, "Iterar con un arbol nulo devuelve 0 elementos recorridos");

	int (*abb_comparador)(void* elemento_1, void* elemento_2) = comparador_busqueda;
	abb_t* un_arbol = arbol_crear(abb_comparador, NULL);
	int elementos[MAX_ELEMENTOS] = {5, 6, 7, 4};
	for(int i = 0; i < 4; i++){
		arbol_insertar(un_arbol, &elementos[i]);
	}
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_POSTORDEN, NULL, NULL) == 0, "No se puede iterar con una funcion nula");
	pa2m_afirmar(abb_con_cada_elemento(un_arbol, ABB_RECORRER_POSTORDEN, recorrer_abb_completo, NULL) == 4, "Se puede iterar con un puntero extra nulo");

	arbol_destruir(un_arbol);
}
int main(){

	pa2m_nuevo_grupo("PRUEBAS DE CREACION DE ARBOL");
	probar_creacion_arbol();

	pa2m_nuevo_grupo("PRUEBAS DE INSERCION");
	probar_insercion();

	pa2m_nuevo_grupo("PRUEBAS DE BUSQUEDA");
	probar_busqueda();

	pa2m_nuevo_grupo("PRUEBAS DE RECORRIDO"); 
	pa2m_nuevo_grupo("RECORRIDO INORDEN");
	probar_recorrido_inorden();
	pa2m_nuevo_grupo("RECORRIDO PREORDEN");
	probar_recorrido_preorden();
	pa2m_nuevo_grupo("RECORRIDO POSTORDEN");
	probar_recorrido_postorden();

	pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION");
	probar_eliminacion();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR");
	probar_iterador();

	pa2m_nuevo_grupo("PRUEBAS CON NULL");
	probar_arbol_NULL();

	pa2m_mostrar_reporte();

	return 0;
}