#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void create_commands (struct command * commands[]);
void add_commands (struct command * commands[], struct parser *res_pars);
int check_string3 (char *str_one, char *str_two);


struct parser* create_parser () {

    struct command* commands[17];

    // ***** add basic commands to pars
    create_commands(commands);

    struct parser *res_pars = calloc(1, sizeof(struct parser));
    if (res_pars == NULL) return NULL;

    // ***** add basic commands to res_pars
    add_commands(commands, res_pars);
    // free commands

    // ***** add history to res_pars && release memory
    res_pars->history = create_container(NULL, COMMAND, commands[1]);

    return res_pars;
}

struct parser* destroy_parser (struct parser* parser) {
    if (parser == NULL) return NULL;

    destroy_containers(parser->commands);
    destroy_containers(parser->history);
    free(parser);

    return NULL;
}

struct command* parse_input (struct parser* parser, char* input) {
    if (parser == NULL || input == NULL) return NULL;
    unsigned long len = strlen(input), new_len = 0; char* received_name = NULL;

    if (input[0] == ' ') {
        for (unsigned long j = 0; j < len; ++j) {
            if (input[j] == ' ') {
                ++new_len;
                if (input[j+1] != ' ') break;
            }
        }
    }
    if (input[len-1] == ' ') {
        for (unsigned long j = len-1; j > 0; --j) {
            if (input[j] == ' ') {
                ++new_len;
                if (input[j-1] != ' ') break;
            }
        }
    }
    new_len = len - new_len;
    char cut_str[new_len+1];

    if ((input[0] == ' ' && input[len-1] == ' ') || (input[0] == ' ' && input[len-1] != ' ') )
    {
        for (unsigned long j = 0; j < len; ++j) {
            if (input[j] == ' ') {
                if (input[j+1] != ' ') {
                    for (unsigned long k = 0, m = j+1; k < new_len; ++k, ++m) cut_str[k] = input[m];
                    break;
                }
            }
        } cut_str[new_len] = '\0';
    }
    if (input[0] != ' ' && input[len-1] == ' ')
    {
        for (int j = 0; j < new_len; ++j) {
            cut_str[j] = input[j];
        } cut_str[new_len] = '\0';
    }

    char str[new_len+1];
    for (unsigned long i = 0; i < len; ++i) {
        if (new_len == len)
            str[i] = input[i];
        else
            str[i] = cut_str[i];
    }
    str[new_len] = '\0';
    char *str_2 = str;

    //printf("str_2: [%s] ............................................................................\n", str_2);

    for (;parser->commands != NULL;)
    {
        if (parser->commands->type == COMMAND) received_name =  parser->commands->command->name;
        else if (received_name == NULL){
            parser->commands = parser->commands->next;
            continue;
        } else {
            parser->commands = parser->commands->next;
            continue;
        } if (check_string3(str_2, received_name) == 0) {
            return parser->commands->command;
        } else parser->commands = parser->commands->next;
    }

    return NULL;
}


void create_commands (struct command* commands[])
{
    commands[0] = create_command("KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "(QUIT)|(EXIT)", 2);
    commands[1] = create_command("SEVER", "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(S)", 1);
    commands[2] = create_command("JUH", "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(J)", 1);
    commands[3] = create_command("VYCHOD", "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(V)", 1);
    commands[4] = create_command("ZAPAD", "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(Z)", 1);
    commands[5] = create_command("ROZHLIADNI SA", "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", "", 0);
    commands[6] = create_command("PRIKAZY", "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", "(HELP)|(POMOC)", 2);
    commands[7] = create_command("VERZIA", "Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", "", 0);
    commands[8] = create_command("RESTART", "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", "", 0);
    commands[9] = create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "(ABOUT)", 1);
    commands[10] = create_command("VEZMI", "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", "", 0);
    commands[11] = create_command("POLOZ", "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", "", 0);
    commands[12] = create_command("INVENTAR", "Zobrazí obsah hráčovho batohu.", "(I)", 1);
    commands[13] = create_command("POUZI", "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", "", 0);
    commands[14] = create_command("PRESKUMAJ", "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", "", 0);
    commands[15] = create_command("NAHRAJ", "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "(LOAD)", 1);
    commands[16] = create_command("ULOZ", "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "(SAVE)", 1);
}

void add_commands (struct command* commands[], struct parser *res_pars)
{
    res_pars->commands = create_container(NULL, COMMAND, commands[0]);

    create_container(res_pars->commands, COMMAND, commands[1]);
    create_container(res_pars->commands, COMMAND, commands[2]);
    create_container(res_pars->commands, COMMAND, commands[3]);
    create_container(res_pars->commands, COMMAND, commands[4]);
    create_container(res_pars->commands, COMMAND, commands[5]);
    create_container(res_pars->commands, COMMAND, commands[6]);
    create_container(res_pars->commands, COMMAND, commands[7]);
    create_container(res_pars->commands, COMMAND, commands[8]);
    create_container(res_pars->commands, COMMAND, commands[9]);
    create_container(res_pars->commands, COMMAND, commands[10]);
    create_container(res_pars->commands, COMMAND, commands[11]);
    create_container(res_pars->commands, COMMAND, commands[12]);
    create_container(res_pars->commands, COMMAND, commands[13]);
    create_container(res_pars->commands, COMMAND, commands[14]);
    create_container(res_pars->commands, COMMAND, commands[15]);
    create_container(res_pars->commands, COMMAND, commands[16]);
}

int check_string3 (char *str_one, char *str_two) {
    if (str_two == NULL || str_one == NULL) return 1;
    if (strlen(str_one) != strlen(str_two)) return 1;
    for (int i = 0; i < strlen(str_one); ++i) if (toupper(str_one[i]) != toupper(str_two[i])) return 1;
    return 0;
}
