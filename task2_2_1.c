#include <stdio.h>

double gorner_scheme(double x)
{
    double coefficient, result = 0;

    for (int i = 0; printf("a%d: ", i) && scanf("%lf", &coefficient) != EOF; ++i)
    {
        result = result * x + coefficient;
    }

    return result;
}

int main() {
    double x;

    printf("x= ");
    scanf("%lf", &x);

    printf("\nresult= %.10g\n", gorner_scheme(x));

    return 0;
}
