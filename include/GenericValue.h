#ifndef GENERIC_VALUE_H
#define GENERIC_VALUE_H

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
    union { // allow to only store one element
        int intValue;
        float floatValue;
        char charValue;
        char* stringValue;
    } data;
} GenericValue;


/**
 * Function to compare generic values
 * 
 * @param a the first generic value
 * @param b the second generic value
 * 
 * @return int 1 if they are equals, 0 otherwise
 */
int compareGenericValue(GenericValue a, GenericValue b);

void toPrintGenericValue(GenericValue value);


#endif