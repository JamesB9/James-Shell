/* MAIN.C
 *
 * Author: James Burling
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "commands.h"

#define LOOP_AGAIN 0
#define MAX_CHARS_INPUT 255

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

    int loop = LOOP_AGAIN;
    while(loop == LOOP_AGAIN) {
        Command command;
        initCommand(&command, getInput());
        loop = runCommand(&command);
        freeCommand(&command);
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
    char s[255];
    printf("%s%s%s > %s","\033[01;33m", getcwd(s, 255),"\033[1;36m","\033[97m");

    // Allocates a char array of max characters 255 on the heap and gets the inputted line from stdin
    char* string_input = (char*) malloc(MAX_CHARS_INPUT * sizeof(char));
    fgets(string_input, MAX_CHARS_INPUT, stdin);

    return strtok(string_input, "\n");// Return the line input without \n that fgets adds.
}