#ifndef HASHMAP_H
#define HASHMAP_H

#include"linkedList.h"

/**
 * Structure to constitute a hashmap to store generic values through linked list
 */
typedef struct {

    linkedList** data; // array of linked lists
    size_t size;
    size_t capacity;

} HashMap;


/**
 * Function to hash a string
 * It is used for the hashing process for HashMap
 */
unsigned long hashCode(unsigned char *key);


/**
 * Function to init a new HashMap structure instance
 */
HashMap* createHashMap(size_t capacity);

/**
 * Function to free the HashMap heap memory
 */
void freeHashMap(HashMap* map);

/**
 * Function to increase map capacity to avoid collision
 */
int increaseHashMapCapacity(HashMap* map);

/**
 * Function to add a new value to the given HashMap structure
 */
int putHashMap(HashMap* map, char* key, GenericValue value);


/**
 * Function to remove a value from a HashMap structure thnaks to the key
 */
int removeHashMap(HashMap* map, char* key);


#endif