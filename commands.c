//
// Created by JamesBurling on 03/11/2020.
//

#include <stdlib.h>
#include "commands.h"

#define TRUE 1
#define FALSE 0

const char unixCommandPath[] = "/bin/";

int runCommand(Command* command){
    pid_t pid = fork();

    if (pid == 0)
    {
        if(strcmp(command->commandName, "cd") == 0){
            char s[100];
            chdir(getArg(command,1));
        }else{
            execv(getCommandPath(command), command->arguments);
        }
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    outputCommand(command);
    return strcmp(command->commandName, "exit");
}

void initCommand(Command* command, char* commandString){
    command->length = 0;
    command->commandName = strtok(commandString, " ");
    command->arguments = (char**) malloc(0);

    // ADD COMMAND PATH
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

char* getCommandPath(Command* command){
    return getArg(command,0);
}

char* getArg(Command* command, int index){
    return *(command->arguments + index);
}

void addArg(Command* command, char* string){
    command->arguments = (char**) realloc(command->arguments, sizeof(char*) * ++command->length);
    *(command->arguments + (command->length - 1)) = string;
}

void freeCommand(Command* command){
    free(command->commandName);
    free(command->arguments);
}

void outputCommand(Command* command){
    printf("Command: %s\n", command->commandName);
    printf("Arguments (%d):\n", command->length);
    for(int i = 0; i < command->length; i++){
        printf("%d %s\n", i, getArg(command,i));
    }
    printf("----------------\n");
}