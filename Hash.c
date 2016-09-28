#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

#define TAM_INICIAL 100
//LE VOY A PONER G A TODAS LAS DOCUMENTACIONES QUE HICE YO, TRATA DE PONERLE L A LAS TUYAS*
//*Son documentaciones para nosotros, y hay que borrarlas para la entrega


//LA ESTRUCTURA NODO_HASH G
typedef struct nodo_hash {
	const char* clave;
	void* dato;
	estado; //Me faltaria esto del estado G
} nodo_hash_t;

//LA ESTRUCTURA HASH G
struct hash {
    size_t cant;
    size_t tam;
    hash_destruir_dato_t destruir_dato;
    nodo_hash_t** tabla;
};

//LA ESTRUCTRUA ITERADORA DE HASH G
struct hash_iter {
    const hash_t* hash;
    size_t pos;
};

//CREAR UN NODO_HASH (Es una funcion auxiliar para facilitar el creado de los nodos) G
nodo_hash_t* nodo_hash_crear(const char *clave, void *dato){
	nodo_hash_t* nodo = malloc(sizeof(nodo_hash_t));
	if (nodo == NULL){	
	 return NULL;
	}
	nodo->clave = strdup(clave);
	nodo->dato = dato;
	nodo->estado = //Me faltaria el estado para incializarlo, pero seria que tiene algo adentro G
	return nodo;
}

//FUNCION PARA CREAR EL HASH G
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	if (hash == NULL){
	 return NULL;
	}		
	hash->tabla = malloc(TAM_INICIAL, sizeof(nodo_hash_t));
	if (hash->tabla == NULL) {
		free(hash);
		return NULL;
	}
	hash->cant = 0;
	hash->tam = TAM_INICIAL;
	hash->destruir_dato = destruir_dato;
	return hash;
}
