#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


int check_string3 (char *str_one, char *str_two);

/**                         <RACCOON>
 *
 *                                    .                : :
 *                  _..----..__   __..:'.-'''-.-''    .  :
 *                .'      ,    '''    '    :   .'    /  '
 *               ',                  ( -=o):(o=-)   .  :
 *              :     ,               ''.  ;  .'  __:  :
 *              :          :      ,      '.0.''.-'.))  :  __..--
 *              :           :                ._.-'__| ':''.
 *               .           :   ,   ..  :.-' __.' /   ;    .
 *              .'       ,   :    _.'  '. '.''    /   /  '
 *            .:. .'.        :--:'_..--'''.))  .  ' -'    __.--'
 *          .''::'   '-.  .-''.  '.   .             __.--'
 *          :...:     __\  '.  '..))     '    __.--'
 *          ::'':.--''   '.)))          __.--'
 */

struct parser* create_parser () {
    /** this video helped me learn regular expressions
      * https://www.youtube.com/watch?v=Sa92COTUkfw */

    struct parser *pars = calloc(1, sizeof(struct parser));
    if (pars == NULL) return NULL;

    // ***** add basic commands to pars
    pars->commands = create_container(NULL, COMMAND, create_command("KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "^\\s{0,}(KONIEC|QUIT|EXIT)\\s{0,}$", 3));

    create_container(pars->commands, COMMAND, create_command("SEVER", "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(SEVER|S)\\s{0,}$", 2));
    create_container(pars->commands, COMMAND, create_command("JUH", "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(JUH|J)\\s{0,}$", 2));
    create_container(pars->commands, COMMAND, create_command("VYCHOD", "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(VYCHOD|V)\\s{0,}$", 2));
    create_container(pars->commands, COMMAND, create_command("ZAPAD", "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "^\\s{0,}(ZAPAD|Z)\\s{0,}$", 2));
    create_container(pars->commands, COMMAND, create_command("ROZHLIADNI SA", "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", "^\\s{0,}ROZHLIADNI\\sSA\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("PRIKAZY", "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", "^\\s{0,}(PRIKAZY|HELP|POMOC)\\s{0,}$", 3));
    create_container(pars->commands, COMMAND, create_command("VERZIA", "Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", "^\\s{0,}VERZIA\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("RESTART", "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", "^\\s{0,}RESTART\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 2) );
    create_container(pars->commands, COMMAND, create_command("VEZMI", "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", "^\\s{0,}VEZMI\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("POLOZ", "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", "^\\s{0,}POLOZ\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("INVENTAR", "Zobrazí obsah hráčovho batohu.", "^\\s{0,}(INVENTAR|I)\\s{0,}$", 2));
    create_container(pars->commands, COMMAND, create_command("POUZI", "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", "^\\s{0,}POUZI\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("PRESKUMAJ", "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", "^\\s{0,}PRESKUMAJ\\s{0,}$", 1));
    create_container(pars->commands, COMMAND, create_command("NAHRAJ", "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "^\\s{0,}(NAHRAJ|LOAD)\\s{0,}$", 2));
    create_container(pars->commands, COMMAND, create_command("ULOZ", "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "^\\s{0,}(ULOZ|SAVE)\\s{0,}$", 2));

    // ***** add history to res_pars && release memory
    pars->history = create_container(NULL, COMMAND,  create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "^\\s{0,}(O HRE|ABOUT)\\s{0,}$", 2));
    if (pars->history == NULL) {
        destroy_parser(pars);
        return NULL;
    }

    return pars;
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

int check_string3 (char *str_one, char *str_two) {
    if (str_two == NULL || str_one == NULL) return 1;
    if (strlen(str_one) != strlen(str_two)) return 1;
    for (int i = 0; i < strlen(str_one); ++i) if (toupper(str_one[i]) != toupper(str_two[i])) return 1;
    return 0;
}
