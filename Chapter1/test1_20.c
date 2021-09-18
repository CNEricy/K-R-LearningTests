//
// Created by Hello on 2021/9/8.
//

/**
 * 主要思路:
 * 了解tab的工作:用空白符补足n = 8-字符数%8
 */

#include <stdio.h>

#define TABSPACE 8

int main(void)
{
    //Q1
    int c, space, nc;

    nc = 0;
    while ((c = getchar()) != EOF) {
        if (c != '\t') {
            ++nc;
            putchar(c);
        } else {
            space = nc % TABSPACE;
            for (int i = 0; i < TABSPACE-space; ++i)
                putchar(' ');
            nc = 0;
        }
    }

    //Q2  符号常量(symbolic parameter)

}
