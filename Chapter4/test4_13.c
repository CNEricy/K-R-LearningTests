#include <stdio.h>

void reverse(char []);

int main()
{
    reverse("abcdefg");
}

void reverse(char s[])
{
    if (*s == '\0')
        return;
    reverse(s+1);
    putchar(*s);
}