#include"../../include/HashMap.h"
#include"../../include/linkedList.h"

typedef unsigned long ulong;

ulong hashCode(unsigned char *key) {
    ulong hash = 5381; // magic number for the hash function
    int c;
    
    while ((c = *key++)) { 
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

HashMap* createHashMap(size_t capacity) {
    // allocate memory for the hashMap
    HashMap* map = malloc(sizeof(HashMap));
    if (map == NULL)
        return NULL;

    map->size = 0;
    map->capacity = capacity;
    map->data = malloc(capacity * sizeof(linkedList)); // allocate memory for the array of linked lists
    
    if (map->data == NULL) {
        free(map);   
        return NULL;
    }
    // init linked list pointers to NULL
    for (size_t i = 0; i < capacity; i++) 
        map->data[i] = NULL;
    
    return map;
}

void freeHashMap(HashMap* map) {
    // free all the linked list
    for (size_t i = 0;  i < map->capacity; i++) 
        freeLinkedList(map->data[i]);
    
    free(map);
}



int putHashMap(HashMap* map, char* key, GenericValue value) {

    ulong index = hashCode(key) % map->capacity;
    int status;
    if (map->data[index] != NULL) { // if there is already a value at this index, we put it in the associated linked list
        status = appendNode(map->data[index], value);
    } else { // first value so we have to init the linked list
        map->data[index] = createLinkedList();
        status = appendNode(map->data[index], value);
    }

    return status;
}


