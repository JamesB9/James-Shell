//
// Created by JamesBurling on 03/11/2020.
//
#include <stdlib.h>

typedef struct StringListStruct{
    int length;
    char** pointerArray;
}StringList;

void initStringList(StringList* list){
    list->length = 0;
    list->pointerArray = (char**) malloc(0);
}

char* getString(StringList* list, int index){
    return *(list->pointerArray+index);
}

void addString(StringList* list, char* string){
    list->length += 1;
    list->pointerArray = (char**) realloc(list->pointerArray, sizeof(char*) * list->length);
    *(list->pointerArray + (list->length - 1)) = string;
}

void outputList(StringList* list){
    printf("List Output:\n");
    for(int i = 0; i < list->length; i++){
        printf("%d %s\n", i, getString(list,i));
    }

}

void freeStringList(StringList* list){
    for(int i = 0; i < list->length; i++){
        free(&list->pointerArray[i]);
    }
    //printf("Freeing List\n");
    //free(*list->pointerArray);
    //printf("List Freed\n");
}
