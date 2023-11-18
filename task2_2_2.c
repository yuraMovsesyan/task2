#include <stdio.h>

void gorner_scheme(double x)
{
    double coefficient, result = 0, d = 0;

    for (int i = 0; printf("a%d: ", i) && scanf("%lf", &coefficient) != EOF; ++i)
    {
        d = d * x + result;
        result = result * x + coefficient;
    }

    printf("\nresult= %.10g\n", result);
    printf("d= %.10g\n", d);
}

int main()
{
    double x;

    printf("x= ");
    scanf("%lf", &x);

    gorner_scheme(x);

    return 0;
}
