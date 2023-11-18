#include <stdio.h>
#include <time.h>

int fib_iterative(int n)
{
    if (n <= 1)
    {
        return n;
    }

    int prev = 0, current = 1, temp;
    for (int i = 2; i <= n; ++i)
    {
        temp = current;
        current = prev + current;
        prev = temp;
    }

    return current;
}

int fib_recursive(int n)
{
    if (n <= 1)
    {
        return n;
    }

    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

int main()
{
    int i;

    while (scanf("%d", &i) != EOF)
    {
        // Измеряем время для итеративной функции
        clock_t start_iterative = clock();
        int result_iterative = fib_iterative(i);
        clock_t end_iterative = clock();
        double time_iterative = ((double) (end_iterative - start_iterative)) / CLOCKS_PER_SEC;

        printf("Итеративная: F(%d) = %d, Время: %.6f сек\n", i, result_iterative, time_iterative);

        // Измеряем время для рекурсивной функции
        clock_t start_recursive = clock();
        int result_recursive = fib_recursive(i);
        clock_t end_recursive = clock();
        double time_recursive = ((double) (end_recursive - start_recursive)) / CLOCKS_PER_SEC;

        printf("Рекурсивная: F(%d) = %d, Время: %.6f сек\n", i, result_recursive, time_recursive);
    }

    return 0;
}
