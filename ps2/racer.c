// Stanislav Voloshyn
// @pchoul - telegram

// Created by Macbook Pro on 20.03.2021.

#include <stdio.h>
#include <stdbool.h>

int bubbleSort (int arr[][2], int n);

bool testValue(float k, int arr[][2], int t, int parts) {
    double res = 0;
    for (int i = 0; i < parts; ++i) {
        if ( ((float)arr[i][1] + k) != 0 ) {
            res += (float)arr[i][0] / ((float)arr[i][1] + k);
        }
    }
    printf("k: %f -> time: %f\n", k, res);
 
    if (res == t) return true;
    return false;
}



int rac (void)
{
    int nParts = 0, q = 0, t = 0;
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
    
    float i = -999;

    i = (float) bubbleSort(mainArr, nParts) * -1;
        
    for (i = i; i < 999; ++i) {
        if (testValue(i, mainArr, t, nParts)) {
            printf("%f\n", i);
            return 0;
        }
    }
    
//  ====================================================================================
//                         ПРОВЕРКА 'К' С ПЛАВАЮЩЕЙ ТОЧКОЙ
//  ====================================================================================
      
    
    
    
    
    printf("%f\n", i);
    return 0;
}


int main(void) {
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















