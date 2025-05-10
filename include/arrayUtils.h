#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include<stdlib.h>

/**
 * Structure to represent a dynamic array that supports
 * dynamic allocations and removals
 */
typedef struct {

    int* data; // pointer to the data
    size_t size; // number of elements in the array
    size_t capacity; // total allocated capacity (size_t will self adapt to the data type)

} DynamicArray;


/**
 * Function to create a dynamic array
 * 
 * @param size_t capacity: the maximum capacity at the initiation
 * @return DynamicArray pointer
 */
DynamicArray* createArray(size_t capacity);

/**
 * Function to create an independant clone of a dynamic array
 * 
 * @param DynamicArray* the pointer of the array to clone
 * @param DynamicArray* the pointer of the clone array (will be updated by the function)
 * 
 * @return 0 if success -1 if an error has occured
 */
int copy(DynamicArray* array, DynamicArray* clone);



/**
 * Function to free a dynamic array structure
 * 
 * @param DynamicArray* the pointer of the array to free
 */
void freeArray(DynamicArray* array);

/**
 * Function to get the size of the dynamic array
 * 
 * @param DynamicArray the pointer of the structure
 * 
 * @return the size of the array
 */
size_t getArraySize(const DynamicArray* array);


/**
 * Function to remove unused memory allocation for the dynamic array
 * @param DynamicArray the pointer of the structure
 * 
 * @return 0 if success -1 if an error has occured
 */
int adjustCapacity(DynamicArray* array);

/**
 * Function to add a new value at the end of the dynamic array
 * If the maximum capacity has been reached, it will add 16 more spaces
 * 
 * @param DynamicArray the pointer of the structure
 * @param new_value: integer to store in teh array
 * 
 * @return 0 if success -1 if an error has occured
 */
int appendArray(DynamicArray* array, int new_value);


/**
 * Function to add a new value at the end of the dynamic array
 * If the maximum capacity has been reached, just one space will be added
 * Use this function for rare addition in a full list
 * 
 * @param DynamicArray the pointer of the structure
 * @param new_value: integer to store in teh array
 * 
 * @return 0 if success -1 if an error has occured
 */
int lazyAppendArray(DynamicArray* array, int new_value);


/**
 * Function to increase or adapt the size of the dynamic array
 * It will send an erro message if the new capacity is lower than the the current size of the array
 * 
 * @param DynamicArray the i=pointer of the concerned array
 * @param new_capacity the new capacity of the array
 * 
 * @return 0 if everything is okey, -1 otherwise
 */
int setMaximumCapacity(DynamicArray* array, int new_capacity);


/**
 * Function to get the value of a specified index in the array
 * 
 * @param DynamicArray the pointer of the structure
 * @param index the index in the array
 * @param value: the pointer of the variable to store the value in the array
 * 
 * @return 0 if success -1 if an error has occured
 */
int getArrayElement(const DynamicArray* array, size_t index, int* value);


/**
 * Function to get the value of a specified index in the array
 * 
 * @param DynamicArray the pointer of the structure
 * @param index the index in the array
 * @param value: the new value
 * 
 * @return 0 if success -1 if an error has occured
 */
int setArrayElement(const DynamicArray* array, size_t index, int new_value);


#endif