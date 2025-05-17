#include"../../include/arrayUtils.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef unsigned int uint;
const int ALLOC_CHUNK = 32;

int verify_index_conformity(size_t index, int current_size) {
    if ((int) index >= current_size){
        printf("Error, the index (%zu) is greater than the total number of elements in the array (%i)\n", index, current_size);
        return -1;
    }
    return 0;
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

void toPrintArray(const DynamicArray* array) {

    printf("Array size: %zu\n", array->size);
    printf("Array max capacity: %zu\n", array->capacity);
    for (int i = 0; i < (int) array->size; i++) {
        printf("%i", array->data[i]);
        if (i != (int) array->size -1)
            printf(", ");
        else 
            printf("\n");
    }

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
    array->capacity = array->size;
    return 0;
}


void freeArray(DynamicArray* array) {
    free(array->data);
    free(array);
    array = NULL;
}

size_t getArraySize(const DynamicArray* array) {
    return array->size;
}

int getArrayElement(const DynamicArray* array, size_t index, int* value) {
    const int isIndexValid = verify_index_conformity(index, array->size);
    if (isIndexValid == -1) return -1;
    *value = array->data[index];
    return 0;
}


int setMaximumCapacity(DynamicArray* array, int new_capacity) {
    const int currentSize = array->size;
    if (new_capacity <= currentSize) {
        printf("The new capacity must be stricly greater than the current size of the array.\n Current size: %i New capacity: %i\n", currentSize, new_capacity);
        return -1;
    } else if (new_capacity == (int) array->capacity){
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


int appendArray(DynamicArray* array, int new_value, int alloc_chunk) {
    const uint currentSize = array->size;
    if (currentSize == array->capacity) // increase the capacity if the maximum has been reached
        setMaximumCapacity(array, currentSize + alloc_chunk);

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

int removeArray(DynamicArray* array, int value_to_delete) {

    int cpt = 0;
    int found = 0;
    int size = array->size ;

    if (size == 0) {
        printf("The given array is empty.\n");
        return -1;
    }

    while(cpt < size) { // iterate on the array to find the value to delete
        if (found)
            array->data[cpt - 1] = array->data[cpt];
        else if (array->data[cpt] == value_to_delete)
            found = 1;
        cpt ++;
    }

    if (found) {
        array->size --;
        adjustCapacity(array); // delete the last element of the array
        return 0;
    } else {
        printf("The value: %i is not in the array.\n", value_to_delete);
        return -1;
    }
}


int setArrayElement(const DynamicArray* array, size_t index, int new_value) {
    const int isIndexValid = verify_index_conformity(index, array->size);
    if (isIndexValid == -1) return -1;
    array->data[index] = new_value;
    return 0;
}

int is_slice_index_correct(int start_index, int end_index, int max_index){


    if (start_index > end_index) return -1;

    else if (end_index > max_index) return -1;

    else if (start_index >= 0 &&  end_index >= 0)
        return 0;
    
    return -1;

}


DynamicArray* sliceArray(const DynamicArray* array, int start_index, int end_index) {

    int max_index = array->size;
    if (is_slice_index_correct(start_index, end_index, max_index) == -1){
        printf("Error, the given index (%i and %i) must be different and be comprise between 0 and %i\n", start_index, end_index, max_index);
        return NULL;
    }
    int nb_elements = end_index - start_index;
    DynamicArray* sub_array = createArray(nb_elements); // create a new array with the correct capcity

    if (sub_array == NULL)
        return NULL;
    
    if (start_index >= (int) array->size) // return empty array if the start index is greater then the size of the list
        sub_array->size = 0;
    
    else {
        for (int i = start_index; i < end_index; i++) 
            appendArray(sub_array, array->data[i], 16);
        sub_array->size = nb_elements;
    }
    sub_array->capacity = nb_elements;
    return sub_array;

}


DynamicArray* sortArrayElement(DynamicArray* array) {
    
    int high = array->size - 1;
    int low = 0;
    
    if (high - low <= 15) { // tiny arrays will be sort using insert sort
        insertionSort(array, low, high);
        return array;
    } else { // merge sort otherwise
        static DynamicArray* aux = NULL;
        aux = createArray(array->size);
        mergeSort(array, aux, low, high);
        freeArray(aux);
        aux = NULL;
    }
    
    return array;
}

/**
 * Function that will perform the merging sort
 */
void mergeSort(DynamicArray* array, DynamicArray* aux, int low, int high) {
    if (high <= low) return; // base case, the array is unique and so it is sorted

    int mid = low + (high - low) / 2; // fancy way to comoute the middle to avoid integer overflow
    mergeSort(array, aux, low, mid);
    mergeSort(array, aux, mid + 1, high);
    merge(array, aux, low, mid, high);
}

void merge(DynamicArray* array, DynamicArray* aux, int low, int mid, int high) {

    for (int k = low; k <= high; k++) // store the values in the auxilliary array
        aux->data[k] = array->data[k];
    
    
    // merging: i point to the beginning of the first array and j to the beginning of the second one
    int i = low;
    int j = mid + 1;
    for (int k = low; k <= high; k++) {
        if (i > mid) // if the first array is empty               
            array->data[k] = aux->data[j++];
        else if (j > high)   // if the second array is empty           
            array->data[k] = aux->data[i++];
        else if (aux->data[j] < aux->data[i])  // if the element of thr first array is lower than the second one
            array->data[k] = aux->data[j++];
        else            // the opposite                
            array->data[k] = aux->data[i++];
    }
}

/**
 * Insertion sort function for the array
 */
void insertionSort(DynamicArray* array, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int value = array->data[i]; // store the studied value 
        int j = i;
        
        while (j > low && array->data[j-1] > value) {
            array->data[j] = array->data[j-1]; // delete the value ti put the previous one if it is greater
            j--;
        }
        array->data[j] = value; // restore teh original value to the correct location
    }
}







