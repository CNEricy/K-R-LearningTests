//
// Created by Hello on 2021/9/5.
//

#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int length);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 80) {
            printf("%s\n", line);
        }
    }

    return 0;
}


int getline(char line[], int length)
{
    int c, i;
    for (i = 0; i < length - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
        printf("%d: ", i);
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';

    return i;
}
