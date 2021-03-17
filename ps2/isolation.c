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
    //printf("Main arr is down\n");

    // выводим в терминал главную матрицу
    //for (int i = 0; i < a; ++i) {
    //    for (int j = 0; j < b; ++j) {
    //        printf("%i ", mainArr[i][j]);
    //    }
    //printf("\n");
    //}

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
    } //printf("============\n");

    int value = 0;
    //int helpArr[b];
    int* helpArr = (int *)calloc(b+1, sizeof(int));
    if (helpArr == NULL) {
        free(helpArr);
        helpArr = NULL;
        exit(1);
    }
    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            for (int k = 0; k < a; ++k) {
                if (bgArr[i][j] == bgArr[k][j]) ++value;
            } helpArr[j] = value;
            value = 0;
        }
    }
    for(int i = 0; i < a; i++) free(bgArr[i]);
    free(bgArr);

    // сортировка пузырком массива helpArr
    int ts;
    for (int j = 0; j < b - 1; ++j) {
        if (helpArr[j] > helpArr[j + 1]) {
            ts = helpArr[j];
            helpArr[j] = helpArr[j + 1];
            helpArr[j + 1] = ts;
        }
    }

    // просто выводим на экран
    //for (int i = 0; i < a; ++i) {
    //    for (int j = 0; j < b; ++j) {
    //        printf("%c ", bgArr[i][j]);
    //    }
    //    printf("\n");
    //}

    //printf("[%s] %d\n", bgArr[1], value);

    //for (int i = 0; i < b; ++i) {
    //    printf("%d ", helpArr[i]);
    //} printf("\n");

    int res = (a - helpArr[0])+1;
    if (helpArr[0] == 1) res -= 1;
    printf("%d\n", res);
    free(helpArr);
}
