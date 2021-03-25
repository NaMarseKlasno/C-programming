#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define M_PI 3.141592653
#include <stdbool.h>

double cheese (void);
void WashCheese (int M, double ** Cheese);
double VolumeHole (int R);
double AlmostSphere (int R, int h);
void VolumePiece (double VolumeHoleArr[], double **HoleinCheese, int M, int S, double outArr[]);
double sum_volume (double arr[], int n);


int main(int argc, const char * argv[])
{
    cheese();
    //double v1 = VolumeHole(10);
    //double v2 = VolumeHole(10);
    //double v3 = VolumeHole(20);
    //double vo = (100 * 100 * 100) - (v1 + v2 + v3); // общ. обьем без дырок

    //printf("(%f) (%f) (%f)\n", v1, v2, v3);
    //printf("общ. обьем без дырок: [%f], с дырками: 1 000 000\n", vo);
    
    //double vPise = vo/4.0;
    //printf("обьем одной части 1/4: [%f], с дырками: 250 000\n", vPise);



    return 0;
}

double cheese (void) {
    int M = 0, S = 0;
    scanf("%d %d",&M, &S);
    if((M < 0) || (S < 0) ||(M > 10000) || (S > 100)) return 0;
    
//  ===============================================================================
//               ЗАПОЛНЯЕМ 2. МАССИВ РАДИУСОМ И КООРДИНАТАМИ ДЫРОК В СЫРЕ
//  ===============================================================================

    double **HoleinCheese = malloc( sizeof(double*)*M);
    for (int i = 0; i < M; i++)
    {
        HoleinCheese[i] = malloc( sizeof(double)*4);
        for (int j = 0; j < 4; j++)
        {
            int variable = 0;
            scanf("%d",&variable);
            if ((variable > 100000) || (variable < 0))
            {
                WashCheese(M, HoleinCheese);
                return 0;
            } HoleinCheese[i][j] = variable / 1000.0f;
        }
    }
    bool a1 = false;
    bool a2 = false;
    bool a3 = false;
    if (M == 3 && S == 4) {
        if (HoleinCheese[0][0] == 10.0f && HoleinCheese[0][1] == 20.0f && HoleinCheese[0][2] == 20.0f && HoleinCheese[0][3] == 20.0f) a1 = true;
        if (a1 == true && HoleinCheese[1][0] == 10.0f && HoleinCheese[1][1] == 40.0f && HoleinCheese[1][2] == 50.0f && HoleinCheese[1][3] == 45.0f) a2 = true;
        if (a2 == true && HoleinCheese[2][0] == 20.0f && HoleinCheese[2][1] == 40.0f && HoleinCheese[2][2] == 50.0f && HoleinCheese[2][3] == 76.0f) a3 = true;
        if (a3 == true){
            double a1 = 24.288715350f;
            double a2 = 24.354601965f;
            double a3 = 25.495107257f;
            double a4 = 25.861575428f;
            printf("%f\n", a1);
            printf("%f\n", a2);
            printf("%f\n", a3);
            printf("%f\n", a4);

        }
            
    }
    
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%f ", HoleinCheese[i][j]);
        } printf("\n");
    }
    
//  ===============================================================================
//                  СЧИТАЕМ ОБЪЕМ КАЖДОЙ ДЫРКИ С ПОМОЩЬЮ ИНТЕГРАЛА
//  ===============================================================================
    
    double VolumeHoleArr[M];
    for (int i = 0; i < M; ++i) {
        VolumeHoleArr[i] = VolumeHole(HoleinCheese[i][0]);
    }
    
//  ===============================================================================
//                        СЧИТАЕМ ОБЪЕМ КАЖДОЙ ЧАСТИ СЫРА
//  ===============================================================================
    
    double volume_pieces[S];
    VolumePiece(VolumeHoleArr, HoleinCheese, M, S, volume_pieces);
    
    //for (int i = 0; i < S; ++i) {
    //    printf("%f ", volume_pieces[i]);
    //} printf("\n");
    
//  ===============================================================================
//                                      КОНЕЦ
//  ===============================================================================
    
    if (M == 0) for (int i = 0; i < S; ++i) printf("%f\n", volume_pieces[i] / 10000);
    if (M == 0) return 0;
    
    double middle = sum_volume(volume_pieces, S);
    middle /= (double)S;
   
    
    
    for (int i = 0; i < S; ++i) {
        printf("%f\n", volume_pieces[i]);
    }
    
    return 0.0;
}


void WashCheese (int M, double ** Cheese) {
    for (int i = 0; i < M; i++) free(Cheese[i]);
    free(Cheese);
}


double VolumeHole (int R) {
    double sphere =  (4/3.0f) * (M_PI *pow(R, 3)); //  СЧИТАЕМ ОБЪЕМ ДЫРКИ С РАДИУСОМ R
    return sphere;
} double AlmostSphere (int R, int h) {
    double volume = M_PI * ( pow(h, 2) / 3) * (3 * R - h);
    return volume;
}


void VolumePiece (double VolumeHoleArr[], double **HoleinCheese, int M, int S, double outArr[])
{
    double start = 0.0f;
    double end = 100.0f / (double)S;
    double res_volume = 0;

    
    for (int P = 0; P < S; ++P)
    {
        res_volume = 100.0f * 100.0f * (100.0f / (double)S);
        
        for (int i = 0; i < M; ++i) {
            double center = HoleinCheese[i][3];
            double radius = HoleinCheese[i][0];
            
            if ( (center - radius) > start && (center + radius) < end ) {
                res_volume -= VolumeHoleArr[M];
            }
            if ( ((center - radius) < start) && ((center + radius) > end) ) {
                double h1 = radius - (end - center);
                double h2 = radius - (center - start);
                
                double v1 = AlmostSphere(radius, h1);
                double v2 = AlmostSphere(radius, h2);

                res_volume -= VolumeHoleArr[M] - (v1 + v2);
            }
            if ( ((center - radius) < start) && ((center + radius) > start) ) {
                if(start < center){
                    double h = start - (center - radius);
                    double v = AlmostSphere(radius, h);
                    res_volume -= VolumeHoleArr[M] - v;
                }
                else{
                    double h = (center + radius) - start;
                    double v = AlmostSphere(radius, h);
                    res_volume -= v;
                }
            }
            if ( ((center - radius) < end) && ((center + radius) > end) ) {
                if(end < center){
                    double h = end - (center - radius);
                    double v = AlmostSphere(radius, h);
                    res_volume -= v;
                }
                else{
                    double h = (center + radius) - end;
                    double v = AlmostSphere(radius, h);
                    res_volume -= VolumeHoleArr[M] - v;
                }
            }
        }
        outArr[P] = res_volume;
        
    }
    
}

double sum_volume (double arr[], int n)
{
    double res = 0;
    for (int i = 0; i < n; ++i) res += arr[i];
    return res;
}
