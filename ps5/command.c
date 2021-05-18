#include "command.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct command* create_command(char* name, char* description, char* pattern, size_t nmatch) {
    /** https://pubs.opengroup.org/onlinepubs/009695399/functions/regcomp.html */

    if (name == NULL || description == NULL || name[0] == '\0' || description[0] == '\0') return NULL;

    struct command* comm = calloc(1, sizeof(struct command));
    if (comm == NULL) return NULL;

    comm->name = name;
    comm->description = description;

    if (pattern != NULL)
    {
        /// TODO: fix bug with memory leak
        if (regcomp(&comm->preg, pattern, 0) != 0) {
            destroy_command(comm);
            return NULL;
        }
    } comm->nmatch = nmatch;

    return comm;
}

struct command* destroy_command(struct command* command) {
    if (command == NULL) return NULL;

    regfree(&command->preg);
    free(command->name);
    free(command->description);
    free(command);

    return NULL;
}