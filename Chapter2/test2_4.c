//
// Created by Hello on 2021/9/14.
//

#include <stdio.h>

#define MATCHED 1
#define UNMATCHED 0

void squeeze(char s1[], char s2[]);

int main(void)
{
    char s1[] = "hello";
    char s2[] = "world";
    squeeze(s1, s2);
    printf("%s", s1);
}

void squeeze(char s1[], char s2[])
{
    int m, n;

    for (m = n = 0; s1[m] != '\0'; ++m) {
        int j, status;
        status = UNMATCHED;

        for (j = 0; s2[j] != '\0'; ++j)
            if (s1[m] == s2[j]) {
                status = MATCHED;
                break;
            }

        if (status == UNMATCHED) s1[n++] = s1[m];
    }
    s1[n] = '\0';
}