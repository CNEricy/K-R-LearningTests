//
// Created by Hello on 2021/8/31.
//

#include <stdio.h>

#define WORDNUM 20
#define IN 1
#define OUT 0

int main(void)
{
    int c, status, num;
    int wordLen[WORDNUM]; //记录单词长度

    status = IN;
    num = 0;
    for (int i = 0; i < WORDNUM; i++) {
        wordLen[i] = 0;
    }

    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == '\t' || c == '\b' || c == ' ')
            status = OUT;
        else {
            if (status == OUT) ++num;
            ++wordLen[num];
            status = IN;
        }
    }

    printf("\t^\n");
    printf("\t|\n");
    for (int i = 0; i <= num; i++) {
        printf("\t|");
        for (int j = 0; j < wordLen[i]; j++)
            printf(" *");
        printf(" (%d)\n", wordLen[i]);
    }
    printf("\t");
    for (int i = 0; i < WORDNUM; i++)
        printf(" --");
    printf(">\n");
}