//
// Created by Hello on 2021/9/14.
//

#include <stdio.h>

int any(char s1[], char s2[]);

int main(void)
{
    char s1[] = "hello";
    char s2[] = "world";
    printf("%d", any(s2, s1));
}

int any(char s1[], char s2[])
{
    int i;

    for (i = 0; s1[i] != '\0'; ++i) {
        int j;

        for (j = 0; s2[j] != '\0'; ++j) {
            if (s2[j] == s1[i]) return i;
        }
    }

    return -1;
}