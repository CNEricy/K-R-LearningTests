//
// Created by Hello on 2021/8/27.
//

#include <stdio.h>

int main()
{
    int c;
    for (int i = 0; i < 5; i++) {
        printf("%d\n", getchar() != EOF); //注意' ', '\n'也是一个非EOF字符,占用一轮循环,但是当这些字符跟在以ctrl+z(windows)表示的结束符后,不会进入
    }

    return 0;
}