#include "k.h"
#include "ui.h"
#include "hof.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    struct game game = {
            .board = {
                    {'A', ' ', ' ', ' '},
                    {' ', ' ', 'A', ' '},
                    {' ', ' ', ' ', 'B'},
                    {'A', ' ', ' ', ' '}
            },
            .score = 0
    };

    render(game);

    //  ============================================================
    //                      ГЛАВНЫЙ ЦИКЛ ИГРЫ
    //  ============================================================

    while (1) {

        if (is_game_won(game)) return 0;
        if (!is_move_possible(game)) return 0;

        int consT = getchar();
        switch (consT)
        {
            case 119:
                if (update(&game, -1, 0))
                    add_random_tile(&game);
                render(game);
                break;
            case 115:
                if (update(&game, 1, 0))
                    add_random_tile(&game);
                render(game);
                break;
            case 101:
                free(list);
                free(player1);
                return 0;
            case 100:
                if (update(&game, 0, -1))
                    add_random_tile(&game);
                render(game);
                break;
            case 97:
                if (update(&game, 0, 1))
                    add_random_tile(&game);
                render(game);
                break;
            default:
                break;
        }
    }
    free(player1);
    free(list);

    //  ============================================================
    //                  ПРОВЕРКА ФУНКЦИОНАЛЬНОСТИ
    //  ============================================================

    struct player *list = calloc(10, sizeof(struct player) );
    int hof_size = load(list);

    struct player *player1 = calloc( 1, sizeof(player1));
    strcpy(player1->name, "Plcololo");
    player1->score = 228;

    add_player(list, &hof_size, *player1);
    save(list, hof_size);

    for (int i = 0; i < hof_size; i++) printf("%s %d\n", list[i].name, list[i].score);

    return 0;
}
