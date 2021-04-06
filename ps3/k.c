#include <stdlib.h>
#include <stdio.h>
#include "k.h"
#include <ctype.h>

void sum_up (char arr1[], char arr2[]) {
    int dictionary [11][2] = {
        {'A', 2},
        {'B', 4},
        {'C', 8},
        {'D', 16},
        {'E', 32},
        {'F', 64},
        {'G', 128},
        {'H', 256},
        {'I', 512},
        {'J', 1024},
        {'K', 2048}
    };
    //printf("%c\n", dictionary[10][0]);

    for (int i = 0; i < SIZE; ++i) {
        char a;
        int sum = 0;
        //char s1 = arr1[i];
        //char s2 = arr2[i];
        if (arr1[i] == arr2[i] && arr1[i] != ' ' && isupper(arr1[i]) && isupper(arr2[i])) {
            for (int j = 0; j < 11; ++j) if (arr1[i] == dictionary[j][0]) sum = dictionary[j][1] * 2;
            for (int j2 = 0; j2 < 11; ++j2) if (sum == dictionary[j2][1]) a = dictionary[j2][0];
            arr1[i] = tolower(a);
            arr2[i] = ' ';
        } else if (arr1[i] == ' ') {
            arr1[i] = arr2[i];
            arr2[i] = ' ';
        } //else arr2[i] = ' ';


    }

}

bool vector_movement (const struct game game, int dy, int dx) {
    if (dy == 0 && dx == 1) {  // right
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (game.board[i][j] == ' ')
                    for (int a = 0; a < j; ++a)
                        if (game.board[i][a] != ' ') return true;

                for (int k = 0; k < SIZE; ++k)
                    if (game.board[i][k] == game.board[i][j] && j != k && game.board[i][k] != ' ' && isupper(game.board[i][k]) && (j == k+1 || k == j+1) ) return true;
            }
        } return false;
    } else if (dy == 0 && dx == -1) {  // left
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (game.board[i][j] == ' ')
                    for (int a = j; a < SIZE; ++a)
                        if (game.board[i][a] != ' ') return true;

                for (int k = 0; k < SIZE; ++k)
                    if (game.board[i][k] == game.board[i][j] && j != k && game.board[i][k] != ' ' && isupper(game.board[i][k]) && (j == k+1 || k == j+1)) return true;
            }
        } return false;

    } else if (dy == 1 && dx == 0) {  // up
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (game.board[i][j] == ' ')
                    for (int a = i; a < SIZE; ++a)
                        if (game.board[a][j] != ' ') return true;

                for (int c = 0; c < SIZE; c++)
                    if (game.board[c][j] == game.board[i][j] && i != c && game.board[c][j] != ' ' && isupper(game.board[c][j]) && (i == c+1 || c == i+1)) return true;
            }
        } return false;

    } else if (dy == -1 && dx == 0) {  // down
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {

                if (game.board[i][j] == ' ')
                    for (int a = 0; a < i; ++a)
                        if (game.board[a][j] != ' ') return true;

                for (int c = 0; c < SIZE; c++)
                    if (game.board[c][j] == game.board[i][j] && i != c && game.board[c][j] != ' ' && isupper(game.board[c][j]) && (i == c+1 || c == i+1)) return true;
            }
        } return false;
    }
}


void add_random_tile(struct game *game) {
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    for (int x = 0; x < SIZE; ++x)
        for (int y = 0; y < SIZE; ++y)
            if (game.board[x][y] == 'K') return true;
    return false;
}

bool is_move_possible(const struct game game) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (game.board[i][j] == ' ') return true;
            for (int c = 0; c < SIZE; c++)
                if (game.board[c][j] == game.board[i][j] && i != c) return true;
            for (int k = 0; k < SIZE; ++k)
                if (game.board[i][k] == game.board[i][j] && j != k) return true;
        }
    } return false;
}

bool update(struct game *game, int dy, int dx) {

    if (dy == 0 && dx == 1 && vector_movement(*game, dy, dx) == true) {  // right
        char arr1[SIZE + 1] = {};
        char arr2[SIZE + 1] = {};

        for (int i = SIZE-1; i >= 1; --i) {
            for (int j = 0; j < SIZE; ++j) arr1[j] = game->board[j][i];
            for (int j = 0; j < SIZE; ++j) arr2[j] = game->board[j][i - 1];

            sum_up(&arr1, &arr2);

            for (int j = 0; j < SIZE; ++j) game->board[j][i] = arr1[j];
            for (int j = 0; j < SIZE; ++j) game->board[j][i-1] = arr2[j];

            if (i == 1 && vector_movement(*game, dy, dx) == true) i = SIZE;
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; ++j)
                game->board[i][j] = toupper(game->board[i][j]);
        return true;

    } else if (dy == 0 && dx == -1 && vector_movement(*game, dy, dx) == true) {  // left
        char arr1[SIZE + 1] = {};
        char arr2[SIZE + 1] = {};

        for (int i = 0; i < SIZE-1; ++i) {
            for (int j = 0; j < SIZE; ++j) arr1[j] = game->board[j][i];
            for (int j = 0; j < SIZE; ++j) arr2[j] = game->board[j][i+1];

            sum_up(&arr1, &arr2);

            for (int j = 0; j < SIZE; ++j) game->board[j][i] = arr1[j];
            for (int j = 0; j < SIZE; ++j) game->board[j][i+1] = arr2[j];

            if (i == SIZE-2 && vector_movement(*game, dy, dx) == true) i = -1;
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; ++j)
                game->board[i][j] = toupper(game->board[i][j]);
        return true;

    } else if (dy == 1 && dx == 0 && vector_movement(*game, dy, dx) == true) {  // up

        char arr1[SIZE + 1] = {};
        char arr2[SIZE + 1] = {};

        for (int i = 0; i < SIZE-1; ++i) {
            for (int j = 0; j < SIZE; ++j) arr1[j] = game->board[i][j];
            for (int j = 0; j < SIZE; ++j) arr2[j] = game->board[i+1][j];

            sum_up(&arr1, &arr2);

            for (int j = 0; j < SIZE; ++j) game->board[i][j] = arr1[j];
            for (int j = 0; j < SIZE; ++j) game->board[i+1][j] = arr2[j];

            if (i == SIZE-2 && vector_movement(*game, dy, dx) == true) i = -1;
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; ++j)
                game->board[i][j] = toupper(game->board[i][j]);
        return true;

    } else if (dy == -1 && dx == 0 && vector_movement(*game, dy, dx) == true) {  // down

        char arr1[SIZE + 1] = {};
        char arr2[SIZE + 1] = {};

        for (int i = SIZE-1; i >= 1; --i) {
            for (int j = 0; j < SIZE; ++j) arr1[j] = game->board[i][j];
            for (int j = 0; j < SIZE; ++j) arr2[j] = game->board[i-1][j];

            sum_up(&arr1, &arr2);

            //for (int j = 0; j < SIZE; ++j) {
            //    printf("%c  ", arr1[j]);
            //} printf("\n");
            //for (int j = 0; j < SIZE; ++j) {
            //    printf("%c  ", arr2[j]);
            //} printf("\n=============\n");

            for (int j = 0; j < SIZE; ++j) game->board[i][j] = arr1[j];
            for (int j = 0; j < SIZE; ++j) game->board[i-1][j] = arr2[j];

            //printf("\n---------------\n");
            //for (int i1 = 0; i1 < SIZE; i1++){
            //    for (int j = 0; j < SIZE; ++j) {
            //        printf("%c  ", game->board[i1][j]);
            //    } printf("\n");
            //}
            //printf("\n---------------\n");


            if (i == 1 && vector_movement(*game, dy, dx) == true) i = SIZE;

            //getchar();
        }
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; ++j)
                game->board[i][j] = toupper(game->board[i][j]);
        return true;

    }

    return false;
}
