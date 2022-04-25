#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

struct data{
    double z, r;
};

void mzero(int s);
void pol_dil(struct data mas[], double volume_cut, int num, int cut);
double f(struct data mas[], int len, double min, double max);
double calculate_buble(double r);
double calculate_buble_sector(double r, double h);
double search_buble(struct data buble, double min, double max);



int main(){
    int m, s;
    scanf("%d %d", &m, &s);
    struct data mas[m+1];

    double bufx, bufy;
    for(int i=0; i < m; i++){
        scanf("%lf %lf %lf %lf", &(mas[i].r), &bufx, &bufy, &(mas[i].z));
        mas[i].r /= 1000;
        mas[i].z /= 1000;
    }
    if(m == 0){
        mzero(s);
        return 0;
    }
    else if(s == 1){
        printf("100\n");
        return 0;
    }

    double bubles_v = 0;
    for(int i = 0; i < m; i++){
        bubles_v += calculate_buble(mas[i].r);
    }
    double correct_v = (1000000 - bubles_v)/s;
    pol_dil(mas, correct_v, m, s);


    return 0;
}

void pol_dil(struct data mas[], double volume_cut, int m, int s){
    double min = 0, max = 100, centr = min, c_min = 0, f_min, f_centr, f_max,  last = 100, buf;

    for(int i = 0; i < s-1; i++){
        do{
            buf = centr;
            centr = (min + max)/2;

            // printf("min: %lf\ncentr: %lf\nmax: %lf\n", min, centr, max);
            // printf("_min: %lf\n_centr: %lf\n_max: %lf\n\n", f_min, f_centr, f_max);

            f_min = f(mas, m, c_min, min);
            f_centr = f(mas, m, c_min, centr);
            f_max = f(mas, m, c_min, max);


            if(f_min == f_centr || f_max == f_centr || f_centr == 0 ||buf == centr) {
                break;
            }
            else if((f_min-volume_cut) * (f_centr-volume_cut) < 0){
                max = centr;
            }
            else if((f_max-volume_cut) * (f_centr-volume_cut) < 0){
                min = centr;
            }
        }while(fabs(f_centr-volume_cut) > 0.00000001);

        printf("%.9lf\n", centr - c_min);

        last -= centr - c_min;
        c_min = centr;
        buf = c_min;
        max = 100;
        min = c_min + 0.0000000001;
    }

    printf("%.9lf\n", last);
}

double f(struct data mas[], int len, double min, double max){
    double bubles_v = 0;
    for(int i=0; i < len; i++){
        bubles_v += search_buble(mas[i], min, max);
    }
    double cheese_v = 100 * 100 * (max-min);

    return cheese_v - bubles_v;
}

double search_buble(struct data buble, double min, double max){
    if(buble.z - buble.r < min && max < buble.z + buble.r){
        double buf = calculate_buble(buble.r);
        buf -= calculate_buble_sector(buble.r, fabs(min - buble.z + buble.r));
        buf -= calculate_buble_sector(buble.r, fabs(max - buble.z - buble.r));
        return buf;
    }
    else if(buble.z - buble.r < max && max < buble.z + buble.r){
        return calculate_buble_sector(buble.r, fabs(max - buble.z + buble.r));
    }
    else if(buble.z - buble.r < min && min < buble.z + buble.r){
        return calculate_buble_sector(buble.r, fabs(min - buble.z - buble.r));
    }
    else if(min <= buble.z - buble.r && buble.z + buble.r <= max){
        return calculate_buble(buble.r);
    }
    return 0;
}

void mzero(int s){
    for(int i = 0; i < s; i++){
        printf("%.9lf\n", (double)100/s);
    }
}

double calculate_buble(double r){
    double result = (double)(4 * r*r*r * PI) / 3;
    return result;
}

double calculate_buble_sector(double r, double h){
    double result = (double)(PI * h*h) * (r - (h/3));
    return result;
}
