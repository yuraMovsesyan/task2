#include <stdio.h>
#include <setjmp.h>

jmp_buf begin;
char curlex;

void getlex(void);
int expr(void);
int mult(void);
int pow(int n, int e);
int power(void);
int term();
void error(void);

int main()
{
    int result;
    setjmp(begin);
    printf("==>");
    getlex();
    result = expr();
    if (curlex != '\n') error();
    printf("\n%d\n", result);
    return 0;
}

void getlex()
{
    while ((curlex = getchar()) == ' ');
}

void error(void)
{
    printf("\nОШИБКА!\n");
    longjmp(begin, 1);
}

int expr()
{
    int e = mult();
    while (curlex == '+' || curlex == '-')
    {
        char operation = curlex;
        getlex();
        int term = mult();

        if (operation == '+')
        {
            e += term;
        }
        else if (operation == '-')
        {
            e -= term;
        }
    }
    return e;
}

int mult()
{
    int m = power();
    while (curlex == '*' || curlex == '/')
    {
        char operation = curlex;
        getlex();
        int factor = power();
        if (operation == '*')
        {
            m *= factor;
        } else if (operation == '/')
        {
            if (factor == 0)
            {
                error();
            }
            m /= factor;
        }
    }
    return m;
}

int term()
{
    int t;
    switch (curlex)
    {
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            t = curlex - '0';
            break;
        case '(':
            getlex();
            t = expr();
            if (curlex == ')') break;
        default:
            error();
    }
    getlex();
    return t;
}


int power()
{
    int res = term();
    while (curlex == '^')
    {
        getlex();
        int e = power();
        res = pow(res, e);
    }
    return res;

}

int pow(int n, int e)
{
    int res = 1;
    while (e > 0)
    {
        res *= n;
        e--;
    }
    return res;
}