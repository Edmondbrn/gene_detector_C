#include<stdio.h>
#include<stdlib.h>

int getArraySize(int* array) {
    return sizeof(array) / sizeof(array[0]);
}


int main(void) {

    int cpt = 0;
    int* intArr = malloc(sizeof(int) * 10);
    while (cpt < 10) {
        intArr[cpt] = cpt;
        cpt ++;
    }
    printf("Test array 0 %i\n", intArr[0]);
    printf("Size of array %i\n", getArraySize(intArr));
    free(intArr);


    return 0;
}