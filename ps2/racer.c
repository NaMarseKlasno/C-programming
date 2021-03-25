// Stanislav Voloshyn
// @pchoul - telegram


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int bubbleSort (int arr[][2], int n);

bool testValue2(long double k, int arr[][2], int t, int parts, long double *value) {
    long double res = 0;
    for (int i = 0; i < parts; ++i) {
        if ( ((long double)arr[i][1] + k) != 0 ) {
            res += (long double)arr[i][0] / ((long double)arr[i][1] + k);
        } else return false;
    } if (*value == -103725598) return false;
    //printf("2k: %.9Lf -> 2time: %.9Lf\n", k, res);
    *value = res;
    if (*value >= (double)t) {
        return true;
    }
    else {
        *value = res;
        return false;
    }
}

bool testValue(long double k, int arr[][2], int t, int parts, long double *value, short count) {
    long double res = 0;
    for (int i = 0; i < parts; ++i) {
        if ( ((long double)arr[i][1] + k) != 0 ) {
            res += (long double)arr[i][0] / ((long double)arr[i][1] + k);
        } else return false;
    }
    //printf("k: %.9Lf -> time: %.9Lf\n", k, res);
    
    if (count == 1) {
        if (*value >= res) *value = -10372;
        else *value = res;
    }
    
    if (count == 2) {
        static short nw = 0;
        if (*value <= (long double)t && nw != 0) {
            *value = -10372;
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
    
    long double i = -1001;
    bool stop1 = true;
    
    i = (double) bubbleSort(mainArr, nParts) * -1;
    long double value = 0.0;
    
    for (i = i; i <= 1002; ++i) {
        if (testValue(i, mainArr, t, nParts, &value, count)) {
            printf("%.6Lf\n", i);
            return 0;
        } if (value == -10372) break;

        while (stop1 == true && testValue2(0, mainArr, t, nParts, &value)) i = 0        
        while (stop1 == true && testValue2(i+100, mainArr, t, nParts, &value)) i+=100;
        while (stop1 == true && testValue2(i+90, mainArr, t, nParts, &value)) i+=90;
        while (stop1 == true && testValue2(i+80, mainArr, t, nParts, &value)) i+=80;
        while (stop1 == true && testValue2(i+70, mainArr, t, nParts, &value)) i+=70;
        while (stop1 == true && testValue2(i+60, mainArr, t, nParts, &value)) i+=60;
        while (stop1 == true && testValue2(i+50, mainArr, t, nParts, &value)) i+=50;
        while (stop1 == true && testValue2(i+40, mainArr, t, nParts, &value)) i+=40;
        while (stop1 == true && testValue2(i+30, mainArr, t, nParts, &value)) i+=30;
        while (stop1 == true && testValue2(i+20, mainArr, t, nParts, &value)) i+=20;
        while (stop1 == true && testValue2(i+10, mainArr, t, nParts, &value)) i+=10;
        while (stop1 == true && testValue2(i+1, mainArr, t, nParts, &value)) i+=1;

        stop1 = false;

    }
    //printf("last i: %Lf\n", i);
    
    long double from = i-2;
    long double to = i;

    //printf("from: %Lf\n", from);
    //printf("to : %Lf\n", to);
    //printf("=====================\n");
    
//  ====================================================================================
//                              'К' С ПЛАВАЮЩЕЙ ТОЧКОЙ
//  ====================================================================================
    value = 0.0;
    count = 1;
    //bool same = false, 
    bool stop = true;
    
    for (long double i = from; i < to; i += 0.000000001) {
        if (testValue(i, mainArr, t, nParts, &value, count)) {
            printf("%.6Lf\n", i);
            return 0;
        }
        if (value == -10372) {
            to = i-0.000000001;
            //same = true;
            break;
        } count = 2;
        
        while (stop == true && testValue2(i+1, mainArr, t, nParts, &value)) i+=1;
        while (stop == true && testValue2(i+0.1, mainArr, t, nParts, &value)) i+=0.1;
        while (stop == true && testValue2(i+0.01, mainArr, t, nParts, &value)) i+=0.01;
        while (stop == true && testValue2(i+0.001, mainArr, t, nParts, &value)) i+=0.001;
        while (stop == true && testValue2(i+0.0001, mainArr, t, nParts, &value)) i+=0.0001;
        while (stop == true && testValue2(i+0.00001, mainArr, t, nParts, &value)) i+=0.00001;
        while (stop == true && testValue2(i+0.000001, mainArr, t, nParts, &value)) i+=0.000001;
        while (stop == true && testValue2(i+0.0000001, mainArr, t, nParts, &value)) i+=0.0000001;
        while (stop == true && testValue2(i+0.00000001, mainArr, t, nParts, &value)) i+=0.00000001;
        while (stop == true && testValue2(i+0.000000001, mainArr, t, nParts, &value)) i+=0.000000001;

        stop = false;
    }
    
    //double suckmydick = 0.0;
    //if (same) 
    printf("%.6Lf\n", to);
    //else printf("%f\n", suckmydick);
    
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
