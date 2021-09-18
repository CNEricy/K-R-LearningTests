//
// Created by Hello on 2021/9/14.
//

#include <stdio.h>

/**
 * 答:x-1后,x的二进制表示中最右边原本值为1的二进制位变成0,且其后(若有)的每个二进制位也与原值互为0,1;0&1=0
 *   缩写:(2的n次)&(2的n次-1)=0
 * 主要思路:
 * 对x使用该表达式知道x=0,使用次数即x的二进制表示中1的个数
 */

int bitcount(unsigned int x);

int main(void)
{
    unsigned int x = 8;
    printf("%d", bitcount(x));
}

int bitcount(unsigned int x)
{
    int i = 0;
    while (x) {
        x &= (x-1);
        ++i;
    }

    return i;
}