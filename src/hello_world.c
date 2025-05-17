#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"arrayUtils.h"
#include"linkedList.h"



int main(void) {
    
    double cpu_time_used;
    clock_t start, end;

    DynamicArray* array = createArray(1000);

    if (array == NULL)
        return -1;

    start = clock();
    for (int i = 1000000; i != 0; i-- )
        appendArray(array, i, 64);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Insertion time for 1000000 elements in arrayList %f seconds\n", cpu_time_used);
    adjustCapacity(array);
    freeArray(array);

    linkedList* list = createList();

    if (list == NULL)
        return -1;

    start = clock();
    for (int i = 1000000; i != 0; i-- )
        appendNode(list, createIntValue(i));
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Insertion time for 1000000 elements in linkedList %f seconds\n", cpu_time_used);
    freeList(list);

    return 0;
}