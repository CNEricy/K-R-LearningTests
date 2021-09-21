//
// Created by Hello on 2021/9/20.
//

/**
 * 原因:正数最大值为2^(m-1)-1,因此当原函数中的n为-2^(m-1)时,n = -n这步会发生溢出,仍是-2^(m-1),第一位仍是'-'
 *
 * 主要思路:
 * 思路一:当n为INT_MIN时,可以将n+1,这是取正不会溢出,最后再将1加上即可. 由于INT_MIN一定为整数,因此无需考虑近1的情况
 * 思路二:由于溢出是因为int类型的位数不够,因此可以将n赋值给更大长度的类型,比如long long
 *
 * 疑问:在以n == INT_MIN之前,我是以n-1>0未测试条件的,原本想的是n的值为-2147483648时,n-1的值为2147483647,
 *      但是始终没有进入正确的语句块中,我做了以下测试:
 *      printf("%d", n-1 > 0); output:0
 *      printf("%d %d",n-1,n); output: 2147483647,-2147483648
 *      printf("%d", n-1 == 2147483647); output:0
 *      printf("%d", n == INT_MIN); output:1
 *      printf("%d", n-1 = INT_MAX); output:0
 *
 *      遗留问题,待后续有能力再解答!!!!!!wcnmd
 */

#include <stdio.h>
#include <limits.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main(void)
{
    int n = -2147483648;
    char s[11];
    itoa(n, s);
    printf("%s\n", s);
}

void itoa(int n, char s[])
{
    int i, sign;
    int overflow;

    overflow = 0;

    if ((sign = n) < 0) {
        if (n == INT_MIN) {
            n = -(n + 1);
            overflow = 1;
        } else n = -n;

    }
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while (n /= 10);

    if (sign < 0) s[i++] = '-';
    if (overflow) s[0] = s[0] + 1;

    reverse(s);
    s[i] = '\0';
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