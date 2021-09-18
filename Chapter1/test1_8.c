//
// Created by Hello on 2021/8/28.
//

#include <stdio.h>

int main()
{
    int c, ns, nt, nl;
    ns = nt = nl = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') ++ns;
        if (c == '\t') ++nt;
        if (c == '\n') ++nl;
        putchar(c);
    }

    printf("%d, %d, %d\n", ns, nt, nl);
    return 0;
}