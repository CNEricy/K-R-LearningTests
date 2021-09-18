//
// Created by Hello on 2021/9/7.
//

#include <stdio.h>

#define MAXLINE 1000

int getline(char s[], int lim);

void reverse(char before[], int len);

int main(void)
{
    int len;
    char ch[MAXLINE];

    while ((len = getline(ch, MAXLINE)) > 0) {
        reverse(ch, len);
        printf("%s\n", ch);
    }
}

int getline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = '\n';
        ++i;
    }

    s[i] = '\0';

    return i;
}

void reverse(char before[], int len)
{
    for (int i = 0; i < len / 2; ++i) {
        char t = before[i];
        before[i] = before[len - i - 1];
        before[len - i - 1] = t;
    }
}