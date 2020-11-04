//
// Created by JamesBurling on 03/11/2020.
//

#include <stdlib.h>

const char* unixCommandPath = "/bin/";

typedef struct CommandStruct{
    char** arguments;
    int length;
}Command;

Command generateCommand(char* commandName, StringList* argumentList, char* currentDir);


char* getCommandPath(Command* command);
int runCommand(Command* command);
void initCommand(Command* command);
char* getArg(Command* command, int index);
void addArg(Command* command, char* string);
void outputArguments(Command* command);

Command generateCommand(char* commandName, StringList* argumentList, char* currentDir){
    Command command;
    initCommand(&command);

    // ADD COMMAND PATH
    int length = strlen(unixCommandPath) + strlen(commandName);
    char* commandPath = (char*) malloc(length*sizeof(char));
    strcpy(commandPath,unixCommandPath);
    strcat(commandPath,commandName);
    addArg(&command, commandPath);

    // ADD USER ARGUMENTS
    for(int i = 0; i< argumentList->length; i++){
        addArg(&command, getString(argumentList,i));
    }

    // ADD NULL
    addArg(&command, NULL);

    return command;
}

char* getCommandPath(Command* command){
    return getArg(command,0);
}

int runCommand(Command* command){
    pid_t pid = fork();

    if (pid == 0)
    {
        execv(getCommandPath(command), command->arguments);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}

void initCommand(Command* command){
    command->length = 0;
    command->arguments = (char**) malloc(0);
}

char* getArg(Command* command, int index){
    return *(command->arguments + index);
}

void addArg(Command* command, char* string){
    command->length += 1;
    command->arguments = (char**) realloc(command->arguments, sizeof(char*) * command->length);
    *(command->arguments + (command->length - 1)) = string;
}

void outputArguments(Command* command){
    printf("List Output:\n");
    for(int i = 0; i < command->length; i++){
        printf("%d %s\n", i, getArg(command,i));
    }
}