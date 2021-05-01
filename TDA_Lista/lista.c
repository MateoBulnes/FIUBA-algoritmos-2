#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

#define ERROR -1

lista_t* lista_crear(){
	lista_t* lista = malloc(sizeof(lista_t)); 
	if(lista == NULL) 
 		return NULL;
 	lista->nodo_inicio = NULL;
 	lista->nodo_fin = NULL;
 	lista->cantidad = 0;
 	return lista;
}

int lista_insertar(lista_t* lista, void* elemento){
	if(lista == NULL) 
		return ERROR;
	
	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t)); 
	if(nuevo_nodo == NULL)
		return ERROR;
	if(lista->cantidad == 0) 
		lista->nodo_inicio = nuevo_nodo;
	else{                     
		lista->nodo_fin->siguiente = nuevo_nodo; 
	}
	lista->nodo_fin = nuevo_nodo;
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;
	(lista->cantidad)++;

	return 0;
}

bool lista_vacia(lista_t* lista){
	if(lista == NULL || lista->cantidad == 0)
		return true;
	return false;
}
bool existe_posicion(size_t cantidad, size_t posicion){
	return(posicion < cantidad);
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){ 
	if(lista == NULL)
		return ERROR;

	if((!existe_posicion(lista->cantidad, posicion)) || (lista->cantidad == 0)) 
		lista_insertar(lista, elemento);
	else{
		nodo_t* nuevo_nodo = malloc(sizeof(nodo_t)); 
		if(nuevo_nodo == NULL)
			return ERROR;

		size_t contador = 0;
		nodo_t* aux = lista->nodo_inicio, *anterior = NULL; 
		while(posicion != contador){ 
			anterior = aux; 
			aux = aux->siguiente;
			contador++;
		}
		nuevo_nodo->elemento = elemento; 
		nuevo_nodo->siguiente = aux;
		if(posicion > 0) 
			anterior->siguiente = nuevo_nodo;
		else 
			lista->nodo_inicio = nuevo_nodo;
		(lista->cantidad)++;
	}
	return 0;
}

int lista_borrar(lista_t* lista){
	if(lista == NULL){
		return ERROR;
	}
	if(lista->cantidad == 0)
		return ERROR;
	
	nodo_t* aux = lista->nodo_inicio;
	nodo_t* anterior = NULL;

	while(aux != lista->nodo_fin){
		anterior = aux;
		aux = aux->siguiente;
	}
	if(lista->cantidad > 1){	
		anterior->siguiente = NULL;
		lista->nodo_fin = anterior;
	}
	free(aux);
	if(lista->cantidad <= 1){ 
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	}
	(lista->cantidad)--;

	return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista_vacia(lista))
		return ERROR;
	if((!existe_posicion(lista->cantidad, posicion)) || (lista->cantidad == posicion+1))
		lista_borrar(lista);
	else{
		size_t contador = 0;
		nodo_t* aux = lista->nodo_inicio, *anterior = NULL;
		while(posicion != contador){
			anterior = aux;
			aux = aux->siguiente;
			contador++;
		}
		if(posicion > 0)
			anterior->siguiente = aux->siguiente;
		else
			lista->nodo_inicio = aux->siguiente;
		free(aux);
		(lista->cantidad)--;
	}
	return 0;
}

void* lista_ultimo(lista_t* lista){
	if(lista_vacia(lista))
		return NULL;
	return lista->nodo_fin->elemento;
}
size_t lista_elementos(lista_t* lista){
	if(lista == NULL)
		return 0;
	return (lista->cantidad);
}
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(lista_vacia(lista))
		return NULL;
	size_t contador = 0;
	nodo_t* aux = lista->nodo_inicio;
	while(contador != posicion){
		aux = aux->siguiente;
		contador++;
	}
	return aux->elemento;
}


int lista_apilar(lista_t* lista, void* elemento){
	int resultado = lista_insertar(lista, elemento);
	return resultado;
}

int lista_desapilar(lista_t* lista){
	int resultado = lista_borrar(lista);
	return resultado;
}

void* lista_tope(lista_t* lista){
	if(lista_vacia(lista))
		return NULL;
	void* tope = lista_ultimo(lista);
	return tope;
}

int lista_encolar(lista_t* lista, void* elemento){
	int resultado = lista_insertar(lista, elemento);
	return resultado;
}

void* lista_primero(lista_t* lista){
	if(lista_vacia(lista))
		return NULL;
	void* elemento = lista_elemento_en_posicion(lista, 0);
	return elemento;
}

int lista_desencolar(lista_t* lista){
	int resultado = lista_borrar_de_posicion(lista, 0);
	return resultado;
}

void lista_destruir(lista_t* lista){
	if(lista == NULL)
		return;
	nodo_t* aux = NULL;

	while(lista->nodo_inicio != NULL){
		aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(aux);
	}
	free(lista);
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(lista == NULL)
		return NULL;
	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(iterador == NULL)
		return NULL;
	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(iterador == NULL)
		return false;
	return iterador->corriente;
}
bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!lista_iterador_tiene_siguiente(iterador))
		return false;
	iterador->corriente = iterador->corriente->siguiente;
	return iterador->corriente;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if((lista_vacia(iterador->lista)) || (iterador->corriente == NULL))
		return NULL;
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void* elemento, void*), void *contexto){ 
	if(lista_vacia(lista) || (funcion == NULL))
		return 0;

	nodo_t* nodo_aux = lista->nodo_inicio;
	size_t cant_recorridos = 0;

	while((nodo_aux != NULL) && (funcion(nodo_aux->elemento, contexto) == true)){
		nodo_aux = nodo_aux->siguiente;
		cant_recorridos++;
	}
	if((*(int*)contexto) == 0) 
		return 0;

	return cant_recorridos;
}