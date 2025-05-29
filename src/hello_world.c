#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"arrayUtils.h"
#include"linkedList.h"
#include"HashMap.h"



int main(void) {
    printf("\n\n\n\n");
    printf("Test file reader\n");

    FILE *file;

    file = fopen("ressources/test.fasta", "r");
    if (file == NULL) {
        printf("The file is not found.\n");
        fclose(file);
        return -1;
    }
    char bufferReader[150];

    HashMap* map = createHashMap(10);
    while(fgets(bufferReader, 150, file)) {
        // printf("%s", bufferReader);
        if (bufferReader[0] == '>') // skip fasta first line
            continue;

        int size = strlen(bufferReader);
        for(int i = 0; i < size; i++) {
            if (bufferReader[i] == '\n')
                continue;

            char strNucl[2];
            strNucl[0] = bufferReader[i];
            strNucl[1] = '\0';
            if (containsKey(map, strNucl)) {
                GenericValue* nbNucl;
                getHashMapValue(map, strNucl, &nbNucl);
                GenericValue newValue = createIntValue(nbNucl->data.intValue + 1);
                putHashMap(map, strNucl, newValue);
            } else {
                GenericValue nbNucl = createIntValue(0);
                putHashMap(map, strNucl, nbNucl);
            }
        }
    }

    toPrintHashMap(map);
    freeHashMap(map);


    fclose(file);
    printf("\n\n\n\n");

    return 0;
}

