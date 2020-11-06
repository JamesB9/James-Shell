/* MAIN.C
 *
 * Author: James Burling
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include "commands.c"

#define TRUE 1
#define FALSE 0

char* getInput();
void writeHeader();

/*
 * Function: main
 * ------------------------
 * Contains the main loop. This asks the user for input, interprets the string to create a
 * Command. Then the command is run.
 *
 * @return int of how the program exited.
 */
int main(){
    writeHeader();

    int loop = TRUE;
    while(loop != 0) {
        Command command;
        initCommand(&command, getInput());

        int test = runCommand(&command);
        printf("LOOP: %d\n", test);
        loop = test;
        //loop = runCommand(&command);
        freeCommand(&command);
        printf("loop: %d\n", loop);
    }
    return EXIT_SUCCESS;
}

/*
 * Function: writeHeader
 * ------------------------
 * Prints the header text (e.g. title, description and author) to the stdout
 *
 * @return void
 */
void writeHeader(){
    char asciiText[] = "\033[01;33m-------------------------------------------------------------------------------\n\033[1;36m"
                       "   __                              __ _          _ _ \n"
                       "   \\ \\  __ _ _ __ ___   ___  ___  / _\\ |__   ___| | |\n"
                       "    \\ \\/ _` | '_ ` _ \\ / _ \\/ __| \\ \\| '_ \\ / _ \\ | |\n"
                       " /\\_/ / (_| | | | | | |  __/\\__ \\ _\\ \\ | | |  __/ | |\n"
                       " \\___/ \\__,_|_| |_| |_|\\___||___/ \\__/_| |_|\\___|_|_|\n\n"
                       "\033[01;33mDescription:\033[1;36m A simple Linux shell for OS1 Coursework\n"
                       "\033[01;33mAuthor:      \033[1;36mJames Burling\n"
                       "\033[01;33m-------------------------------------------------------------------------------\n\n";
    printf("\033[97m%s", asciiText);
}

/*
 * Function: getInput
 * ------------------------
 * Prints the current directory to stdout and prompts the user for input.
 * Reads a string containing all user input for a single line from stdin.
 *
 * @return a pointer to a char array containing user input
 */
char* getInput(){
    char* string_input = (char*) malloc(256 * sizeof(char));
    char s[100];

    printf("%s%s%s > %s","\033[01;33m", getcwd(s, 100),"\033[1;36m","\033[97m");

    fgets(string_input, 256, stdin);
    string_input = strtok(string_input, "\n");
    return string_input;
}