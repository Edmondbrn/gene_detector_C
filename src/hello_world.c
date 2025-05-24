#include<stdio.h>
#include<stdlib.h>
#include"arrayUtils.h"
#include"linkedList.h"
#include"HashMap.h"



int main(void) {
    printf("\n\n\n\n");
    printf("Test de la hash map made in Edmondo.\n");
    HashMap* map = createHashMap(10);

    // Ajouter des clés dynamiques dans la HashMap
    for (int i = 0; i < 20; i++) {
        char key[50];  // Buffer pour stocker la clé
        snprintf(key, sizeof(key), "key%d", i);  // Générer une clé sous la forme "key0", "key1", etc.
        putHashMap(map, key, createFloatValue((float) i));  // Ajouter la clé et la valeur associée
    }
    // Tester la récupération des valeurs
    for (int i = 0; i < 20; i++) {
        char key[50];
        snprintf(key, sizeof(key), "key%d", i);  // Générer la même clé
        GenericValue* value;
        int status = getHashMapValue(map, key, &value);
        if (status == 0) {
            printf("Key: %s, Value: ", key);
            toPrintGenericValue(*value);  // Afficher la valeur associée
        } else {
            printf("Key: %s not found\n", key);
        }
    }

    toPrintHashMap(map);
    freeHashMap(map);
    printf("\n\n\n\n");

    return 0;
}

