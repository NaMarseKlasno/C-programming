#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k.h"
#include "ui.h"
#include "hof.h"

int main()
{
    struct player *list = malloc(sizeof(struct player) * 10);
    int hof_size = load(list);

    struct player *player1 = malloc(sizeof(player1));
    player1->score = 12;
    char *name = "Hello";
    strcpy(player1->name, name);

    add_player(list, &hof_size, *player1);
    save(list, hof_size);

    for (int i=0; i<hof_size; i++)
    {
        printf("%s\t%d\n", list[i].name, list[i].score);
    }

    struct game game = {
            .board = {
                    {'A', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' '},
                    {'A', ' ', ' ', ' '}
            },
            .score = 0
    };

    render(game);

    while (true)
    {
        int flag = getchar();
        switch (flag)
        {
            case 119:
                if (update(&game, -1, 0)) add_random_tile(&game);
                render(game);
                break;
            case 97:
                if (update(&game, 0, 1)) add_random_tile(&game);
                render(game);
                break;
            case 115:
                if (update(&game, 1, 0)) add_random_tile(&game);
                render(game);
                break;
            case 100:
                if (update(&game, 0, -1)) add_random_tile(&game);
                render(game);
                break;
            case 101:
                free(list);
                free(player1);
                return 0;
            default:
                break;
        }
    }
}
