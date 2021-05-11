#include "command.h"
#include <stdlib.h>
#include <string.h>


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    if (name == NULL || description == NULL || strlen(name) == 0 || strlen(description) == 0) return NULL;

    struct command* comm = calloc(1, sizeof(struct command));
    if (comm == NULL) return NULL;

    comm->name = calloc(strlen(name)+1, sizeof(char));
    for (int i = 0; i < strlen(name)+1; ++i) {
        comm->name[i] = name[i];
    }
    comm->description = calloc(strlen(description)+1, sizeof(char));
    for (int i = 0; i < strlen(description)+1; ++i) {
        comm->description[i] = description[i];
    }

    comm->nmatch = nmatch;
    comm->groups = &pattern;



    return comm;
}

struct command* destroy_command(struct command* command) {
    if (command == NULL) return NULL;

    free(command->name);
    free(command->description);
    free(command);

    return NULL;
}