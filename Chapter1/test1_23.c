//
// Created by Hello on 2021/9/11.
//

/**
 * 1.该程序不适用于#define定义变量时使用了注释符的情况, 例如#define COMMENT //
 * 2.该程序默认C语言程序中的语法正确即可正确编译,不存在一行只有左引号;单引号中存字符串等情况
 * 主要思路:
 * 1.只有在非注释中才需要去找注释符,注释中需要去找结束注释的符号
 * 2.非注释时,只有不在字符串中才需要去找注释符,通过保存的上一个字符和本次字符组合比较是否满足注释符号;
 *   字符串中需要去找下一个"(注意:要排除转义序列的情况);
 *   单引号中只能有一个字符,因此无需判断单引号
 * 3.通过打印上一个字符而不是打印本次字符的方式是因为很容易通过当前字符知道上一个字符是否需要打印;
 *   而很难通过下一个字符判断当前字符需要打印
 */

#include <stdio.h>

#define IN 1 //in string
#define OUT 0 //outside string

#define ISNC 1  //not in comment
#define ISSLC 2  //single line comment
#define ISMLC 3 //multiline comment


int main(void)
{
    int c, status, commentStatus;
    int lChar; //记录上一个字符

    status = OUT;
    commentStatus = ISNC;
    lChar = '\0';

    while ((c = getchar()) != EOF) {
        if (commentStatus == ISNC) {
            if (status == OUT) {
                if (c == '/' && lChar == '/') commentStatus = ISSLC; //开启//注释
                else if (c == '*' && lChar == '/') commentStatus = ISMLC; //开启/**/注释
                else {
                    putchar(lChar);
                    if (c == '"') status = IN;
                }
            } else {
                putchar(lChar);
                if (c == '"' && lChar != '\\') status = OUT;
            }
        } else if (commentStatus == ISSLC) { // '//'注释中,等待'\n'
            if (c == '\n') {
                commentStatus = ISNC;
                c = '\0';  //去掉行注释末尾的'\n'
            }
        } else { // '/**/'注释中,等待'*/'
            if (c == '/' && lChar == '*') {
                commentStatus = ISNC;
                c = '\0'; //去掉多行注释末尾的'/'
            }
        }

        lChar = c;
    }

    putchar(lChar);

}
