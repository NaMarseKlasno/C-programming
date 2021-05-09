#ifndef ADDITIONAL_H
#define ADDITIONAL_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "room.h"
#include "game.h"
#include "container.h"

void destroy_next_conts (struct container* next);


int check_symbol (char c);


int check_string (char *str_one, char *str_two);

#endif
