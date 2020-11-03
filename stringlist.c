//
// Created by JamesBurling on 03/11/2020.
//
#include <stdlib.h>

typedef struct StringListStruct{
    int length;
    int** pointerArray;
}StringList;


void addString(StringList* list, char* string){
    list->length += 1;
    list->pointerArray = realloc(list->pointerArray, sizeof(int *) * list->length);

    list->pointerArray[list->length-1] = &string;
}

