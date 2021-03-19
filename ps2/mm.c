// Mighty Method
// Stanislav Voloshyn
// @pchoul - telegram

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int mm(void);

int main(void)
{
    // Mighty Method
    printf("%lld\n", mm());
    return 0;
}


long long int mm(void)
{
    char num[2000] = {};
    scanf("%s", num);
    
    unsigned long len = strlen(num);
    
    long long int sum = 0;
    for (int i = 0; i < len; ++i) {
        sum += num[i]-'0';
    }
    //printf("%lld\n", sum);
    if (sum < 10) return sum;
    if (sum == 10) return 1;
    
    
    
    long long int n = sum;
    long long int k, i, m, *arr = NULL;
    
    for (m = 0, k = n; k != 0; m++) k /= 10;

    arr = (long long int *)calloc(10*m+1, sizeof(int));
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

    arr = (long long int *)realloc(arr, (10* m+1 * sizeof(int))+1);
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
    free(arr);
    arr = NULL;
    //printf("%lld\n", n);
    
    return n;
    
}
