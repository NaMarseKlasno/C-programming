#include <stdio.h>
#include <stdlib.h>
struct lip
{
    long double distance;
    long double velocity;
    struct lip *next;
};
void scan(struct lip *lip, int max)
{
    for (int i = 0; i < max; i++)
    {
        scanf("%Le %Le", &lip->distance, &lip->velocity);
        if (i < max - 1)
        {
            lip->next = (struct lip *)malloc(sizeof(struct lip));
            lip = lip->next;
        }
    }
}
void freee(struct lip *l, long double size, int i)
{
    if (i < size - 1)
    { 
        freee(l->next,size,i+=1);
    }
    free(l);
}
long double result(struct lip *lip, long double hoal, long double left, long double right, int lim, int iteration, long double size)
{
    long double sample = (left + right) / 2;
    long double cas = 0;
    struct lip *l = lip;
    int i = 0;
    while (1)
    {
        if ((l->velocity + sample) <= 0.0)
            return result(lip, hoal, sample, right, lim, iteration += 1,size);
        cas += (l->distance / (l->velocity + sample));
        if (i >= size -1)
            break;
        l = l->next;
        i++;
    }
    if (iteration >= lim)
        return sample;
    if (cas < hoal)
        return result(lip, hoal, left, sample, lim, iteration += 1,size);
    else
        return result(lip, hoal, sample, right, lim, iteration += 1,size);
}
int main()
{

    long double s, res = 0;
    scanf("%Le %Le", &s, &res);
    struct lip *lip = (struct lip *)malloc(sizeof(struct lip));
    // lip->distance = 0;
    // lip->velocity = 0;
    // lip->next = NULL;
    scan(lip, s);
    long double vl = result(lip, res, -10000, 10000, 200, 0,s);
    freee(lip,s,0);
    printf("%.6Lf", vl);
    return 0;
}
