//
// Created by Hello on 2021/9/14.
//

#include <stdio.h>
#include <string.h>

long long htoi(char s[]);

int main(void)
{
    char c[] = "0x1111";
    printf("%lld", htoi(c));
}

long long htoi(char s[])
{
    int i, len;
    long long sum;

    len = strlen(s);
    sum = 0;
    if (len < 2) return 0;

    for (i = 2; i < len; ++i) {
        int t = 0;
        if (s[i] >= '0' && s[i] <= '9') {
            t = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            t = s[i] - 'a' + 10;
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            t = s[i] - 'A' + 10;
        }
        sum = 16 * sum + t;
    }

    return sum;
}