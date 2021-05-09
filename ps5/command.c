#include "command.h"
#include <stdlib.h>
#include <string.h>


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    if (name == NULL || description == NULL) return NULL;

    struct command* comm = calloc(1, sizeof(struct command));
    if (comm == NULL) return NULL;

    comm->name = malloc(sizeof(char)*strlen(name)+1);
    strcpy(comm->name, name);

    comm->description = malloc(sizeof(char)*strlen(description)+1);
    strcpy(comm->description, description);

    comm->nmatch = nmatch;
    comm->groups = &pattern;

    return comm;
}

struct command* destroy_command(struct command* command) {
    if (command == NULL) return NULL;

    free(command->description);
    free(command->name);

    for (int i = 0; strlen(*command->groups); ++i)
        free(command->groups[i]);

    free(command);

    return NULL;
}