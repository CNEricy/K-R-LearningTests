//
// Created by Hello on 2021/8/26.
//

#include <stdio.h>

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("Fahrenheit-Celsius\n\n");

    fahr = lower;
    while (fahr <= upper) {
        celsius = (5.0 / 9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius); //字符宽.小数位 字符宽从右往左排,包含小数点以及小数位,%.0f强制不打印小数点和小数部分
        fahr += step;
    }
}