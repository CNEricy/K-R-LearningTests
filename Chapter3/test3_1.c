//
// Created by Hello on 2021/9/16.
//
/**
 * 主要思路:
 * 由于原循环内部执行了两次测试,现要求一次,则考虑将大于等于查询值的情况设为默认情况,此时只有一次测试;
 * 由于将大于和等于查询值的情况合并,那么当已经找到查询值位置的时候仍会进行循环,因此该版本的运行时间会大于等于原版
 */

#include <stdio.h>

int binsearch(int x, int v[], int n);

int main()
{
    int arr[] = {1,2,3,4,5,6,7};
    printf("%d\n", binsearch(8, arr, 7));
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;

    while (low < high) {
        mid = (high-low)/2 + low;

        if (v[mid] < x) low = mid + 1;
        else high = mid;
    }

    if (low == high && v[low] == x) return low;

    return -1;
}