#include <stdio.h>
#include <ctype.h>

char arr[30];
int getline(char s[], int length);

int main()
{
    int len;
    while ((len = getline(arr, 30)) > 0)
        printf("%s", arr);
}

int getline(char s[], int length)
{
    int i, c;

    i = 0;
    while (i < length - 1 && (c = getchar()) != EOF && c != '\n') {
        printf("%c ", c);
        s[i++] = c;
    }

    if (c == '\n') {
        s[i++] = c;
    } else if (i >= 0) {  //有输入时getline()一定以'\n'结尾,保证getop()中判断操作对象的类型时不会越界(lp<=len-1)
        s[i++] = '\n';
    }

    s[i] = '\0';
    return i;
}