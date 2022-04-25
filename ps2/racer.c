#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct data{
    double v, s;
};


double f (struct data mas[], int len, double x);

int main() {
    int n;
    double t;
    scanf("%d %lf", &n, &t);

    struct data data[n+1];

    for(int i = 0; i < n; i++){

        scanf("%lf %lf", &(data[i].s), &(data[i].v));
    }


    double min = data[0].v, max = 3000, centr, f_min, f_max, f_centr, buf = min;

    for(int i = 0; i < n; i++){
        if(min > data[i].v){
            min = data[i].v;
        }
        if(max < data[i].v){
            max = data[i].v;
        }
    }
    min *= -1;


    do {
        buf = centr;
        centr = (min + max)/2;

        // printf("min: %lf\ncentr: %lf\nmax: %lf\n", min, centr, max);
        // printf("_min: %lf\n_centr: %lf\n_max: %lf\n\n", f_min, f_centr, f_max);

        f_min = f(data, n, min) - t;
        f_max = f(data, n, max) - t;
        f_centr = f(data, n, centr) - t;

        if(f_max * f_centr < 0){
            min = centr;
        }
        else if(f_min * f_centr < 0){
            max = centr;
        }

        if(buf == centr){
            break;
        }

    }while(fabs(f_centr) > 0.0000001);


    printf("%f\n",centr);

    return 0;
}

double f(struct data mas[], int len, double x){
    double sum = 0;
    for(int i=0; i < len; i++){
        sum += mas[i].s / (mas[i].v + x);
    }
    return sum;
}
