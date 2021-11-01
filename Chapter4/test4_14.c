#include <stdio.h>

#define swap(t, x, y)  { \
    t n = x;                 \
    x = y;                   \
    y = n;                   \
}


int main()
{
    int a = 1, b = 2;
    printf("before:\ta=%d,\tb=%d\n", a, b);
    swap(int, a, b);
    printf("after:\ta=%d,\tb=%d\n", a, b);
}