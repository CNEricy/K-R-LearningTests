//
// Created by Hello on 2021/8/31.
//
#include <stdio.h>

#define IN 1
#define OUT 0

int main(void)
{
    int c;
    int status = IN;
    while ((c = getchar()) != EOF) {
        if (c == '\b' || c == '\n' || c == '\t' || c == ' ') {
            if (status == IN) putchar('\n');
            status = OUT;
        } else {
            putchar(c);
            status = IN;
        }
    }
}