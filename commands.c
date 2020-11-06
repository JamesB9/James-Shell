/* COMMANDS.C
 *
 * Author: James Burling
 * Date: 03/11/2020
 * Last Modified: 06/11/2020
 *
 */

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
    if (strcmp(command->commandName, "exit") == 0) { // IF commandName == exit --> EXIT_LOOP
        return EXIT_LOOP;
    } else if (strcmp(command->commandName, "cd") == 0){ // IF commandName == exit --> EXIT_LOOP
        chdir(getArg(command, 1)); // System Call to change directory
        return LOOP_AGAIN;
    } else {
        pid_t pid = fork(); // Creates child process with pid=0

        if (pid < 0) {
            perror("fork error ");
            return EXIT_LOOP;
        } else if (pid == 0) {
            if (execv(getCommandPath(command), command->arguments)) { // Executes the command
                printf("The command '%s' doesn't exist\n", command->commandName, stderr);
                perror("execv error ");
                return EXIT_LOOP;
            }
        } else {
            int status;
            waitpid(pid, &status, 0); // Parent process waits here until child process has finished
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
    // Initialises all command's variables.
    command->length = 0;
    command->commandName = strtok(commandString, " "); // extract first word in commandString
    command->arguments = (char**) malloc(0);

    // Creates the file path to the commands executable.
    const char unixCommandPath[] = "/bin/";
    int length = strlen(unixCommandPath) + strlen(command->commandName);
    char* commandPath = (char*) malloc(length*sizeof(char));

    strcpy(commandPath,unixCommandPath);
    strcat(commandPath,command->commandName);
    addArg(command, commandPath); // Sets first argument in array to be the commandPath

    // Extracts and appends all the arguments from commandString
    char *arg;
    while(arg != NULL){
        arg = strtok(NULL, " ");
        addArg(command, arg);
    }while(arg != NULL);
    free(arg); // Free the memory on the heap allocated for holding temporary argument strings.
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
 * Implemented via pointer arithmetic.
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
 * The realloc function is used followed by pointer arithmetic to add the new argument to the end of the array
 *
 * @param command - pointer to a command struct
 * @param arg  - a pointer to a char array containing a command line input from the user. e.g. "-la"
 *
 * @return void
 */
void addArg(Command* command, char* arg){
    // Re-allocates the arguments array so that its length is incremented by one.
    command->arguments = (char**) realloc(command->arguments, sizeof(char*) * ++command->length);
    // sets the value of the last element in the arguments array equal to arg.
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