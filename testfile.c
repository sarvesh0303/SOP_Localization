#include <stdio.h>

main() {
    int d = 8;
    int* x = &d;
    int* y = x;
    printf("%d %d %d\n",*x,*y,d);
    *y = 12;
    printf("%d %d %d\n",*x,*y,d);
}