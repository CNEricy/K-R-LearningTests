//
// Created by Hello on 2021/9/21.
//

#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main(void)
{
    int n = -2147483648;
    char s[12];
    itoa(n, s, 15);
    printf("%s\n", s);
}

void itoa(int n, char s[], int w)
{
    int i, sign, overflow;

    overflow = 0;
    if ((sign = n) < 0) {
        if (n == INT_MIN)
        {
            n += 1;
            overflow = 1;
        }
        n = -n;
    }

    i = 0;
    while (n) {
        s[i++] = n % 10 + '0';
        n /= 10;
    }

    if (sign < 0) s[i++] = '-';
    if (overflow) s[0] += 1;

    while (i < w) s[i++] = ' ';

    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int len;
    for (len = 0; s[len] != '\0'; ++len) ;

    for (int i = 0; i < len / 2; ++i) {
        char t = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = t;
    }
}