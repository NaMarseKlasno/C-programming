// Stanislav Voloshyn
// @pchoul - telegram

// Created by Macbook Pro on 20.03.2021.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int bubbleSort (int arr[][2], int n);

bool testValue(double k, int arr[][2], int t, int parts, double *value, short count) {
    double res = 0;
    for (int i = 0; i < parts; ++i) {
        if ( ((double)arr[i][1] + k) != 0 ) {
            res += (double)arr[i][0] / ((double)arr[i][1] + k);
        }
    }
    //printf("k: %f -> time: %f\n", k, res);

    if (count == 1) {
        if (*value > res) *value = -1;
        else *value = res;
    }

    if (count == 2) {
        static short nw = 0;
        if (*value <= (double)t && nw != 0) {
            *value = -1;
        }
        else *value = res;
        nw = 1;

    }

    if (res == t) return true;
    return false;
}




int rac (void)
{
    int nParts = 0, q = 0, t = 0;
    short count = 1;
    scanf("%d %i", &nParts, &t);

    int mainArr[nParts][2];
    for (int i = 0; i < nParts; ++i) {
        for (int j = 0; j < 2; ++j) {
            scanf("%i", &q);
            mainArr[i][j] = q;
        }
    }
//  ====================================================================================
//                              ПРОВЕРКА НА ПРОСТОЙ ОТВЕТ
//  ====================================================================================

    double i = -1000;

    i = (double) bubbleSort(mainArr, nParts) * -1;
    //float min = i;
    double value = 0.0;

    for (i = i; i < 1000; ++i) {
        if (testValue(i, mainArr, t, nParts, &value, count)) {
            printf("%f\n", i);
            return 0;
        } if (value == -1) break;
    }
    //printf("save: %f\n", save);
    //printf("last i: %f\n", i);

    double from = i-2;
    double to = i;

    //printf("from: %f\n", from);
    //printf("to : %f\n", to);
    //printf("=====================\n");
//  ====================================================================================
//                              'К' С ПЛАВАЮЩЕЙ ТОЧКОЙ
//  ====================================================================================
    value = 0.0;
    count = 1;
    bool same = false;

    for (double i = from; i < to; i += 0.000001) {
        if (testValue(i, mainArr, t, nParts, &value, count)) {
            printf("%f\n", i);
            return 0;
        } if (value == -1) {
            to = i-0.000001;
            same = true;
            break;
        }
        count = 2;
    }


    if (same) printf("%f\n", to);

    return 0;
}


int main(void)
{
    rac();
    return 0;
}


int bubbleSort (int arr[][2], int n) {
    int i, j;

    int qwerty[n];
    for (int i = 0; i < n; ++i) qwerty[i] = arr[i][1];

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (qwerty[j] > qwerty[j+1]) {
                int tmp = qwerty[j];
                qwerty[j] = qwerty[j+1];
                qwerty[j+1] = tmp;
            }
        }
    }

    return qwerty[0];
}















//979.000490763
//998.000853868
