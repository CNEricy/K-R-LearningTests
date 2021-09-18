//
// Created by Hello on 2021/9/7.
//

#include <stdio.h>

#define MAXLINE 10

int getline(char s[], int lim);

int main(void)
{
    int len;
    char ch[MAXLINE];

    while ((len = getline(ch, MAXLINE)) > 0) {
        printf("%s\n", ch);
    }
}

int getline(char s[], int lim)
{
    int c, i;
    int allSpace = 1; //假设全为空格
    for (i = 0; ; ++i)
    {
        if (i == lim - 1 ||  (c = getchar()) == EOF) { //当数量超过最大值-1或到达EOF,需要判断之前存储的是否都为' ',若是,则重新获取输入,否则,退出循环
            if (allSpace == 1) i = -1;
            else break;
        }
        if (c == '\n') //c为换行符时非全空格,直接退出循环
            break;
        s[i] = c;
        if (c != ' ') allSpace = 0;
    }
    if (c == '\n') {
        s[++i] = c;
        ++i;
    }

    s[i] = '\0';

    /*删除行末尾的空格及制表符知道遇到其他字符*/
    for (int j = i - 1; j >= 0; --j) { //i为'\0',不计算在输入行内
        if (s[i] == ' ' || s[i] == '\t')
            s[i] = '\0';
        else
            break;
    }
    return i;
}