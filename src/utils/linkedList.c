#include"../../include/linkedList.h"
#include<stdlib.h>
#include<stdio.h>

linkedList* createList() {
    linkedList* list = malloc(sizeof(linkedList));

    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    return list;
}


GenericValue createIntValue(int value) {
    GenericValue genericValue; 
    genericValue.type = INT_TYPE;
    genericValue.data.intValue = value;
    return genericValue;
}


GenericValue createFloatValue(float value) {
    GenericValue genericValue; 
    genericValue.type = FLOAT_TYPE;
    genericValue.data.floatValue = value;
    return genericValue;
}

GenericValue createCharValue(char value) {
    GenericValue genericValue; 
    genericValue.type = CHAR_TYPE;
    genericValue.data.charValue = value;
    return genericValue;
}

GenericValue createStringValue(char* value) {
    GenericValue genericValue; 
    genericValue.type = STRING_TYPE;
    genericValue.data.stringValue = value;
    return genericValue;
}

Node* createNode(GenericValue value) {

    Node* node = malloc(sizeof(Node));

    if (node == NULL)
        return NULL;
    
    node->value = value;
    node->next = NULL;
    return node;
}

int appendNode(linkedList* list, GenericValue value) {

    Node* new_node = createNode(value);

    if (new_node == NULL)
        return -1;

    if (list->head == NULL) { // if the list is empty
        list->head = new_node; 
        list->tail = new_node;
    } else {
        list->tail->next = new_node; // the last node point to the new node
        list->tail = new_node;
    }
    return 0;
}


void freeList(linkedList* list) {

    Node* head = list->head;
    Node* tmp = NULL;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(list);
}
