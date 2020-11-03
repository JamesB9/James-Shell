#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
//#include <pthread.h>

#define TRUE 1
#define FALSE 0

char* get_input(){
    char* string_input = (char*) malloc(50 * sizeof(char));

    printf("> ");
    fgets(string_input, 50, stdin);


    return string_input;
}

int main() {
    // Get user input
    char* userInput = get_input();

    // Extract command, arguments from input
    int **p, rowCount = 2;
    p = (int**) malloc(sizeof(int*) * rowCount); // Initialise array of pointers

    //for(int i = 0; i < row; i++){
    //    *(p+i) = (char*) malloc(sizeof(char) * col);
    //}

    char* temp = strtok(userInput, " ");
    int length;
    while(temp != NULL){ // While words in user input

        /* COPY WORD INTO ROW */
        length = strlen(temp);
        *(p + (rowCount-1)) = (char*) malloc(sizeof(char) * length);
        strcpy(p+(rowCount-1), temp);

        printf("%s\n", p+(rowCount-1));
        /* CREATE NEW ROW */
        p = (int**) realloc(p, sizeof(int*) * ++rowCount);
        printf("%s\n", p+(rowCount-2));
        temp = strtok(NULL, " ");
    }
    printf("ALL STORED\n");
    /* Print out array of word */
    for(int i = 0; i < rowCount; i++){
        printf("%s\n", (p+i));
    }

    /*
    char *command, *arg, *args;
    int argumentSize = 20, argumentCount = 1, argumentPointer = 0;

    args = (char*) malloc(argumentCount * argumentSize * sizeof(char));
    command = strtok(userInput, " "); // First token

    while((arg = strtok(NULL, " ")) != NULL){
        printf( "Arg: %s\n", arg);

        strcpy(args, arg);
        printf("Args: %s\n", args);
        args = (char*) realloc(args,++argumentCount * argumentSize * sizeof(char));
    }

    printf("Arguments: %s\n", args);
     */
    return EXIT_SUCCESS;
}
