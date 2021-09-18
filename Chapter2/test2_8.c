//
// Created by Hello on 2021/9/14.
//

#include <stdio.h>

unsigned int rightrot(unsigned int x, int n);
unsigned int setbits(unsigned int x, int p, int n, unsigned int y);
unsigned int getbits(unsigned int x, int p, int n);

int main(void)
{
    unsigned a = 0b01001101;

    printf("%x", rightrot(a, 7));
}

unsigned int rightrot(unsigned int x, int n)
{
    unsigned int t = getbits(x, n-1, n);

    return setbits(x >> n, 31, n, t);

    /*return setbits(x >> n, 30, n, t); //适用于算术移位的signed int x */
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    unsigned int t = getbits(x, p-n, p+1-n); //存储最后的p+1-n位的值
    unsigned int yn = getbits(y, n - 1, n); //获取y右边n位的值

    return x & (~0 << (p+1)) | yn << (p + 1 - n) | t; //先将x的右边p+1位变成0再用或运算赋值
}

unsigned int getbits(unsigned int x, int p, int n)
{
    return (x >> (p + 1 - n) & ~(~0 << n));
}