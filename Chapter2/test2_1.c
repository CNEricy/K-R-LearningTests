//
// Created by Hello on 2021/9/12.
//

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void)
{
    //signed
    printf("maximum value of signed char: %d\n", CHAR_MAX);
    printf("minimum value of signed char: %d\n", CHAR_MIN);

    printf("maximum value of signed short: %d\n", SHRT_MAX);
    printf("minimum value of signed short: %d\n", SHRT_MIN);

    printf("maximum value of signed int: %d\n", INT_MAX);
    printf("minimum value of signed int: %d\n", INT_MIN);

    printf("maximum value of signed long: %ld\n", LONG_MAX);
    printf("minimum value of signed long: %ld\n", LONG_MIN);

    //unsigned
    printf("maximum value of unsigned char: %u\n", UCHAR_MAX);

    printf("maximum value of unsigned short: %u\n", USHRT_MAX);

    printf("maximum value of unsigned int: %u\n", UINT_MAX);

    printf("maximum value of unsigned long: %lu\n", ULONG_MAX);


    printf("-------------------------------------\n");

    //signed
    printf("maximum value of signed char: %d\n", (1 << (8 * sizeof(char)- 1)) - 1);
    printf("minimum value of signed char: %d\n", -(1 << (8 * sizeof(char) - 1)));

    printf("maximum value of signed short: %d\n", (1 << (8 * sizeof(short) - 1)) - 1);
    printf("minimum value of signed short: %d\n", -(1 << (8 * sizeof(short) - 1)));

    printf("maximum value of signed int: %d\n", (1u << (8 * sizeof(int)- 1)) - 1);
    printf("minimum value of signed int: %d\n", -(1u << (8 * sizeof(int) - 1)));

    printf("maximum value of signed long: %d\n", (1u << (8 * sizeof(long) - 1)) - 1);
    printf("minimum value of signed long: %d\n", -(1u << (8 * sizeof(long) - 1)));

    //unsigned
    printf("maximum value of unsigned char: %u\n", (1u << 8 * sizeof(char)) - 1);

    printf("maximum value of unsigned short: %u\n",  (1u << 8 * sizeof(short)) - 1);

    printf("maximum value of unsigned int: %lld\n",  (1ll << 8 * sizeof(int)) - 1);

    printf("maximum value of unsigned long: %lld\n",  (1ll << 8 * sizeof(long)) - 1);

}