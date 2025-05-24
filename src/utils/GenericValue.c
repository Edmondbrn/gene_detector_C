#include <string.h> // for strcmp
#include"../../include/GenericValue.h"

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
    }

}