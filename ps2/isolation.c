#include <stdio.h>
#include <stdlib.h>

void isolation(void);

int main()
{
    isolation();
    return 0;
}

void isolation(void)
{
    int a, b, t;
    scanf("%i %i", &a, &b);

    //int mainArr[a][b];
    int **mainArr = (int **)calloc(a, sizeof(int *));
    if (mainArr == NULL) {
        free(mainArr);
        mainArr = NULL;
        exit(1);
    }
    for(int i = 0; i < a; i++) {
        mainArr[i] = (int *)calloc(b, sizeof(int));
        if (mainArr == NULL) {
            free(mainArr);
            mainArr = NULL;
            exit(1);
        }
    }

    // заполняем главную матрицу входными данными
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            scanf("%i", &t);
            mainArr[i][j] = t;
        }
    }
    // выводим в терминал главную матрицу


    //char bgArr[a][b];
    char **bgArr = (char **)calloc(a, sizeof(char *));
    if (bgArr == NULL) {
        free(bgArr);
        bgArr = NULL;
        exit(1);
    }
    for(int i = 0; i < a; i++) {
        bgArr[i] = (char *)calloc(b, sizeof(char ));
        if (bgArr == NULL) {
            free(bgArr);
            bgArr = NULL;
            exit(1);
        }
    }

    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            if (j == 0) bgArr[i][j] = 'Y';
            else if (mainArr[i][j] < mainArr[i][0]) {
                if (mainArr[i][j] < mainArr[i][j-1]) bgArr[i][j] = 'A';
                else bgArr[i][j] = 'B';
            } else if (mainArr[i][j] > mainArr[i][0]) {
                if (mainArr[i][j] < mainArr[i][j-1]) bgArr[i][j] = 'C';
                else bgArr[i][j] = 'D';
            }
        }
    }
    for(int i = 0; i < a; i++) free(mainArr[i]);
    free(mainArr);

    //printf("result down\n");
    //for (int i = 0; i < a; ++i) {
    //    for (int j = 0; j < b; ++j) {
    //        printf("%c ", bgArr[i][j]);
    //    }
    //    printf("\n");
    //}

    // LX - A
    // XL - B
    // RX - C
    // XR - D
    char test;

    // сортировка bgArr
    for (int i = 0; i < a; ++i)
    {
        for (int q = 0; q < b; ++q) {
            for (int j = 0; j < b - 1; ++j) {
                if (bgArr[i][j] > bgArr[i][j+1]) {
                    test = bgArr[i][j];
                    bgArr[i][j] = bgArr[i][j+1];
                    bgArr[i][j+1] = test;
                }
            }
        }
    }

    int* helpArr = (int *)calloc(a+1, sizeof(int));
    if (helpArr == NULL) {
        free(helpArr);
        helpArr = NULL;
        exit(1);
    }
    int value = 0;

    for (int i = 0; i < a; ++i) {
        for (int x = 0; x < a; ++x) {
            for (int y = 0; y < b; ++y) {
                if (bgArr[i][y] == bgArr[x][y]) value++;
            }
            if (value == b) helpArr[i] = helpArr[i]+1;
            value = 0;
        }
    }

    int max = helpArr[0];
    for (int i = 0; i < a; ++i) {
        if (helpArr[i] > max) max = helpArr[i];
    }
    //printf("max: %d\n", max);

    int res = (a - max)+1;
    //if (helpArr[0] == 1) res -= 1;
    printf("%d\n", res);

    free(helpArr);

    for(int i = 0; i < a; i++) free(bgArr[i]);
    free(bgArr);
}
