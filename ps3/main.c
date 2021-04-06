#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(void)
{
char *p;
p = (char *) malloc(17);
if(!p) {
printf("Allocation error.");
exit (1);
}
strcpy(p, "This is 16 chars");
p = (char *) realloc (p,18);
if(!p) {
printf("Allocation error.");
exit (1);
}
strcat (p, ".");
printf(p);
free(p);
return 0;
}