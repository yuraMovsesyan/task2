#include <stdio.h>

double str2double(char str[])
{
    double result = 0.0;
    int i = 0;
    int sign = 1;

    // Пропускаем начальные пробелы
    while (str[i] == ' ')
    {
        i++;
    }

    // Знак числа
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    } 
    else if (str[i] == '+')
    {
        i++;
    }

    //Целая часть числа
    while ('0' <= str[i] && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    // Дробную часть числа
    if (str[i] == '.')
    {
        i++;
        double fraction = 0.1;
        while ('0' <= str[i] && str[i] <= '9')
        {
            result += (str[i] - '0') * fraction;
            fraction /= 10.0;
            i++;
        }
    }

    if (str[i] == 'e' || str[i] == 'E')
    {
        i++;
        int expSign = 1;
        if (str[i] == '-')
        {
            expSign = -1;
            i++;
        } else if (str[i] == '+')
        {
            i++;
        }

        int exponent = 0;
        while ('0' <= str[i] && str[i] <= '9')
        {
            exponent = exponent * 10 + (str[i] - '0');
            i++;
        }
        
        for (int j = 0; j < exponent; j++)
        {
            if (expSign > 0)
            {
                result *= 10;
            }
            else
            {
                result /= 10;
            }
        }
    }

    return sign * result;
}

int main()
{
    char str[100];

    while (scanf("%s", str) != EOF)
    {
        double result = str2double(str);
        printf("%.10g\n", result);
    }

    return 0;
}
