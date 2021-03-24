// Stanislav Voloshyn
// @pchoul - telegram


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int bubbleSort (int arr[][2], int n);

bool testValue(long double k, int arr[][2], int t, int parts, double *value, short count) {
    double res = 0;
    for (int i = 0; i < parts; ++i) {
        if ( ((long double)arr[i][1] + k) != 0 ) {
            res += (long double)arr[i][0] / ((long double)arr[i][1] + k);
        }
    }
    //printf("k: %Lf -> time: %Lf\n", k, res);
    
    if (count == 1) {
        if (*value > res) *value = -1;
        else *value = res;
    }
    
    if (count == 2) {
        static short nw = 0;
        if (*value <= (long double)t && nw != 0) {
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
    
    long double i = -10000;
    double value = 0.0;
    long double from = i-2;
    long double to = i;

    i = (long double) bubbleSort(mainArr, nParts) * -1;
    
    for (i = i; i <= 1001; ++i) {
        if (testValue(i, mainArr, t, nParts, &value, count)) {
            printf("%.6Lf\n", i);
            return 0;
        } if (value == -1) break;
    }
    //printf("last i: %Lf\n", i);
    
    //printf("from: %Lf\n", from);
    //printf("to : %Lf\n", to);
    //printf("=====================\n");
    
//  ====================================================================================
//                              'К' С ПЛАВАЮЩЕЙ ТОЧКОЙ
//  ====================================================================================
    value = 0.0;
    count = 1;
    bool same = false;
    
    for (long double i = from; i <= 10000.0; i += 0.000000001) {
        if (testValue(i, mainArr, t, nParts, &value, count)) {
            printf("%.6Lf\n", i);
            return 0;
        } if (value == -1) {
            to = i-0.000000001;
            same = true;
            break;
        }
        count = 2;
    }
    
    
    if (same) printf("%.6Lf\n", to);
    
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
