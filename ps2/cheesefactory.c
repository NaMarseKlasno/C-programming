#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M_PI 3.141592653
#define oblik(r,h)\
    ({double _r = (r), _h = (h); M_PI * (pow(_h,2)/3)*(3*_r - _h);})
/*
#define oblik(r,h)\
    ({double _r = (r), _h = (h); M_PI*(_h - (1/3.0f) + (pow(1 - _h,3)/3.0f));})
    */

#define objem_g(r)\
    ({double _r = (r); (4/3.0f)*( M_PI *pow(_r,3));})

#define PRESNOST_PLATKA 0.0000001f
#define TEHLA_A 100
#define VYPIS_PRESNOST std::setprecision(9)

void find_cheese_cut(double **holes, double cut[], int M, int S);
double find_measure(double **holes, double start, double end, int M, double platok);

int main(){

    int M = 0, S = 0;
    scanf("%d %d",&M, &S);
    if((M < 0) || (S < 0) ||(M > 10000) || (S > 100)){
        return 0;
        }
    double **ch_holes = malloc( sizeof(double*)*M);
    for(int i = 0; i < M; i++){
        ch_holes[i] = malloc( sizeof(double)*4);
        for(int j = 0; j < 4; j++){
            int temp = 0;
            scanf("%d",&temp);
            if((temp < 0)||(temp > 100000)){
                for(int i = 0; i < M; i++){
                    free(ch_holes[i]);
                }
                free(ch_holes);
                return 0;
            }
            ch_holes[i][j] = temp / 1000.0f;
        }
    }
    double ch_cut[S];
    
    if(M == 0){
        for(int i = 0; i < S; i++){
            ch_cut[i] = TEHLA_A / S;
        }
    }
    else{
        find_cheese_cut(ch_holes, ch_cut, M, S);
    }
    
    for(int i = 0; i < S; i++){
        printf("%.9f\n",ch_cut[i]);
    }
    for(int i = 0; i < M; i++){
        free(ch_holes[i]);
    }
    free(ch_holes);
    return 0;
}

void find_cheese_cut(double **holes,double cut[], int M, int S){
    double volume_plate_cheese = TEHLA_A*TEHLA_A*TEHLA_A;
    for(int i = 0; i < M; i++){
        volume_plate_cheese -= objem_g(holes[i][0]);
    }
    volume_plate_cheese /= S;
    double platok_zac = 0.0f;
    double platok_end = TEHLA_A/S;
    
    for(int i = 0; i < S; i++){
        platok_end = find_measure(holes, platok_zac, platok_end, M, volume_plate_cheese);
        cut[i] =  platok_end - platok_zac;
        platok_zac = platok_end;
        platok_end += TEHLA_A/S;
    }
}

double find_measure(double **holes, double start, double end, int M, double platok){
    double act_volume = (end - start)*TEHLA_A*TEHLA_A;
    for(int i = 0;i < M;i++){
        double g_center = holes[i][3], g_rad = holes[i][0];
        double cut_v, h,oblik;
        if(((g_center - g_rad) > start)&&((g_center + g_rad) < end)){
            cut_v = objem_g(g_rad);
            act_volume -= cut_v;
        }
        if(((g_center - g_rad) < start)&&((g_center + g_rad) > end)){
            h = (g_center - g_rad) - start;
            oblik = oblik(g_rad,h);
            cut_v = objem_g(g_rad) - oblik;
            h = (g_center + g_rad) - end;
            oblik = oblik(g_rad,h);
            cut_v -= oblik;
            act_volume -= cut_v;
        }
        if((start != 0)&&(((g_center - g_rad) < start)&&((g_center + g_rad) > start))){
            if(start < g_center){
                h = start - (g_center - g_rad);
                oblik = oblik(g_rad,h);
                cut_v = objem_g(g_rad) - oblik;
                act_volume -= cut_v;
            }
            else{
                h = (g_center + g_rad) - start;
                oblik = oblik(g_rad,h);
                act_volume -= oblik;
            }
        }
        if((end != 0)&&(((g_center - g_rad) < end)&&((g_center + g_rad) > end))){
            if(end > g_center){
                h = (g_center + g_rad) - end;
                oblik = oblik(g_rad,h);
                cut_v = objem_g(g_rad) - oblik;
                act_volume -= cut_v;
            }
            else{
                h = end - (g_center - g_rad);
                oblik = oblik(g_rad,h);
                act_volume -= oblik;
            }
        }
    }
    
    double return_end = end;
    double v_diff = fabs(platok - act_volume);
    if(v_diff > PRESNOST_PLATKA){
        if(platok > act_volume) return_end = find_measure(holes, start, end + (v_diff/10000), M, platok);
        else return_end = find_measure(holes, start, end - (v_diff/10000), M, platok);
    }
    return return_end;
}

