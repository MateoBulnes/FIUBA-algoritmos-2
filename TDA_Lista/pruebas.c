#include <stdio.h>
#include "pa2mm.h"
#include "lista.h"

#define MAX_ELEMENTOS 10
#define MAX_POSICIONES 50
#define ERROR -1

void probar_creacion_lista(){
	lista_t* una_lista = NULL;

	pa2m_afirmar((una_lista = lista_crear()) != NULL, "Puedo crear una lista");

	lista_destruir(una_lista);
}

void probar_insertar_elemento(){
	lista_t* una_lista = lista_crear();
	int elemento = 10, segundo_elemento = 20;

	pa2m_afirmar(lista_insertar(una_lista, &elemento) == 0, "Puedo insertar un elemento al final");
	pa2m_afirmar((*(int*)una_lista->nodo_inicio->elemento) == elemento, "Inserte el elemento correctamente");
	pa2m_afirmar(lista_insertar(una_lista, &segundo_elemento) == 0, "Puedo agregar un segundo elemento");
	pa2m_afirmar((*(int*)una_lista->nodo_inicio->siguiente->elemento) == segundo_elemento, "Inserte el elemento correctamente");
	pa2m_afirmar(lista_insertar(una_lista, NULL) == 0, "Puedo agregar un elemento NULL");
	pa2m_afirmar(lista_elementos(una_lista) == 3, "Tengo 3 elementos en la lista");
	
	lista_destruir(una_lista);
}

bool son_elementos_correspondientes(lista_t* lista, int elementos[MAX_ELEMENTOS]){
	return(((*(int*)lista->nodo_inicio->elemento) == elementos[5]) && 
		   ((*(int*)lista->nodo_inicio->siguiente->elemento) == elementos[0]) &&
		   ((*(int*)lista->nodo_inicio->siguiente->siguiente->elemento) == elementos[3]) &&
		   ((*(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->elemento) == elementos[1]) &&
		   ((*(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente->elemento) == elementos[2]) &&
		   ((*(int*)lista->nodo_inicio->siguiente->siguiente->siguiente->siguiente->siguiente->elemento) == elementos[4]));
}

void probar_insertar_en_posicion(){
	lista_t* una_lista = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30, 25, 50, 5, 70};
	size_t pos = 1, pos_inexistente = 40, pos_primera = 0;

	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &(elementos[0]), pos) == 0, "Puedo insertar un elemento en una lista sin elementos");
	lista_insertar(una_lista, &(elementos[1]));
	lista_insertar(una_lista, &(elementos[2]));

	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &(elementos[3]), pos) == 0, "Puedo insertar un elemento en la posicion 1");
	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &(elementos[4]), pos_inexistente) == 0, "Puedo insertar un elemento en una posicion que no existe");
	pa2m_afirmar(lista_insertar_en_posicion(una_lista, &(elementos[5]), pos_primera) == 0, "Puedo insertar un elemento en la primera posicion");
	pa2m_afirmar(lista_insertar_en_posicion(una_lista, NULL, 50) == 0, "Puedo insertar un elemento NULL");
	pa2m_afirmar(lista_elementos(una_lista) == 7, "Tengo 7 elementos en la lista");
	pa2m_afirmar(son_elementos_correspondientes(una_lista, elementos) == true, "Los 7 elementos agregados son los correspondientes");
	
	lista_destruir(una_lista);
}
void probar_borrar_elemento(){
	lista_t* una_lista = lista_crear();
	int elemento = 10, segundo_elemento = 20, tercer_elemento = 30;

	lista_insertar(una_lista, &elemento);
	lista_insertar(una_lista, &segundo_elemento);
	lista_insertar(una_lista, &tercer_elemento);

	pa2m_afirmar(lista_borrar(una_lista) == 0, "Puedo borrar un elemento de la lista");
	pa2m_afirmar(lista_elementos(una_lista) == 2, "Hay 2 elementos en la lista");
	pa2m_afirmar((lista_elemento_en_posicion(una_lista, 0) == &elemento) && (lista_elemento_en_posicion(una_lista, 1) == &segundo_elemento), "Los elementos que quedaron son los correspondientes");
	pa2m_afirmar(lista_borrar(una_lista) == 0, "Puedo borrar un elemento de la lista");
	pa2m_afirmar((lista_elemento_en_posicion(una_lista, 0) == &elemento), "Los elementos que quedaron son los correspondientes");
	pa2m_afirmar(lista_elementos(una_lista) == 1, "Hay 1 elemento en la lista");
	pa2m_afirmar(lista_borrar(una_lista) == 0, "Puedo borrar un elemento de la lista"); 
	pa2m_afirmar(lista_elementos(una_lista) == 0, "Hay 0 elementos en la lista");

	lista_destruir(una_lista);
}

void probar_borrar_de_posicion(){
	lista_t* una_lista = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30, 40};
	size_t pos = 1, primera_pos = 0, pos_inexistente = 10;

	for(int i = 0; i < 4; i++){
		lista_insertar(una_lista, &(elementos[i]));
	}
	
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, pos) == 0, "Puedo borrar un elemento del medio de la lista");
	pa2m_afirmar(lista_elementos(una_lista) == 3, "Tengo 3 elementos en la lista");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 0) == &(elementos[0]) && lista_elemento_en_posicion(una_lista, 1) == &(elementos[2]) && lista_elemento_en_posicion(una_lista, 2) == &(elementos[3]), "Los elementos que quedaron en la lista son los correspondientes");
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, primera_pos) == 0, "Puedo borrar el primer elemento de la lista");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 0) == &(elementos[2]) && lista_elemento_en_posicion(una_lista, 1) == &(elementos[3]), "Los elementos que quedaron en la lista son los correspondientes");
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, pos_inexistente) == 0, "Puedo borrar un elemento en posicion que no existe");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, 0) == &(elementos[2]), "Los elementos que quedaron en la lista son los correspondientes");
	pa2m_afirmar(lista_elementos(una_lista) == 1, "Tengo 1 elemento en la lista");
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0) == 0, "Puedo borrar toda la lista");

	lista_destruir(una_lista);
}


void probar_devolucion_de_elementos(){
	lista_t* una_lista = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30, 40};
	size_t pos[MAX_POSICIONES] = {0, 2, 1, 3};

	for(int i = 0; i < 4; i++){
		lista_insertar(una_lista, &(elementos[i]));
	}

	pa2m_afirmar(lista_elementos(una_lista) == 4, "Tengo 4 elementos en la lista");
	pa2m_afirmar(lista_ultimo(una_lista) == una_lista->nodo_fin->elemento, "Devuelvo el ultimo elemento de la lista");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, pos[0]) == una_lista->nodo_inicio->elemento, "Devuelvo el elemento en posicion 0");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, pos[2]) == una_lista->nodo_inicio->siguiente->elemento, "Devuelvo el elemento en posicion 1");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, pos[1]) == una_lista->nodo_inicio->siguiente->siguiente->elemento, "Devuelvo el elemento en posicion 2");
	pa2m_afirmar(lista_elemento_en_posicion(una_lista, pos[3]) == una_lista->nodo_inicio->siguiente->siguiente->siguiente->elemento, "Devuelvo el elemento en posicion 3");
	
	lista_destruir(una_lista);
}

void probar_lista_vacia(){
	lista_t* una_lista = lista_crear();

	pa2m_afirmar(lista_vacia(una_lista) == true, "La lista esta vacia");
	pa2m_afirmar(lista_elementos(una_lista) == 0, "La cantidad de elementos en la lista es 0");
	pa2m_afirmar(una_lista->nodo_inicio == NULL, "El primer elemento de la lista es NULL");
	pa2m_afirmar(una_lista->nodo_fin == NULL, "El ultimo elemento de la lista es NULL");
	pa2m_afirmar(lista_borrar(una_lista) == ERROR, "Borrar un elemento en una lista vacia devuelve error");
	pa2m_afirmar(lista_borrar_de_posicion(una_lista, 0) == -1, "Borrar un elemento en una posicion de la lista vacia devuelve error");
	pa2m_afirmar(lista_ultimo(una_lista) == NULL, "Pido el ultimo elemento de una lista vacia, devuelve NULL");

	lista_destruir(una_lista);
}

void probar_funciones_pila(){
	lista_t* pila = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30};

	pa2m_afirmar(lista_apilar(pila, &(elementos[0])) == 0, "Puedo apilar un elemento en una pila vacia");
	pa2m_afirmar(lista_tope(pila) == pila->nodo_fin->elemento, "Devuelve el tope de la pila correspondiente");
	pa2m_afirmar(lista_apilar(pila, &(elementos[1])) == 0, "Puedo apilar un segundo elemento en la pila");
	pa2m_afirmar(lista_tope(pila) == pila->nodo_fin->elemento, "Devuelve el tope de la pila correspondiente");
	pa2m_afirmar(lista_apilar(pila, &(elementos[2])) == 0, "Puedo apilar un tercer elemento en la pila");
	pa2m_afirmar(lista_desapilar(pila) == 0, "Puedo desapilar un elemento");
	pa2m_afirmar(lista_desapilar(pila) == 0, "Puedo desapilar un segundo elemento");
	pa2m_afirmar(lista_desapilar(pila) == 0, "Puedo desapilar toda la pila");
	pa2m_afirmar(lista_tope(pila) == NULL, "La pila esta vacia");
	pa2m_afirmar(lista_apilar(pila, NULL) == 0, "Puedo apilar un elemento NULL");

	lista_destruir(pila);
}

void probar_funciones_cola(){
	lista_t* cola = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30, 40};
   
	pa2m_afirmar(lista_encolar(cola, &(elementos[0])) == 0, "Puedo encolar un elemento en una cola vacia");
	pa2m_afirmar(lista_encolar(cola, &(elementos[1])) == 0, "Puedo encolar un segundo elemento");
	pa2m_afirmar(lista_encolar(cola, &(elementos[2])) == 0, "Puedo encolar un tercer elemento");
	pa2m_afirmar(lista_encolar(cola, &(elementos[3])) == 0, "Puedo encolar un cuarto elemento");

	pa2m_afirmar(lista_primero(cola) == cola->nodo_inicio->elemento, "Devuelvo el primer elemento de la cola");
	
	pa2m_afirmar(lista_desencolar(cola) == 0, "Puedo desencolar un elemento");
	pa2m_afirmar(lista_desencolar(cola) == 0, "Puedo desencolar un segundo elemento");
	pa2m_afirmar(lista_desencolar(cola) == 0, "Puedo desencolar un tercer elemento");
	pa2m_afirmar(lista_desencolar(cola) == 0, "Puedo desencolar toda la cola");
	pa2m_afirmar(lista_primero(cola) == NULL, "La cola esta vacia");
	pa2m_afirmar(lista_encolar(cola, NULL) == 0, "Puedo encolar un elemento NULL");

	lista_destruir(cola);
}

void probar_iterador_externo(){
	lista_t* una_lista = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30};

	for(int i = 0; i < 3; i++){
		lista_insertar(una_lista, &(elementos[i]));
	}
	
	lista_iterador_t* iterador = NULL;
	pa2m_afirmar((iterador = lista_iterador_crear(una_lista)) != NULL, "Puedo crear un iterador");

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true, "El iterador tiene siguiente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &(elementos[0]), "El primer elemento es el correcto");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == true, "Avanzo al 2° elemento");

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true, "El iterador tiene siguiente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &(elementos[1]), "El segundo elemento es el correcto");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == true, "Avanzo al 3° elemento");

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true, "El iterador tiene siguiente");
	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &(elementos[2]), "El tercer elemento es el correcto");
	pa2m_afirmar(lista_iterador_avanzar(iterador) == false, "No hay mas elementos, detiene la iteracion");
	
	lista_iterador_destruir(iterador);
	lista_destruir(una_lista);
}

bool recorrer_lista_entera(void* elemento, void* contador){
    if(elemento && contador)
       (*(int*)contador)++;
    return true;
}

bool recorrer_lista_hasta_contador(void* elemento, void* contador){
	if((*(int*)contador) == 2)
		return false;
	(*(int*)contador)++;
	return true;
}

void probar_iterador_interno(){
	lista_t* una_lista = lista_crear();
	int elementos[MAX_ELEMENTOS] = {10, 20, 30};

	for(int i = 0; i < 3; i++){
		lista_insertar(una_lista, &(elementos[i]));
	}
	int contador = 0;
	pa2m_afirmar(lista_con_cada_elemento(una_lista, NULL, &contador) == 0, "No se puede iterar sin funcion de iteracion");
	pa2m_afirmar(lista_con_cada_elemento(una_lista, recorrer_lista_entera, &contador) == 3, "Puedo recorrer toda la lista con el iterador interno");
	contador = 0;
	pa2m_afirmar(lista_con_cada_elemento(una_lista, recorrer_lista_hasta_contador, &contador) == 2, "Puedo recorrer la lista hasta el segundo elemento");

	for(int i = 0; i < 3; i++){
		lista_borrar(una_lista);
	}
	contador = 0;
	pa2m_afirmar(lista_con_cada_elemento(una_lista, recorrer_lista_entera, &contador) == 0, "Mando una lista vacia, devuelve error");

	lista_destruir(una_lista);
}

void probar_lista_nula(){
	pa2m_afirmar(lista_vacia(NULL) == true, "Lista nula es vacia");
	pa2m_afirmar(lista_elementos(NULL) == 0, "La cantidad de elementos en una lista nula es 0");
	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL, "El primer elemento en una lista nula es nulo");
	pa2m_afirmar(lista_ultimo(NULL) == NULL, "El ultimo elemento en una lista nula es nulo");
	pa2m_afirmar(lista_insertar(NULL, NULL) == ERROR, "Insertar al final de una lista nula devuelve error");
	pa2m_afirmar(lista_insertar_en_posicion(NULL, NULL, 2) == ERROR, "Insertar en una posicion cualquiera de una lista nula devuelve error");
	pa2m_afirmar(lista_insertar_en_posicion(NULL, NULL, 0) == ERROR, "Insertar al principio de una lista nula devuelve error");
	pa2m_afirmar(lista_borrar(NULL) == ERROR, "Borrar el ultimo elemento de una lista nula devuelve error");
	pa2m_afirmar(lista_borrar_de_posicion(NULL, 0) == ERROR, "Borrar el primer elemento de una lista nula devuelve error");
	pa2m_afirmar(lista_borrar_de_posicion(NULL, 5) == ERROR, "Borrar un elemento de una posicion cualquiera de la lista nula devuelve error");
	pa2m_afirmar(lista_apilar(NULL, NULL) == ERROR, "Apilar un elemento en una lista nula devuelve error");
	pa2m_afirmar(lista_desapilar(NULL) == ERROR, "Desapilar un elemento de una lista nula devuelve error");
	pa2m_afirmar(lista_tope(NULL) == NULL, "El tope de una lista nula es nulo");
	pa2m_afirmar(lista_encolar(NULL, NULL) == ERROR, "Encolar un elemento en una lista nula devuelve error");
	pa2m_afirmar(lista_desencolar(NULL) == ERROR, "Desencolar un elemento de una lista nula devuelve error");
	pa2m_afirmar(lista_iterador_crear(NULL) == NULL, "El iterador de una lista nula es nulo");
	pa2m_afirmar(lista_con_cada_elemento(NULL, NULL, NULL) == 0, "Recorrer una lista nula con el iterador interno recorre 0 elementos");

	lista_destruir(NULL);
}
int main(){

	pa2m_nuevo_grupo("PRUEBAS DE LISTA VACIA");
	probar_lista_vacia();

	pa2m_nuevo_grupo("PRUEBAS DE CREACION DE LISTA");
	probar_creacion_lista();

	pa2m_nuevo_grupo("PRUEBAS DE INSERCION");
	probar_insertar_elemento();

	pa2m_nuevo_grupo("PRUEBAS DE INSERCION EN POSICION");
	probar_insertar_en_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION");
	probar_borrar_elemento();

	pa2m_nuevo_grupo("PRUEBAS DE ELIMINACION EN POSICION");
	probar_borrar_de_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE DEVOLUCION DE ELEMENTOS");
	probar_devolucion_de_elementos();

	pa2m_nuevo_grupo("PRUEBAS DE PILA");
	probar_funciones_pila();

	pa2m_nuevo_grupo("PRUEBAS DE COLA");
	probar_funciones_cola();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR EXTERNO");
	probar_iterador_externo();

	pa2m_nuevo_grupo("PRUEBAS DE ITERADOR INTERNO");
	probar_iterador_interno();

	pa2m_nuevo_grupo("PRUEBAS CON LISTA NULA");
	probar_lista_nula();

	pa2m_mostrar_reporte();

	return 0;
}