//
// Created by JamesBurling on 03/11/2020.
//

#include <stdlib.h>
#define TRUE 1
#define FALSE 0

const char* unixCommandPath = "/bin/";

typedef struct CommandStruct{
    char** arguments;
    char* commandName;
    int length;
}Command;

void initCommand(Command* command, char* commandName);
char* getCommandPath(Command* command);
int runCommand(Command* command);
char* getArg(Command* command, int index);
void addArg(Command* command, char* string);
void outputArguments(Command* command);

char* getCommandPath(Command* command){
    return getArg(command,0);
}

void changeDirectory(char* directory){

}

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

    return strcmp(command->commandName, "exit");
}

void initCommand(Command* command, char* commandName){
    command->length = 0;
    command->commandName = commandName;
    command->arguments = (char**) malloc(0);

    // ADD COMMAND PATH
    int length = strlen(unixCommandPath) + strlen(commandName);
    char* commandPath = (char*) malloc(length*sizeof(char));
    strcpy(commandPath,unixCommandPath);
    strcat(commandPath,commandName);
    addArg(command, commandPath);
}

char* getArg(Command* command, int index){
    return *(command->arguments + index);
}

void addArg(Command* command, char* string){
    command->length += 1;
    command->arguments = (char**) realloc(command->arguments, sizeof(char*) * command->length);
    *(command->arguments + (command->length - 1)) = string;
}

void outputCommand(Command* command){
    printf("Command: %s\n", command->commandName);
    printf("Arguments:\n");
    for(int i = 0; i < command->length; i++){
        printf("%d %s\n", i, getArg(command,i));
    }
    printf("----------------\n");
}