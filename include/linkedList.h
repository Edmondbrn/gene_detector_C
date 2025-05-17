#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<stdlib.h>

/**
Enum to determine the type of the given argument
*/
typedef enum {
    INT_TYPE,
    FLOAT_TYPE,
    CHAR_TYPE,
    STRING_TYPE
} ValueType;


/**
Structure to create a generic value for the linked list
 */
typedef struct {
    ValueType type;
    union { // allo to only store one element
        int intValue;
        float floatValue;
        char charValue;
        char* stringValue;
    } data;
} GenericValue;


/**Structure to create a new node for a linked list
*/
typedef struct Node {
    GenericValue value;
    struct Node* next;
} Node ;

typedef struct {
    Node* head;
    Node* tail;
} linkedList;

/**
 * Function to create a Node for a linkedList
 * 
 * @param GenericValue value: the generic value to store in the linked list
 */
Node* createNode(GenericValue value);


/**
 * Function to create a linkedList
 * 
 */
linkedList* createList();


/**
 * Function to create a int value for the generic linked list
 * 
 * @param int value, the int to store
 */
GenericValue createIntValue(int value);

/**
 * Function to create a int value for the generic linked list
 * 
 * @param float value, the float to store
 */
GenericValue createFloatValue(float value);

/**
 * Function to create a int value for the generic linked list
 * 
 * @param char value, the char to store
 */
GenericValue createCharValue(char value);

/**
 * Function to create a int value for the generic linked list
 * 
 * @param char* value, the string to store
 */
GenericValue createStringValue(char* value);

/**
 * Function to add a node to the linked list
 * 
 * @param list linked list pointer
 * @param value value, the value to store the new node
 * 
 * @return int 0 if it is OK, -1 otherwise
 */
int appendNode(linkedList* list, GenericValue value);


void freeList(linkedList* list);


#endif