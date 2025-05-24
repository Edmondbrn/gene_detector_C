#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include<stdlib.h>
#include"GenericValue.h"

/**Structure to create a new node for a linked list
*/
typedef struct Node {
    GenericValue value;
    struct Node* next;
} Node ;

typedef struct KeyValueNode {
    GenericValue value;
    char* key;
    struct KeyValueNode* next;
} KeyValueNode ;

typedef struct {
    Node* head;
    Node* tail;
} linkedList;

typedef struct {
    KeyValueNode* head;
    KeyValueNode* tail;
} keyValueLinkedList;
/**
 * Function to create a Node for a linkedList
 * 
 * @param GenericValue value: the generic value to store in the linked list
 */
Node* createNode(GenericValue value);

/**
 * Function to create a key-value Node for a linkedList
 * 
 * @param GenericValue value: the generic value to store in the linked list
 * @param key the key related to the value
 */
KeyValueNode* createKeyValueNode(GenericValue value, char* key);


void toPrintLinkedList(linkedList* list);
void toPrintKeyValueLinkedList(keyValueLinkedList* list);


/**
 * Function to create a linkedList
 * 
 */
linkedList* createLinkedList();

keyValueLinkedList* createKeyValueLinkedList();


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

/**
 * Function to add a node to the linked list
 * 
 * @param list linked list pointer
 * @param value value, the value to store the new node
 * @param key key, the key used in hashMap process
 * 
 * @return int 0 if it is OK, -1 otherwise
 */
int appendKeyValueNode(keyValueLinkedList* list, GenericValue value, char* key);

/**
 * Function to remove the first node containing the given value
 * 
 * @param list linked list pointer
 * @param value value, the value to store the new node
 * 
 * @return int 0 if it is OK, 1 if no node contains the value
 */
int removeNode(linkedList* list, GenericValue value);

/**
 * Function to remove a key-value node to the linked list (based on the key)
 * 
 * @param list linked list pointer
 * @param key key, the key used in hashMap process
 * 
 * @return int 0 if it is OK, -1 otherwise
 */
int removeKeyValueNode(keyValueLinkedList* list, char* key);



void freeLinkedList(linkedList* list);

void freeKeyValueLinkedList(keyValueLinkedList* list);


#endif