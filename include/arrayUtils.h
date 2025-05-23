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
 * Function to slice a dynamic array to get a subpart of it
 * 
 * @param DynamicArray the pointer of the origin structure
 * @param start_index the start index of the original array
 * @param end_index the end index of the original array(not included in the sub array)
 * 
 * @return the pointer of the sub array (can be NULL if error)
 */
DynamicArray* sliceArray(const DynamicArray* array, int start_index, int end_index) ;


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
 * @param alloc_chunk: integer to determine how much space to add if the array is full
 * 
 * @return 0 if success -1 if an error has occured
 */
int appendArray(DynamicArray* array, int new_value, int alloc_chunk);

/**
 * Function to remove a value of the dynamic array
 * It will remove only the first occurence of the value if it is found
 * 
 * @param DynamicArray the pointer of the structure
 * @param value_to_delete: integer to store in teh array
 * 
 * @return 0 if success -1 if an error has occured
 */
int removeArray(DynamicArray* array, int value_to_delete);


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

/**
 * Function to sort the array element by ascending order (merge sort)
 * 
 * @param DynamicArray the pointer of the structure
 * 
 * @return 0 if success -1 if an error has occured
 */
DynamicArray* sortArrayElement(DynamicArray* array);


/**
 * Function to sort the array element by ascending order (merge sort)
 * 
 * @param DynamicArray the pointer of the structure
 * @param low index of the beginning point for the sorting process
 * @param low index of the ending point for the sorting process
 * 
 */
void insertionSort(DynamicArray* array, int low, int high);

/**
 * Function to sort the array element by ascending order (merge sort)
 * 
 * @param array the pointer of the structure
 * @param aux the pointer of the auxilliary array structure (tmp to store data)
 * @param low index of the beginning point of the first sub array
 * @param high index of the ending point of the second array
 * 
 */
void mergeSort(DynamicArray* array, DynamicArray* aux, int low, int high);

/**
 * Function to merge sub arrays in one 
 * @param array the pointer of the structure
 * @param aux the pointer of the auxilliary array structure (tmp to store data)
 * @param low index of the beginning point of the first sub array
 * @param mid index of the starting point of the second array
 * @param high index of the ending point of the first global array
 * 
 */
void merge(DynamicArray* array, DynamicArray* aux, int low, int mid, int high);

/**
 * Function to print the value in the dynamic array
 * 
 * @param DynamicArray the pointer of the structure
 * 
 */
void toPrintArray(const DynamicArray* array);


#endif