#include <string.h> // for strcmp
#include"../../include/GenericValue.h"
#include <stdio.h>
int compareGenericValue(GenericValue a, GenericValue b) {

    if (a.type != b.type)
        return 0;

    switch(a.type){
        case(INT_TYPE):
            return a.data.intValue == b.data.intValue;
        case(FLOAT_TYPE):
            return a.data.floatValue == b.data.floatValue;
        case(CHAR_TYPE):
            return a.data.charValue == b.data.charValue;
        case(STRING_TYPE):
            return strcmp(a.data.stringValue, b.data.stringValue) == 0;
        default:
            return 1;
    }
}

void toPrintGenericValue(GenericValue value) {
    switch(value.type){
        case(INT_TYPE):
            printf("%i\n", value.data.intValue);
            break;
        case(FLOAT_TYPE):
            printf("%f\n", value.data.floatValue);
            break;
        case(CHAR_TYPE):
            printf("%c\n", value.data.charValue);
            break;
        case(STRING_TYPE):
            printf("%s\n", value.data.stringValue);
            break;
        default:
            printf("Error, unkown type.\n");
    }
}