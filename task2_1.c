#include <stdio.h>

double abs(double x)
{
    return x >= 0 ? x : -x;
}

double calculate_sqrt(double x, double epsilon)
{
    double i = x, old;

    do 
    {
        old = i;
        i = 0.5 * (i + x / i);
    } while (abs(old - i) > epsilon);

    return i;
}

int main()
{
    double epsilon, x;

    printf("epsilon= ");
    scanf("%lf", &epsilon);

    while (scanf("%lf", &x) != EOF)
    {
        double result = calculate_sqrt(x, epsilon);
        printf("%.10g\n", result);
    }

    return 0;
}
