//
// Created by Hello on 2021/9/1.
//

#include <stdio.h>

#define WORDNUM 20
#define WORDLEN 20
#define IN 1
#define OUT 0

int main(void)
{
    int c, status, num;
    int words[WORDNUM];

    status = IN;
    num = 0;
    for (int i = 0; i < WORDNUM; ++i) {
        words[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\b') {
            status = OUT;
        } else {
            if (status == OUT) {
                ++num;
            }
            ++words[num];
            status = IN;
        }
    }

    /*(x,y) -> (x,y')*/
    int x[WORDNUM];
    for (int i = 0; i < WORDNUM; ++i)
        x[i] = 0;
    for (int col = 0; col < WORDNUM; ++col) {
        x[col] = WORDLEN - words[col];
    }

    /*paint*/
    printf("\t  ^\n");
    printf("\t  |\n");

    for (int row = 0; row < WORDLEN; ++row) {
        printf("\t%2d|", WORDLEN - row);
        for (int col = 0; col < WORDNUM; ++col) {
            if (x[col] <= row) {
                printf(" *");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\t 0|");
    for (int col = 0; col < WORDNUM; ++col)
        printf(" -");
    printf(">\n");
}