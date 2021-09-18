//
// Created by Hello on 2021/9/12.
//

#include <stdio.h>

int LIM = 4

int main(void)
{
    int c, i;
    char ch[LIM];
    for (i = 0; i < LIM-1; ++i) {
        if ((c = getchar()) != EOF) {
            if (c != '\n') ch[i] = c;
        }
    }
}