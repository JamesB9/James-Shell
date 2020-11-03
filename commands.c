//
// Created by JamesBurling on 03/11/2020.
//
#include <stdlib.h>

const char* unixCommandPath = "/bin/";

typedef struct CommandStruct{
    StringList arguments;
}Command;

Command generateCommand(char* commandName, StringList* argumentList, char* currentDir){
    Command command;
    initStringList(&command.arguments);

    // ADD COMMAND PATH
    int length = strlen(unixCommandPath) + strlen(commandName);
    char* commandPath = (char*) malloc(length*sizeof(char));
    strcpy(commandPath,unixCommandPath);
    strcat(commandPath,commandName);
    addString(&command.arguments, commandPath);

    // ADD USER ARGUMENTS
    for(int i = 0; i< argumentList->length; i++){
        addString(&command.arguments, getString(argumentList,i));
    }

    // ADD NULL
    addString(&command.arguments, NULL);

    return command;
}

char* getCommandPath(Command* command){
    return getString(&command->arguments,0);
}

int runCommand(Command* command){
    pid_t pid = fork();

    if (pid == 0)
    {
        execv(getCommandPath(command), command->arguments.pointerArray);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}
