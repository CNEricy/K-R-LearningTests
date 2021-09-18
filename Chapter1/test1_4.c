//
// Created by Hello on 2021/8/27.
//

#include <stdio.h>

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 30;

    printf("Celsius-Fahrenheit\n\n");
    celsius = lower;
    while (celsius <= upper) {
        fahr = celsius / 9.0 * 5.0 + 32;
        printf("%3.0f %6.2f\n", celsius, fahr);
        celsius += step;
    }
    return 0;
}