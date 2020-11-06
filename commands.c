//
// Created by JamesBurling on 03/11/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "commands.h"

#define EXIT_LOOP 1
#define LOOP_AGAIN 0

/*
 * Function: runCommand
 * ------------------------
 * Checks for certain special commands otherwise it executes the command in the Command struct via a child process.
 * Decides whether to exit or maintain the main program loop
 *
 * @param command       - pointer to a command struct
 *
 * @return an int to decide whether the current process should break the main loop and exit, or keep looping.
 */
int runCommand(Command* command) {

    if (strcmp(command->commandName, "exit") == 0) {
        return EXIT_LOOP;
    } else if (strcmp(command->commandName, "cd") == 0){
        chdir(getArg(command, 1));
        return LOOP_AGAIN;
    } else {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork error ");
            return EXIT_LOOP;
        } else if (pid == 0) {
            if (execv(getCommandPath(command), command->arguments)) {
                perror("execv error ");
                return EXIT_LOOP;
            }
        } else {
            int status;
            waitpid(pid, &status, 0);
            return LOOP_AGAIN;
        }
    }
}

/*
 * Function: initCommand
 * ------------------------
 * Initialises the Command struct variables; allocating memory on the heap and setting default values.
 *
 * @param command       - pointer to a command struct
 * @param commandString - char array containing a command name followed by arguments. e.g. "ls -l -a"
 *
 * @return void
 */
void initCommand(Command* command, char* commandString){
    command->length = 0;
    command->commandName = strtok(commandString, " ");
    command->arguments = (char**) malloc(0);

    // ADD COMMAND PATH
    const char unixCommandPath[] = "/bin/";
    int length = strlen(unixCommandPath) + strlen(command->commandName);
    char* commandPath = (char*) malloc(length*sizeof(char));
    strcpy(commandPath,unixCommandPath);
    strcat(commandPath,command->commandName);
    addArg(command, commandPath);

    // ADD ALL ARGUMENTS TO LIST, NULL AT END
    char *arg;
    while(arg != NULL){
        arg = strtok(NULL, " ");
        addArg(command, arg);
    }while(arg != NULL);
    free(arg);
}

/*
 * Function: getCommandPath
 * ------------------------
 * An accessor function to retrieve a pointer to a char array containing the file path for
 * the Command struct's command executable.
 *
 * @param command - pointer to a command struct
 *
 * @return pointer to a char array containing the file path to command executable. e.g. "/bin/ls"
 */
char* getCommandPath(Command* command){
    return getArg(command,0);
}

/*
 * Function: getArg
 * ------------------------
 * An accessor method for accessing the arguments stored in a Command struct
 *
 * @param command - pointer to a command struct
 * @param index   - integer to decide which argument in the arguments array to return.
 *
 * @return a pointer to a char array containing the argument stored in the arguments array at the index provided.
 */
char* getArg(Command* command, int index){
    return *(command->arguments + index);
}

/*
 * Function: addArg
 * ------------------------
 * Stores a copy of the provided argument in the provided Command structs' array of arguments
 *
 * @param command - pointer to a command struct
 * @param arg  - a pointer to a char array containing a command line input from the user. e.g. "-la"
 *
 * @return void
 */
void addArg(Command* command, char* arg){
    command->arguments = (char**) realloc(command->arguments, sizeof(char*) * ++command->length);
    *(command->arguments + (command->length - 1)) = arg;
}

/*
 * Function: freeCommand
 * ------------------------
 * De-allocates the dynamic memory stored for the Command struct provided.
 *
 * @param command - pointer to a command struct
 *
 * @return void
 */
void freeCommand(Command* command){
    free(command->commandName);
    free(command->arguments);
}

/*
 * Function: outputCommand
 * ------------------------
 * Prints the provided Command structs' command name and all its arguments to stdout.
 *
 * @param command - pointer to a command struct
 *
 * @return void
 */
void outputCommand(Command* command){
    printf("Command: %s\n", command->commandName);
    printf("Arguments (%d):\n", command->length);
    for(int i = 0; i < command->length; i++){
        printf("%d %s\n", i, getArg(command,i));
    }
    printf("----------------\n");
}