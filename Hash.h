#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stddef.h>

 
typedef struct hash hash_t;
typedef struct hash_iter hash_iter_t;
typedef void (*hash_destruir_dato_t)(void *);

//Crea la tabla hash
hash_t *hash_crear(hash_destruir_dato_t destruir_dato);

//Guarda un dato en una clave de la tabla hash
bool hash_guardar(hash_t *hash, const char *clave, void *dato);

//Borra los elementos de una clave de la tabla hash
void *hash_borrar(hash_t *hash, const char *clave);

//Obtiene el elemento en una clave de la tabla hash
void *hash_obtener(const hash_t *hash, const char *clave);

//Devuelve true si una clave pertenece a la tabla o false si no
bool hash_pertenece(const hash_t *hash, const char *clave);

//Devuelve el tamaño de la tabla hash
size_t hash_cantidad(const hash_t *hash);

//Destruye la tabla hash
void hash_destruir(hash_t *hash);


/* ******************************************************************
 *                    Funciones de Iteracion
 * *****************************************************************/

//Crea el iterador
hash_iter_t *hash_iter_crear(const hash_t *hash);

//Avanza el iterador
bool hash_iter_avanzar(hash_iter_t *iter);

//Ve el elemento actual en el que se encuentra el iterador
const char *hash_iter_ver_actual(const hash_iter_t *iter);

//Devuelve True si el iterador se encuentra al final o false si no
bool hash_iter_al_final(const hash_iter_t *iter);

//Destruye el iterador
void hash_iter_destruir(hash_iter_t* iter);

#endif // HASH_H
