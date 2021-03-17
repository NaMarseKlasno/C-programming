#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void mm(void);


int main(void)
{
    // Mighty Method
    mm();
    
    // Perfect Isolation
    
    
    return 0;
}






void mm(void)
{
    
    
    long long n = 0;
    long long k, i, m, *arr = NULL;
    scanf("%lld", &n);

    for (m = 0, k = n; k != 0; m++) k /= 10;
    //printf("1st m = %lld\n", m);
   
    arr = (long long*)calloc(10*m+1, sizeof(int));
    if (arr == NULL) {
        free(arr);
        arr = NULL;
        exit(1);
    }
    
    for (i = 0, k = n; i < m; i++) {
        arr[i] = k % 10;
        k = k / 10;
    } //for ( i = m - 1; i >= 0; i--) printf("%lld ",arr[i]); printf("\n");
    
    
    //printf("m = %lld\n", m);

    for (int j = 0; m > 1; ++j) {
        n = 0;
        for ( i = m - 1; i >= 0; i--) n += arr[i];
        
        for (m = 0, k = n; k != 0; m++) k /= 10;

        //printf("in end n = %lld\n", n);
        //printf("in end m = %lld\n", m);
        
        arr = (long long*)realloc(arr, (10* m * sizeof(int))+1);
        if (arr == NULL) {
            free(arr);
            arr = NULL;
            exit(1);
        }
        for (i = 0; i < m; i++) {
            arr[i] = n % 10;
            n = n / 10;
        }
    
    }
    n = arr[0];
    printf("%lld\n", n);
    free(arr);
    arr = NULL;

    
}