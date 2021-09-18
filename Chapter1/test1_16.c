//
// Created by Hello on 2021/9/5.
//

#include <stdio.h>

#define MAXLINE 10

int getline(char line[], int length);

int main(void)
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0) {
        /*只有当line为char类型的数组时,才会去打印字符串;当line为其他类型数组时,只打印数组第一位元素*/
        printf("%s\n", line);
    }

    return 0;
}


/*由于getline有防溢出功能,当获得行输入超过MAXLINE时,第一行line的数组末尾加入'\0'
 * 后面未计算到该行的仍然在字符流中,会被记录到下一行
 * 因此,如果main函数的while循环中的printf如果不加入换行符,会发现输入多少字符就输出多少字符,
 *
 * 另外一种情况:当不加入getline中的line[i] = '\0'时
 * 发现即使输入字符超过MAXLINE,程序也会自动在line数组MAXLINE-1的地方加入'\0',每行最多只输出MAXLINE-1个元素,以此类推,直到有一行不满足MAXLINE-1个元素
 * 此时,会发现程序再输出完最后一行后,仍然会有其他不应该的输出
 * 因此,为保证程序正确性,line[i]='\0'不能省略
 * */
int getline(char line[], int length)
{
    int c, i;
    for (i = 0; i < length - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
        printf("%d: ", i);
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';

    return i; //'\0'不算在行长度内
}
