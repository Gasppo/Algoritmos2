#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "f_hash.c"

#define TAM_INICIAL 127
//LE VOY A PONER G A TODAS LAS DOCUMENTACIONES QUE HICE YO, TRATA DE PONERLE L A LAS TUYAS
//Son documentaciones para nosotros, y hay que borrarlas para la entrega

//ENUMERA LOS ESTADOS L
typedef enum {VACIO, BORRADO, LLENO} estado_t;

//LA ESTRUCTURA NODO_HASH G
typedef struct nodo_hash {
    const char* clave;
    void* dato;
    estado_t estado;
} nodo_hash_t;

//LA ESTRUCTURA HASH G
struct hash {
    size_t cantidad;
    size_t tamanio;
    hash_destruir_dato_t destruir_dato;
    //VA UN SOLO ASTERIZCO PORQUE EL VECTOR TIENE LOS NODOS ADENTRO L
    nodo_hash_t* tabla;
};

//LA ESTRUCTRUA ITERADORA DE HASH G
struct hash_iter {
    const hash_t* hash;
    size_t posicion;
};

//----------------------Primitivas del hash------------------------

//FUNCION PARA CREAR EL HASH G
hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t* hash = malloc(sizeof(hash_t));
    if (hash == NULL){
     return NULL;
    }

    hash->tabla = malloc(TAM_INICIAL * sizeof(nodo_hash_t));
    if (hash->tabla == NULL) {
        free(hash);
        return NULL;
    }

    //PONE TODOS LOS ESTADOS EN VACIO L
    for(int i = 0; i < TAM _INICIAL; i++){
        hash->tabla[i].estado = VACIO;
    }

    hash->cantidad = 0;
    hash->tamanio = TAM_INICIAL;
    hash->destruir_dato = destruir_dato;
    return hash;
}

//Devuelve la cantidad de elementos guardados L
size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

//Devuelve si la clave pertenece o no al hash
bool hash_pertenece(const hash_t *hash, const char *clave){
	if (hash->cantidad == 0){
		return false;
	}
	int pos = stringToHash(clave, hash->tamanio);
	if(hash->tabla[pos].estado == VACIO || hash->tabla[pos].estado == BORRADO){
		return false;
	}
	return true;
}
	 


bool hash_redimensionar(hash_t *hash, size_t tam_nuevo){
        //Creo un hash auxiliar G
	hash_t* hash_nuevo = hash_crear(hash->destruir_dato);
	if (hash_nuevo == NULL){ 
		return false;
	}
	hash_nuevo->tamanio = tam_nuevo;
	
	//Para asegurarme de que la tabla nueva va estar vacia G
	free(hash_nuevo->tabla);
	//Asigno memoria para el tamaño nuevo al hash auxiliar G
	hash_nuevo->tabla = malloc(tam_nuevo, sizeof(nodo_hash_t));
	if (hash_nuevo->tabla == NULL) {
		free(hash_nuevo);
		return false;
	}
	//Hasheo  el hash auxiliar con los valores del hash original G
	for (int pos = 0; pos < hash->tamanio; pos++) {
		if (hash->tabla[pos]->estado == OCUPADO){
				hash_guardar(hash_nuevo, hash->tabla[pos]->clave, hash->tabla[pos]->dato);
		}
		        //Destruyo ambos valores para poder reemplazar luego con los del hash_nuevo G
			free(hash->tabla[i]->clave);
			free(hash->tabla[i]);
		
	}
	
	//Destruyo la tabla original y la reemplazo con el hash_nuevo que ya tiene adentro los mismos elementos y mas memoria alocada G
	free(hash->tabla);
	hash->tamanio = hash_nuevo->tamanio;
	hash->tabla = hash_nuevo->tabla;
	hash->cantidad = hash_nuevo->cantidad;
	//Destruyo el hash auxiliar G
	free(hash_nuevo);
	return true;
}


bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if(hash->cantidad>=pila->tamanio){
        if(!hash_redimensionar(hash, hash->tamanio*2){
            return false;
			}
		}
	int pos = stringToHash(clave, hash->tamanio); //No se como aplicar bien la funcion G 
	if(hash_pertenece(hash, clave)){
	    hash->destruir_dato(hash->tabla[pos]->dato);
	    hash->tabla[pos]->dato = dato;
	}
	else{
		hash->tabla[pos]->clave = clave;
		hash->tabla[pos]->dato = dato;
		hash->tabla[pos].estado = LLENO;
		
	}
	   hash->cantidad++;
	   return true;
    }      
        
           
           
        
    
    
    



//----------------------Primitivas de los nodos--------------------

//CREAR UN NODO_HASH (Es una funcion auxiliar para facilitar el creado de los nodos) G
/*nodo_hash_t* nodo_hash_crear(const char *clave, void *dato){
    nodo_hash_t* nodo = malloc(sizeof(nodo_hash_t));
    if (nodo == NULL){  
     return NULL;
    }
    nodo->clave = strdup(clave);
    nodo->dato = dato;
    nodo->estado = VACIO;
    return nodo;
}/*
//----------------------Primitivas del iterador--------------------
