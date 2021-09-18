//
// Created by Hello on 2021/9/12.
//

/**
 * 主要思路:
 * 首先有个问题:就是从终端获取输入时,tab只算一个字符,但是如果多行对齐来看,tab占据的列宽度其实是它补足的空白宽度,
 *            所以可以参考test1_20detab程序,将其中的tab都转成空格,以空格来计数
 * solution1将n列中第一个非空格符前的空格也都打印了出来
 * 如果需要将列中的所有空格都去掉,请参考solution2
 */

#include <stdio.h>

#define TABSPACE 8
#define SPLITLEN 10

void solution1(void);

void solution2(void);

int main(void)
{
    solution2();
}

void solution1(void)
{
    int c, space, nc, len;

    nc = 0;
    len = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len == SPLITLEN) {
            printf("\n");
            len = 0;
        }
        if (c != '\t') {
            putchar(c);
            ++nc;
            ++len;
        } else {
            space = nc % TABSPACE;
            for (int i = 0; i < TABSPACE - space; ++i) {
                putchar(' ');
                ++len;
            }
            nc = 0;
        }
    }
}

void solution2(void)
{
    int c, space, nc, len;

    nc = 0;
    len = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (len == SPLITLEN) {
            printf("\n");
            len = 0;
        }
        if (c != '\t') {
            if (c != ' ') putchar(c);
            ++nc;
            ++len;
        } else {
            space = nc % TABSPACE;
            for (int i = 0; i < TABSPACE - space; ++i) {
//                putchar(' ');
                ++len;
            }
            nc = 0;
        }
    }

}