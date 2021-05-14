#include "command.h"
#include <stdlib.h>
#include <string.h>


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    // https://pubs.opengroup.org/onlinepubs/009695399/functions/regcomp.html

    if (name == NULL || description == NULL || name[0] == '\0' || description[0] == '\0') return NULL;

    struct command* comm = calloc(1, sizeof(struct command));
    if (comm == NULL) return NULL;

    comm->name = calloc(strlen(name)+1, sizeof(char));
    strcpy(comm->name, name);

    comm->description = calloc(strlen(description)+1, sizeof(char));
    strcpy(comm->description, description);


    if (pattern != NULL) {
        if (regcomp(&comm->preg, pattern, REG_ICASE | REG_EXTENDED) != 0) {
            free(comm);
            return NULL;
        }
    }

    comm->nmatch = nmatch;

    return comm;
}

struct command* destroy_command(struct command* command) {
    if (command == NULL) return NULL;

    free(command->name);
    free(command->description);
    free(command);

    return NULL;
}