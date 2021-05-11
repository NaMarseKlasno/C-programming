#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void set_commands (struct command* commands[]);
void set_res_commands (struct command* commands[], struct parser *res_pars);
int check_string3 (char *str_one, char *str_two);


struct parser* create_parser () {

    struct command* commands[17];
    // ***** add basic commands to pars
    set_commands(commands);

    struct parser *res_pars = calloc(1, sizeof(struct parser));

    // ***** add basic commands to res_pars
    set_res_commands(commands, res_pars);

    // ***** add history to res_pars && release memory
    res_pars->history = create_container(NULL, COMMAND,  commands[9]);
    if (res_pars->history == NULL){
        destroy_parser(res_pars);
        return NULL;
    }

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
    unsigned long len = strlen(input); char* i_name = NULL; char str[len+1];

    for (unsigned long i = 0; i < len; ++i) str[i] = input[i];
    str[len] = '\0';
    char *str_2 = str;

    for (;parser->commands != NULL;)
    {
        if (parser->commands->type == COMMAND) i_name =  parser->commands->command->name;
        else if (i_name == NULL){
            parser->commands = parser->commands->next;
            continue;
        } else {
            parser->commands = parser->commands->next;
            continue;
        } if (check_string3(str_2, i_name) == 0) {
            return parser->commands->command;
        } else parser->commands = parser->commands->next;
    }

    return NULL;
}


void set_commands (struct command* commands[])
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

void set_res_commands (struct command* commands[], struct parser *res_pars)
{
    res_pars->commands->command = commands[0];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[1];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[2];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[3];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[4];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[5];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[6];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[7];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[8];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[9];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[10];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[11];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[12];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[13];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[14];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[15];
    res_pars->commands = res_pars->commands->next;
    res_pars->commands->command = commands[16];
}

int check_string3 (char *str_one, char *str_two) {
    if (str_two == NULL || str_one == NULL) return 1;
    if (strlen(str_one) != strlen(str_two)) return 1;
    for (int i = 0; i < strlen(str_one); ++i) if (toupper(str_one[i]) != toupper(str_two[i])) return 1;
    return 0;
}
