#include"../../include/HashMap.h"
#include"../../include/linkedList.h"

#include<string.h>
#include<stdio.h>

typedef unsigned long ulong;
const int sizeTreshold = 0.6;

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
    map->data = malloc(capacity * sizeof(keyValueLinkedList)); // allocate memory for the array of linked lists
    
    if (map->data == NULL) {
        free(map);   
        return NULL;
    }
    // init linked list pointers to NULL
    for (size_t i = 0; i < capacity; i++) 
        map->data[i] = NULL;
    
    return map;
}

void freeMapLinkedList(HashMap* map) {
    for (size_t i = 0;  i < map->capacity; i++) {
        keyValueLinkedList* list = map->data[i];
        if (list != NULL)
            freeKeyValueLinkedList(map->data[i]);
    }
    free(map->data);
}

void freeHashMap(HashMap* map) {
    // free all the linked lists
    freeMapLinkedList(map);
    free(map);
}


int increaseHashMapCapacity(HashMap* map) {
    size_t newCapacity = computeNewCapacity(map->capacity);
    keyValueLinkedList** newValues = malloc(newCapacity * sizeof(keyValueLinkedList));
    if (newValues == NULL) {
        printf("Error, cannot increase map capacity, collisions can be frequent.");
        return -1;
    }
    // init new linked lists
    for (size_t i = 0; i < newCapacity; i++) 
        newValues[i] = NULL;
    
    // rehash old values to keep consistency
    for (size_t i = 0; i < newCapacity; i++) {
        keyValueLinkedList* list = map->data[i];
        if (list != NULL){
            KeyValueNode* currentNode = list->head;
            while(currentNode != NULL) { // iterate on every value at this index
                ulong newIndex = hashCode((unsigned char*) currentNode->key) % newCapacity;
                if (newValues[newIndex] == NULL) // if this is the first values at this index
                    newValues[newIndex] = createKeyValueLinkedList();
                // re create a node, can be optimised be detaching the original node to attach it to the new list ?
                appendKeyValueNode(newValues[newIndex], currentNode->value, currentNode->key);
                currentNode = currentNode->next;
            }
            freeKeyValueLinkedList(list);
        }
    }
    free(map->data); // free the previous array of linked lists
    map->data = newValues;
    map->capacity = newCapacity;

    return 0;
}

size_t computeNewCapacity(size_t currentCapacity){
    if (currentCapacity <= 16) {return currentCapacity += 16;}
    else if (currentCapacity <= 64) {return currentCapacity += 64;}
    else if (currentCapacity <= 256) {return currentCapacity += 256;}
    else if (currentCapacity <= 1024) {return currentCapacity += 1024;}
    else {return currentCapacity += 4096;}
}


int putHashMap(HashMap* map, char* key, GenericValue value) {
    ulong index = hashCode((unsigned char*) key) % map->capacity;
    int status;
    if (map->data[index] == NULL) // first value so we have to init the linked list
        map->data[index] = createKeyValueLinkedList();

    // check if the key is already in the map
    keyValueLinkedList* valuesAtIndex = map->data[index];
    KeyValueNode* node = valuesAtIndex->head;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return 0;
        }
        node = node->next;
    }
    // the key is unknown so we have to create a node for it
    status = appendKeyValueNode(valuesAtIndex, value, key);
    if (status) {
        map->size++;
        if (map->size > sizeTreshold * map->capacity) // increase map capacity to avoid collision
            return increaseHashMapCapacity(map);
    }
    return status;
}

int getHashMapValue(HashMap* map, char* key, GenericValue** value_to_return) {
    ulong index = hashCode((unsigned char*) key) % map->capacity;

    if (map->data[index] == NULL)
        return -1;  // unknown key

    keyValueLinkedList* valuesAtIndex = map->data[index];
    KeyValueNode* mapValue = valuesAtIndex->head;
    while (mapValue != NULL){
        if (strcmp(mapValue->key, key) == 0) {
            *value_to_return = &mapValue->value;
            return 0;
        }
        mapValue = mapValue->next;
    }
    return -1; // unknown key
}


int removeHashMap(HashMap* map, char* key) {
    ulong index = hashCode((unsigned char*) key) % map->capacity;

    keyValueLinkedList* valuesAtIndex = map->data[index];

    if (valuesAtIndex == NULL) {}
        return -1;  // unknown key
    //iterate on the list to find the node which is associated with the key
    int status = removeKeyValueNode(valuesAtIndex, key);
    if (status) 
        map->size--;
    return status;
}

int containsKey(HashMap* map, char* key) {

    ulong index = hashCode((unsigned char*) key) % map->capacity;
    keyValueLinkedList* valuesAtIndex = map->data[index];

    if (valuesAtIndex == NULL)
        return 0;
    // iterate on values at this index
    KeyValueNode* node = valuesAtIndex->head;
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) // if the stored values at the index is the key
            return 1;
        node = node->next;
    }
    return 0;
}

void toPrintHashMap(HashMap* map) {
    printf("[");
    for (size_t i = 0; i<map->capacity; i++) {
        keyValueLinkedList* list = map->data[i];
        if (list != NULL)
            toPrintKeyValueLinkedList(list);
    }
    printf("]\n");
}


