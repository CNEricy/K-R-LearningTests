//
// Created by Hello on 2021/9/21.
//

/**
 * 主要思路:
 * 从后往前获取转换后的b进制字符串,然后再倒转下即可
 *
 * 注意:该函数只能用字母表示到35进制,最小为2进制
 */

#include <stdio.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(void)
{
    int n = 177;
    char s[4];
    itob(n, s, 35);
    printf("%s\n", s);
}

void itob(int n, char s[], int b)
{
    if (b < 2) return; //b不能小于2

    int i;

    i = 0;
    while (n) {
        int t = n % b;
        if (t > 9) s[i++] = t-10+'a';
        else s[i++] = t + '0';
        n /= b;
    }
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