//
// Created by Hello on 2021/9/2.
//

#include <stdio.h>

#define NUM 128

int main(void)
{
    int c, cn;
    int chLen[NUM]; //存所有字符长度
    int ch[NUM]; //存参与计数的字符
    int newChLen[NUM]; //存参与计数的字符的出现次数

    cn = 0;
    for (int i = 0; i < NUM; ++i) //数组初始化,否则未初始的随机值会影响后面的重新排列结果
        chLen[i] = 0;

    while ((c = getchar()) != EOF) {
        ++chLen[c - 0];
    }

    //去除未出现的字符,重新排列
    for (int i = 0; i < NUM; ++i) {
        if (chLen[i] > 0) {
            newChLen[cn] = chLen[i];
            ch[cn] = i;
            ++cn;
        }
    }

    printf("\t  ^\n");
    printf("\t  |\n");
    for (int i = 0; i < cn; ++i) {
        //转义字符特殊处理(暂未处理全部转义字符)
        if (ch[i] == '\n') { printf("\t\\n|"); }
        else if (ch[i] == '\t') { printf("\t\\t|"); }
        else if (ch[i] == '\b') { printf("\t\\b|"); }
        else {
            printf("\t%2c|", ch[i]);
        }
        for (int j = 0; j < newChLen[i]; ++j)
            printf(" *");
        printf(" %d\n", newChLen[i]);
    }

    printf("\t  |");
    for (int i = 0; i < NUM / 2; ++i)
        printf(" -");
    printf(">");
}