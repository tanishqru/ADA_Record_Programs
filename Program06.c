//Design and implement C/C++ Program to solve 0/1 Knapsack problem using
//Dynamic Programming method.

#include <stdio.h>

int w[10], p[10], n;

int max(int a, int b)
{
    return a > b ? a : b;
}

int knap(int i, int m)
{
    if (i == n)
        return w[i] > m ? 0 : p[i];
    if (w[i] > m)
        return knap(i + 1, m);
    return max(knap(i + 1, m), knap(i + 1, m - w[i]) + p[i]);
}

int main()
{
    int m, i, max_profit;
    printf("\nEnter the number of objects : ");
    scanf("%d", &n);
    printf("Enter the knapsack capacity : ");
    scanf("%d", &m);
    printf("\nEnter profit followed by weight : \n");
    for (i = 1; i <= n; i++)
        scanf("%d %d", &p[i], &w[i]);
    max_profit = knap(1, m);
    printf("\nMax profit = %d\n", max_profit);
    return 0;
}