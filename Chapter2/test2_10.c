//
// Created by Hello on 2021/9/14.
//

#include <stdio.h>

int lower(int c);

int main(void)
{
    printf("%c", lower('A'));
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : c;
}