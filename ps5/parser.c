#include "parser.h"

#include <stdlib.h>

void set_commands (struct parser *pars);
void set_res_commands (struct parser *pars, struct parser *res_pars);

struct parser* create_parser() {

    // ***** allocate memory
    struct parser *pars = calloc(1, sizeof(struct parser));
    if (pars == NULL) return NULL;
    pars->commands = calloc(17, sizeof(struct container));
    if (pars->commands == NULL) {
        destroy_parser(pars);
        return NULL;
    }

    // ***** add basic commands to pars
    set_commands(pars);

    struct parser *res_pars = calloc(1, sizeof(struct parser));


    // ***** add basic commands to res_pars
    set_res_commands(pars, res_pars);

    // ***** add history to res_pars && release memory
    res_pars->history = create_container(NULL, COMMAND,  pars->commands[9].command);
    if (res_pars->history == NULL){
        destroy_parser(pars);
        destroy_parser(res_pars);
        return NULL;
    } destroy_parser(pars);

    return res_pars;
}

struct parser* destroy_parser(struct parser* parser) {
    if (parser == NULL) return NULL;
    destroy_containers(parser->commands);
    destroy_containers(parser->history);
    free(parser);
    return NULL;}

void set_commands (struct parser *pars)
{
    pars->commands[0].command = create_command("KONIEC", "Príkaz ukončí rozohratú hru. Nastaví príslušný stav hry.", "(QUIT)|(EXIT)", 2);
    pars->commands[1].command = create_command("SEVER", "Presun do miestnosti nachádzajúcej sa na sever od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(S)", 1);
    pars->commands[2].command = create_command("JUH", "Presun do miestnosti nachádzajúcej sa na juh od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(J)", 1);
    pars->commands[3].command = create_command("VYCHOD", "Presun do miestnosti nachádzajúcej sa na východ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(V)", 1);
    pars->commands[4].command = create_command("ZAPAD", "Presun do miestnosti nachádzajúcej sa na západ od aktuálnej. Zmení referenciu aktuálnej miestnosti.", "(Z)", 1);
    pars->commands[5].command = create_command("ROZHLIADNI SA", "Príkaz vypíše aktuálne informácie o miestnosti, v ktorej sa hráč práve nachádza.", "", 0);
    pars->commands[6].command = create_command("PRIKAZY", "Príkaz vypíše na obrazovku zoznam všetkých príkazov, ktoré hra poskytuje.", "(HELP)|(POMOC)", 2);
    pars->commands[7].command = create_command("VERZIA", "Príkaz zobrazí číslo verzie hry, ľubovoľný sprievodný text a meno a priezvisko autora s kontaktom (e-mailová adresa, webová stránka).", "", 0);
    pars->commands[8].command = create_command("RESTART", "Znovu spustí hru od začiatku. Zmení stav hry na požadovaný.", "", 0);
    pars->commands[9].command = create_command("O HRE", "Príkaz zobrazí krátky text, ktorý poslúži ako úvod do príbehu. Ako dobrý začiatok sa javí známy text: Kde bolo tam bolo, …", "(ABOUT)", 1);
    pars->commands[10].command = create_command("VEZMI", "Vloží predmet z miestnosti do batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš vziať.).", "", 0);
    pars->commands[11].command = create_command("POLOZ", "Položí predmet z batohu do miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš položiť.)", "", 0);
    pars->commands[12].command = create_command("INVENTAR", "Zobrazí obsah hráčovho batohu.", "(I)", 1);
    pars->commands[13].command = create_command("POUZI", "Použije predmet z batohu alebo miestnosti. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš použiť.).", "", 0);
    pars->commands[14].command = create_command("PRESKUMAJ", "Vypíše opis predmetu, ktorý sa musí nachádzať v miestnosti alebo batohu. Príkaz má jeden povinný parameter, ktorým je názov predmetu. Ak predmet nebude zadaný alebo sa nenájde v batohu alebo v miestnosti, program vypíše na obrazovku vhodnú hlášku (napr. Neviem, čo chceš preskúmať.).", "", 0);
    pars->commands[15].command = create_command("NAHRAJ", "Príkaz zabezpečí nahratie uloženej pozície hry z disku. Voliteľným parametrom je cesta k súboru.", "(LOAD)", 1);
    pars->commands[16].command = create_command("ULOZ", "Príkaz uloží stav rozohratej hry na disk. Voliteľným parametrom je cesta k súboru.", "(SAVE)", 1);
}

void set_res_commands (struct parser *pars, struct parser *res_pars)
{
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[0].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[1].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[2].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[3].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[4].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[5].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[6].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[7].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[8].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[9].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[10].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[11].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[12].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[13].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[14].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[15].command);
    res_pars->commands = create_container(res_pars->commands, COMMAND, pars->commands[16].command);
}
