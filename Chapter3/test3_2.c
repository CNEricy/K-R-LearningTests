//
// Created by Hello on 2021/9/20.
//

/**
 * 主要思路:
 * escape: 检测到'\t','\n'时,需要两个字符存储转义序列
 * nonEscape: 先将每个字符复制到目标数组,同时用变量last记录上一个值,当前一个与当前满足'\t'或'\n'时,将目标数组中的前一个字符替换(前一个字符必是'\\'),因此无需考虑--j越界情况
 */

#include <stdio.h>

void escape(char s[], char t[]);

void nonEscape(char s[], char t[]);

int main(void)
{
    char t[] = "adfbfad\nfadfds\tbfasdf\tbfdsa\n";
    char s[30];
    char t1[30];
    escape(s, t);
    printf("%s\n", s);
    nonEscape(t1, s);
    printf("%s\n", t1);
}

void escape(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (t[i] != '\0') {
        switch (t[i]) {
            case '\n':
                s[j++] = '\\';
                s[j++] = 'n';
                break;
            case '\t':
                s[j++] = '\\';
                s[j++] = 't';
                break;
            default:
                s[j++] = t[i];
        }
        ++i;
    }
    s[j] = '\0';
}

void nonEscape(char s[], char t[])
{
    int i, j;
    char last;

    i = j = 0;
    last = '\0';

    while (t[i] != '\0') {
        switch (t[i]) {
            case 't':
                switch (last) {
                    case '\\':
                        s[--j] = '\t';
                        break;
                    default:
                        s[j] = t[i];
                        break;
                }
                break;
            case 'n':
                switch (last) {
                    case '\\':
                        s[--j] = '\n';
                        break;
                    default:
                        s[j] = t[i];
                        break;
                }
                break;
            default: s[j] = t[i];
        }
        last = t[i];
        ++i;
        ++j;
    }
}