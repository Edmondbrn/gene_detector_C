#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include"arrayUtils.h"
#include"linkedList.h"



int main(void) {

    linkedList* listGeneric = createLinkedList();

    appendNode(listGeneric, createIntValue(1));
    appendNode(listGeneric, createFloatValue(2.0));
    appendNode(listGeneric, createCharValue('b'));
    appendNode(listGeneric, createStringValue("Ara ara."));

    printf("Generic linked list content before suppression:\n");
    toPrint(listGeneric);

    removeNode(listGeneric, createStringValue("Ara ara."));

    printf("Generic linked list content after suppression:\n");
    toPrint(listGeneric);

    freeLinkedList(listGeneric);

    return 0;
}

