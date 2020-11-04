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

void write_header(){
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

char* get_input(){
    char* string_input = (char*) malloc(256 * sizeof(char));
    char s[100];

    printf("%s%s%s > %s","\033[01;33m", getcwd(s, 100),"\033[1;36m","\033[97m");

    fgets(string_input, 256, stdin);
    string_input = strtok(string_input, "\n");
    return string_input;
}


int main(){
    write_header();

    int loop = TRUE;
    while(loop) {
        // Get user input
        char *userInput = get_input();
        // Extract command, arguments from input
        Command command;
        char *commandName = strtok(userInput, " ");

        initCommand(&command, commandName);

        char *arg = strtok(NULL, " ");
        while (arg != NULL) { // While words in user input
            addArg(&command, arg);
            arg = strtok(NULL, " ");
        }

        addArg(&command, NULL);
        loop = runCommand(&command);
    }
    //freeStringList(&args);
    return EXIT_SUCCESS;
}