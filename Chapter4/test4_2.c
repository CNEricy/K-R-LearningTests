//
// Created by Hello on 2021/9/21.
//

/**
 * 主要思路:
 * 在书本原atof的基础上加上对e指数的判断并适当扩大倍数或减小倍数
 */

#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main(void)
{
    char s[] = "123.45e-6";
    printf("%g\n", atof(s));
}

double atof(char s[])
{
    int i, sign, eSign; //sign和eSign分别记录数值的符号和科学计数法的符号
    double val, power, ePower; //power和ePower分别记录数据处理时的倍率和科学计数法中的倍率

    i = 0;
    while (isspace(s[i])) ++i; //去除空格

    sign = s[i] == '-' ? -1 : 1; //判定正负
    if (s[i] == '-' || s[i] == '+') ++i; //符号位则前进一位

    val = 0.0;
    while (isdigit(s[i])) val = 10 * val + s[i++] - '0'; // x *= y + 1 => x = x * (y + 1)
    if (s[i] == '.') ++i;

    power = 1.0;
    while (isdigit(s[i])) {
        power *= 10;
        val = 10 * val + s[i++] - '0';
    }

    if (s[i] == 'e' || s[i] == 'E') ++i;
    eSign = s[i] == '-' ? -1 : 1;
    ++i;

    ePower = 0.0;
    while (isdigit(s[i])) ePower = 10 * ePower + s[i++] - '0';

    for (int j = 0; j < ePower; ++j) { //math.h中pow(x,y)函数,但是atof函数重复声明了
        power = eSign == -1 ? power * 10 : power / 10;  //用乘除而不是加减是因为power和ePower是结果,而不是指数
    }

    return sign * val / power;
}