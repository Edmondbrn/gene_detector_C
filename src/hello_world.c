#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"arrayUtils.h"
#include"linkedList.h"



int main(void) {
    
    double cpu_time_used;
    clock_t start, end;

    // DynamicArray* array = createArray(1000);

    // if (array == NULL)
    //     return -1;

    // start = clock();
    // for (int i = 1000000; i != 0; i-- )
    //     appendArray(array, i, 64);
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    // printf("Insertion time for 1000000 elements in arrayList %f seconds\n", cpu_time_used);
    // adjustCapacity(array);
    // freeArray(array);

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

    linkedList* listGeneric = createList();

    appendNode(listGeneric, createIntValue(1));
    appendNode(listGeneric, createFloatValue(2.0));
    appendNode(listGeneric, createCharValue('b'));
    appendNode(listGeneric, createStringValue("Ara ara."));

    printf("Generic linked list content:\n");
    toPrint(listGeneric);

    freeList(listGeneric);

    return 0;
}