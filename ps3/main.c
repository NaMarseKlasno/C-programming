#include <stdio.h>
#include "k.h"
#include "hof.h"

int main() {
    // move right
    struct game game = {
            .board = {
                    {'A', ' ', ' ', ' '},
                    {'B', ' ', ' ', 'B'},
                    {'C', 'C', 'C', ' '},
                    {'D', 'D', 'D', 'D'}
            },
            .score = 0
    };

    bool result = update(&game, 0, 1);
/*
game = {
    .board = {
        {' ', ' ', ' ', 'A'},
        {' ', ' ', ' ', 'C'},
        {' ', ' ', 'C', 'D'},
        {' ', ' ', 'E', 'E'}
    },
    .score = 88
};
result = true;
*/

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; ++j) {
            printf("%c  ", game.board[i][j]);
        } printf("\n");
    }

    

    return 0;
}
