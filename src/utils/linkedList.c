#include"../../include/linkedList.h"
#include<stdlib.h>
#include<stdio.h>

linkedList* createLinkedList() {
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

int removeNode(linkedList* list, GenericValue value) {

    Node* node = list->head;
    Node* previousNode = NULL;

    while (node != NULL) {
        GenericValue nodeValue = node->value;
        if (compareGenericValue(nodeValue, value)) { // if the values are equals
            if(previousNode == NULL) // case where the first node has to be removed
                list->head = node->next;
            else
                previousNode->next = node->next; // attach the next node to the previous one
            
            if (node == list->tail)
                list->tail = previousNode; // case where the last node has to be deleted
            
                free(node); // free the current node memory allocation
            return 0;
        }
        previousNode = node;
        node = node->next;
    }
    return 1;
}



void freeLinkedList(linkedList* list) {

    Node* head = list->head;
    Node* tmp = NULL;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(list);
}


void toPrint(linkedList* list) {
    printf("[");


    Node* current_node = list->head;
    while (current_node != NULL){
        GenericValue value = current_node->value;
        if (value.type == INT_TYPE)
            printf("%i, ", value.data.intValue);
        else if (value.type == FLOAT_TYPE)
            printf("%f, ", value.data.floatValue);
        else if (value.type == CHAR_TYPE)
            printf("%c, ", value.data.charValue);
        else if (value.type == STRING_TYPE)
            printf("%s, ", value.data.stringValue);

        current_node = current_node->next;
    }
    printf("]\n");


}
