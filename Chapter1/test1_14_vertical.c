//
// Created by Hello on 2021/9/2.
//

#include <stdio.h>

#define NUM 128

int main(void)
{
    int c, cn, max;
    int chLen[NUM];
    int ch[NUM];
    int newChLen[NUM];

    cn = 0;
    for (int i = 0; i < NUM; ++i) {
        chLen[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        ++chLen[c - 0];
    }

    max = 0;
    for (int i = 0; i < NUM; ++i) {
        if (chLen[i] > 0) {
            if (chLen[i] > max) {
                max = chLen[i];
            }
            newChLen[cn] = chLen[i];
            ch[cn] = i;
            ++cn;
        }
    }

    printf("\t  ^\n");
    printf("\t%2d|\n", max + 1);

    for (int row = 0; row < max; ++row) {
        printf("\t%2d|", max - row);
        for (int col = 0; col < cn; ++col) {
            if (newChLen[col] + row >= max) {
                printf(" *");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }

    printf("\t 0|");
    for (int i = 0; i < 2 * cn; ++i)
        printf(" -");
    printf(">\n");
    printf("\t  |");
    for (int i = 0; i < cn; ++i) {
        if (ch[i] == '\n') {
            printf("\\n");
        } else if (ch[i] == '\t') {
            printf("\\t");
        } else if (ch[i] == '\b') {
            printf("\\b");
        } else if (ch[i] == '\\') printf("\\\\");
        else { printf(" %c", ch[i]); }
    }
}