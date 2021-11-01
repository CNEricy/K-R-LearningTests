/**
 * 主要思路:
 * 方法一.最方便:原printd()不能处理最大负数是因为有符号int最大值为2147483647,因此当取值为INT_MIN时,在n=-n这步会产生溢出,此时只需将int赋值给占更大字节数的long long即可
 * 方法二.不考虑改变类型:当值为INT_MIN时,可以借1,再转变成INT_MAX,在依次打印时,当检测到status=1(n的原值为INT_MIN)且此时n=INT_MAX时,再将1还回来即可
 *  1)判断需要两个条件是因为:
 *      1.1)status==1是用来判断原值是否是INT_MIN
 *      1.2)n==INT_MAX是用来判断当前值是否是需要打印最后一位,若不加此判断,则每一位都会加1
 */


#include <stdio.h>
#include <stdlib.h>

void printd1(long long n);

void printd2(int n);

int main()
{
    printd1(INT_MIN + 1);
    printf("\n");
    printd1(INT_MIN);
    printf("\n");
    printd1(INT_MAX);
    printf("\n");

    //===========================//
    printd2(INT_MIN + 1);
    printf("\n");
    printd2(INT_MIN);
    printf("\n");
    printd2(INT_MAX);
    printf("\n");
}

void printd1(long long n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n / 10)
        printd1(n / 10);
    putchar(n % 10 + '0');
}

int status = 0;

void printd2(int n)
{
    if (n < 0) {
        putchar('-');
        if (n == INT_MIN) {
            status = 1;
            n = INT_MIN + 1;
        }
        n = -n;
    }
    if (n / 10)
        printd2(n / 10);
    if (status == 1 && n == INT_MAX)
        putchar(n % 10 + 1 + '0');
    else
        putchar(n % 10 + '0');
}