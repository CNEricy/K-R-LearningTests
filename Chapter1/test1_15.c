//
// Created by Hello on 2021/9/3.
//

#include <stdio.h>

float fToC(float fahr);

int main(void)
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        celsius = fToC(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    }
}

float fToC(float fahr)
{
    return (5.0 / 9.0) * (fahr - 32.0);
}