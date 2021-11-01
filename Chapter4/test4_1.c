//
// Created by Hello on 2021/9/21.
//

/**
 * 主要思路:
 * 只有该行中还有匹配上的,就更新记录最右值的变量
 */

#include <stdio.h>
#define MAXLINE 1000

int getline(char s[], int lim);

int strindex(char s[], char t[]);

char pattern[] = "ould";

int main(void)
{
    char line[MAXLINE];

    while (getline(line, MAXLINE) > 0) {
        printf("%d\n", strindex(line, pattern));
    }
}

int getline(char s[], int lim)
{
    int i, c;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n') s[i++] = c;

    if (c == '\n') s[i++] = c;

    s[i] = '\0';

    return i;
}

int strindex(char s[], char t[])
{
    int i, j, k, right;
    right = -1;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k);

        if (k > 0 && t[k] == '\0')
            right = i;  //记录的是最右边出现的起始的位置,因此,应该用i赋值
    }

    return right;
}