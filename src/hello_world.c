#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"arrayUtils.h"



int main(void) {

    DynamicArray* array = createArray(100000);

    for (int i = 100000; i != 0; i-- )
        appendArray(array, i);


    clock_t start, end;
    double cpu_time_used;
    printf("Test sort function\n");

    start = clock();
    DynamicArray* sorted_array = sortArrayElement(array);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sort time: %f seconds\n", cpu_time_used);

    freeArray(array);

    return 0;
}