//
// Created by JamesBurling on 03/11/2020.
//
#include <stdlib.h>

typedef struct StringListStruct{
    int length;
    int** pointerArray;
}StringList;

void setupList(StringList* list){
    list->pointerArray = (int**) malloc(sizeof(int*));
    list->length = 1;
}


void addString(StringList* list, char* string){
    list->length += 1;
    list->pointerArray = (int**) realloc(&list, sizeof(int *) * list->length);

    list->pointerArray[list->length-1] = &string;
}

char* getString(StringList* list, int index){
    return list->pointerArray[index];
}
