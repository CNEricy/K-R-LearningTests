//
// Created by Hello on 2021/8/31.
//

#include <stdio.h>

int main(void)
{
    int c;
    int ns = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            putchar(c);
            ns = 0;
        } else if (ns == 0) {
            putchar(c);
            ++ns;
        }
    }
}