#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "f_hash.c"


#define TAM_INICIAL 127
#define VALOR_REDIMENSION 2
#define PORCENTAJE_REDIMENSION 70

//LE VOY A PONER G A TODAS LAS DOCUMENTACIONES QUE HICE YO, TRATA DE PONERLE L A LAS TUYAS
//Son documentaciones para nosotros, y hay que borrarlas para la entrega

//ENUMERA LOS ESTADOS L
typedef enum {VACIO, BORRADO, LLENO} estado_t;

//LA ESTRUCTURA NODO_HASH G
typedef struct nodo_hash {
    char* clave;
    void* dato;
    estado_t estado;
} nodo_hash_t;

//LA ESTRUCTURA HASH G
struct hash {
    size_t cantidad;
    size_t tamanio;
    int borrados;
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
    for(int i = 0; i < TAM_INICIAL; i++){
        hash->tabla[i].estado = VACIO;
    }
    hash->borrados = 0;
    hash->cantidad = 0;
    hash->tamanio = TAM_INICIAL;
    hash->destruir_dato = destruir_dato;
    return hash;
}

//Devuelve la cantidad de elementos guardados L
size_t hash_cantidad(const hash_t *hash){
    return hash->cantidad;
}

//BUSCA UN ELEMENTO EN EL HASH Y DEVUELVE SU POSICION L
//DEVUELVE -1 SI NO ESTA O SI EL HASH ESTA VACIO//
int hash_buscar(const hash_t *hash, const char*clave){
    if (hash->cantidad == 0){
        return -1;
    }
    int pos = stringToHash(clave, (int)hash->tamanio);
    while(hash->tabla[pos].estado != VACIO){
        if(*(hash->tabla[pos].clave) == *clave){
            return pos;
        }
        pos++;
    }
    return -1;
}  

//Devuelve si la clave pertenece o no al hash
bool hash_pertenece(const hash_t *hash, const char *clave){
    return (hash_buscar(hash, clave) >= 0);
}

bool hash_redimensionar(hash_t *hash, size_t tam_nuevo){
    //Creo un hash auxiliar G
    hash_t* hash_nuevo = hash_crear(hash->destruir_dato);
    if (hash_nuevo == NULL){ 
        return false;
    }
    hash_nuevo->tamanio = tam_nuevo;
    
    //Para asegurarme de que la tabla nueva va estar vacia G

    //Asigno memoria para el tamaño nuevo al hash auxiliar G
    hash_nuevo->tabla = malloc(tam_nuevo * sizeof(nodo_hash_t));
    if (hash_nuevo->tabla == NULL) {
        free(hash_nuevo);
        return false;
    }
    //Hasheo  el hash auxiliar con los valores del hash original G
    for (int pos = 0; pos < hash->tamanio; pos++) {
        if (hash->tabla[pos].estado == LLENO){
                hash_guardar(hash_nuevo, hash->tabla[pos].clave, hash->tabla[pos].dato);
        }
                //Destruyo ambos valores para poder reemplazar luego con los del hash_nuevo G
            free(hash->tabla[pos].clave);
        
    }
    
    //Destruyo la tabla original y la reemplazo con el hash_nuevo que ya tiene adentro los mismos elementos y mas memoria alocada G
    free(hash->tabla);
    hash->tamanio = hash_nuevo->tamanio;
    hash->tabla = hash_nuevo->tabla;
    hash->cantidad = hash_nuevo->cantidad;
    //Destruyo el hash auxiliar G
    return true;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
    if((hash->cantidad + hash->borrados) >= hash->tamanio / PORCENTAJE_REDIMENSION){
        if(!hash_redimensionar(hash, hash->tamanio*VALOR_REDIMENSION)){
            return false;
        }
    }

    int pos = stringToHash(clave, (int)hash->tamanio);
    if(hash_pertenece(hash, clave)){
        hash->destruir_dato(hash->tabla[pos].dato);
        hash->tabla[pos].dato = dato;
    }
    else{
        char *clave_duplicado = malloc(sizeof(char *));
        strcpy(clave_duplicado, clave);
        while(hash->tabla[pos].estado == LLENO){
            pos++;
        }
        hash->tabla[pos].clave = clave_duplicado;
        hash->tabla[pos].dato = dato;
        hash->tabla[pos].estado = LLENO;
        
    }
    hash->cantidad++;
    return true;
}      
        
void *hash_borrar(hash_t *hash, const char *clave){
    int posicion = hash_buscar(hash, clave);
    if(posicion == -1){
        return NULL;
    }

    else{
        hash->tabla[posicion].estado = BORRADO;
        hash->borrados++;
        return hash->tabla[posicion].dato;
    }
}

void hash_destruir(hash_t *hash){
    for(int i = 0; i < hash->tamanio; i++){
        if(hash->tabla[i].estado == LLENO){
            hash->destruir_dato(hash->tabla[i].dato);
        }
    }
    free(hash->tabla);
    free(hash);
}
        
    
//----------------------FUNCIONES DE ITERACION-------------------------------------------------------------
hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t* hash_iter = malloc(sizeof(hash_iter_t));
    if (hash_iter == NULL){
     return NULL;
    }
    hash_iter->hash = hash;
    if (hash_cantidad(hash) == 0){
        hash_iter->posicion = hash->tamanio;
    }
    else{
        int i = 0;
        while((i<hash->tamanio) && (hash->tabla[i].estado != LLENO)){
            i++;
        }
        hash_iter->posicion = i;
    }
    return hash_iter;
}


bool hash_iter_avanzar(hash_iter_t *iter){
    if (hash_iter_al_final(iter)){
    return false;
    }
    iter->posicion++;
    while((!hash_iter_al_final(iter)) && (iter->hash->tabla[iter->posicion].estado != LLENO)){
        iter->posicion++;
    }
    return true;
}


const char *hash_iter_ver_actual(const hash_iter_t *iter){
    return iter->hash->tabla[iter->posicion].clave;
}


bool hash_iter_al_final(const hash_iter_t *iter){
    if(iter->posicion == iter->hash->tamanio){
        return true;
    }
    return false;
}


void hash_iter_destruir(hash_iter_t* iter){
    free(iter);
}
