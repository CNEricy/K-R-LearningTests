//
// Created by Hello on 2021/9/20.
//

/**
 * 主要思路:
 * 1.用变量last记录前一个值,当遇到'-'时需要先判断是否是字符串后缀'-'
 * 2.若是,记录到数组中,否则判断是否是前导或尾随的'-'(只需打印,不需要其他处理,则合并两种情况)
 * 3.遇到非'-'字符时都复制到新的数组里,遇到时再根据判断是复制'-'再复制last和s2[i+1]中间字符串(双开)即可
 */

#include <stdio.h>

void expand(char s1[], char s2[]);

int main(void)
{
    char s2[] = "-a-x-A-Y-Z-0-0-9-";
    char s1[1000];
    expand(s1, s2);
    printf("%s\n", s1);
}

void expand(char s1[], char s2[])
{
    int i, j;
    char last;

    i = j = 0;
    last = '\0';

    while (s2[i] != '\0') {
        if (s2[i] == '-' && s2[i + 1] != '\0') { //判断是否是字符串后缀'-';是否是前导或尾随的'-'在嵌套的if-else里判断
            if ((last >= '0' && last <= '9') && (s2[i + 1] >= '0' && s2[i + 1] <= '9')) {
                for (char c = last + 1; c < s2[i + 1]; ++c) {
                    s1[j++] = c;
                }
            } else if ((last >= 'A' && last <= 'Z') && (s2[i + 1] >= 'A' && s2[i + 1] <= 'Z')) {
                for (char c = last + 1; c < s2[i + 1]; ++c) {
                    s1[j++] = c;
                }
            } else if ((last >= 'a' && last <= 'z') && (s2[i + 1] >= 'a' && s2[i + 1] <= 'z')) {
                for (char c = last + 1; c < s2[i + 1]; ++c) {
                    s1[j++] = c;
                }
            } else s1[j++] = last = s2[i];  //前后不一致,则为前导或尾随的'-'
        } else s1[j++] = last = s2[i];

        ++i;
    }

    s1[j] = '\0';
}