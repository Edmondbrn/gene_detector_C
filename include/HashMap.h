#ifndef HASHMAP_H
#define HASHMAP_H

#include"linkedList.h"

/**
 * Structure to constitute a hashmap to store generic values through linked list
 */
typedef struct {

    keyValueLinkedList** data; // array of linked lists
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
 * 
 * @param capacity the initial capacity, if the map has to be big, a huge initial capacity will increase performance
 * 
 * @return a pointer of teh hashmap structure
 */
HashMap* createHashMap(size_t capacity);

/**
 * Function to free the HashMap heap memory
 * 
 * @param map the pointer of the hash map structure
 */
void freeHashMap(HashMap* map);

/**
 * Function to increase map capacity to avoid collision
 * 
 * @param map the pointer of the hash map structure
 * 
 * @return 0 if everything is ok, -1 otherwise
 */
int increaseHashMapCapacity(HashMap* map);

/**
 * Function to compute the new capacity of the hash map to avoid collision
 * 
 * @param currentCapacity the current capacity of the hash map
 * 
 * @return the new capcity
 */
size_t computeNewCapacity(size_t currentCapacity);

/**
 * Function to add a new value to the given HashMap structure
 * 
 * @param map the pointer of the hash map structure
 * @param key the string key to add
 * @param value the generic value to add in the map
 * 
 * @return 0 if everything is ok, -1 otherwise
 */
int putHashMap(HashMap* map, char* key, GenericValue value);

/**
 * Function to get the value stored in a hashmap thnaks to its key
 * 
 * @param map the pointer of the hash map structure
 * @param key the string key to add
 * @param value_to_return the value to store the result of the get function
 */
int getHashMapValue(HashMap* map, char* key, GenericValue** value_to_return);

/**
 * Function to remove a value from a HashMap structure thnaks to the key
 * 
 * @param map the pointer of the hash map structure
 * @param key the string key to remove
 */
int removeHashMap(HashMap* map, char* key);


/**
 * Function to print the content of the hash map
 * @param map the pointer of the hash map structure
 */
void toPrintHashMap(HashMap* map);


#endif