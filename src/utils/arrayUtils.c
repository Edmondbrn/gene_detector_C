#include"../../include/arrayUtils.h"
#include<stdlib.h>
#include<stdio.h>

typedef unsigned int uint;
const int ALLOC_CHUNK = 16;

int verify_index_conformity(size_t index, int current_size) {
    if (index >= current_size){
        printf("Error, the index (%i) is greater than the total number of elements in the array (%i)\n", index, current_size);
        return -1;
    } else if (index < 0) {
        printf("Error, the index cannot be negative.\n");
        return -1;
    }
}

DynamicArray* createArray(size_t initial_capacity) {

    DynamicArray* array = malloc(sizeof(DynamicArray)); // create an allocation for the array

    if (array == NULL)
        return NULL;

    array->data = malloc(sizeof(int) * initial_capacity); // add the classic array to store the data
    if (array->data == NULL) {
        free(array);
        return NULL;
    }
    // init default values
    array->size = 0;
    array->capacity = initial_capacity;
    return array;
}

int copy(DynamicArray* array, DynamicArray* clone) {
    int* clone_data = malloc(sizeof(int) * array->capacity);
    if (clone_data == NULL)
        return -1;
    // copy the old data into the new one
    memcpy(clone_data, array->data, sizeof(int) * array->size);
    clone->capacity = array->capacity;
    clone->size = array->size;
    return 0;
}


int adjustCapacity(DynamicArray* array) {
    int* adjust_data = malloc(sizeof(int) * array->size);
    if (adjust_data == NULL)
        return -1;
    memcpy(adjust_data, array->data, sizeof(int) * array->size);
    free(array->data);
    array->data = adjust_data;
    return 0;
}


void freeArray(DynamicArray* array) {
    free(array->data);
    free(array);
}

size_t getArraySize(DynamicArray* array) {
    return array->size;
}

int getArrayElement(const DynamicArray* array, size_t index, int* value) {
    const int isIndexValid = verify_index_conformity(index, array->size);
    if (isIndexValid == -1) return -1;
    *value = array->data[index];
    return 0;
}


int setMaximumCapacity(DynamicArray* array, int new_capacity) {
    const uint currentSize = array->size;
    if (new_capacity <= currentSize) {
        printf("The new capacity must be stricly greater than the current size of the array.\n Current size: %i New capacity: %i\n", currentSize, new_capacity);
        return -1;
    } else if (new_capacity == array->capacity){
        return 0;
    } else {
        int* new_data = malloc(sizeof(int) * new_capacity);
        if (new_data == NULL)
            return -1;
        // copy the old data into the new one and free the old one
        memcpy(new_data, array->data, sizeof(int) * array->size);
        free(array->data);
        array->data = new_data;
        array->capacity = new_capacity;
        return 0;
    }
}


int appendArray(DynamicArray* array, int new_value) {
    const uint currentSize = array->size;
    if (currentSize == array->capacity) // increase the capacity if the maximum has been reached
        setMaximumCapacity(array, currentSize + ALLOC_CHUNK);

    array->data[currentSize] = new_value;
    array->size ++;
    return 0;
}

int lazyAppendArray(DynamicArray* array, int new_value) {
    const uint currentSize = array->size;
    if (currentSize == array->capacity) // increase the capacity if the maximum has been reached
        setMaximumCapacity(array, currentSize + 1); // the lazy addition is here

    array->data[currentSize] = new_value;
    array->size ++;
    return 0;
}



int setArrayElement(const DynamicArray* array, size_t index, int new_value) {
    const int isIndexValid = verify_index_conformity(index, array->size);
    if (isIndexValid == -1) return -1;
    array->data[index] = new_value;
}




