/* COMMANDS.H
 *
 * Author: James
 * Date Created : 03/11/2020
 * Last Modified: 06/11/2020
 *
 */
#ifndef OS1_COURSEWORK_COMMANDS_H
#define OS1_COURSEWORK_COMMANDS_H

typedef struct CommandStruct{
    char** arguments;
    char* commandName;
    int length;
}Command;

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
void initCommand(Command* command, char* commandString);

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
char* getCommandPath(Command* command);

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
int runCommand(Command* command);

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
char* getArg(Command* command, int index);

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
void addArg(Command* command, char* arg);

/*
 * Function: freeCommand
 * ------------------------
 * De-allocates the dynamic memory stored for the Command struct provided.
 *
 * @param command - pointer to a command struct
 *
 * @return void
 */
void freeCommand(Command* command);

/*
 * Function: outputCommand
 * ------------------------
 * Prints the provided Command structs' command name and all its arguments to stdout.
 *
 * @param command - pointer to a command struct
 *
 * @return void
 */
void outputCommand(Command* command);

#endif //OS1_COURSEWORK_COMMANDS_H
