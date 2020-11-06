//
// Created by JamesBurling on 06/11/2020.
//

#ifndef OS1_COURSEWORK_COMMANDS_H
#define OS1_COURSEWORK_COMMANDS_H

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

void freeCommand(Command* command);

void outputCommand(Command* command);

#endif //OS1_COURSEWORK_COMMANDS_H
