#include <stdio.h>
#include <gmp.h>
#include <unistd.h>


double func_double(double x, double y)
{
    return (1682.0*x*y*y*y*y + 3.0*x*x*x + 29.0*x*y*y - 2.0*x*x*x*x*x + 832.0) / 107751.0;
}

long double func_long_double(long double x, long double y)
{
    return (1682.0L*x*y*y*y*y + 3.0L*x*x*x + 29.0L*x*y*y - 2.0L*x*x*x*x*x + 832.0L) / 107751.0L;
}

void test_standard_types(unsigned long xi, unsigned long yi)
{
    double xd = (double)xi, yd = (double)yi;
    long double xl = (long double)xi, yl = (long double)yi;

    printf("\n=== Стандартные типы (C) ===\n");
    printf("double:      %.2f\n",  func_double(xd, yd));
    printf("long double: %.2Lf\n", func_long_double(xl, yl));
    printf("Ожидаемый результат: 1783\n");
}


void func_mpz(mpz_t x, mpz_t y)
{
    mpz_t y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result;
    mpz_inits(y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result, NULL);

    mpz_pow_ui(y4, y, 4);
    mpz_mul(tmp1, x, y4);
    mpz_mul_ui(tmp1, tmp1, 1682);

    mpz_pow_ui(x3, x, 3);
    mpz_mul_ui(tmp2, x3, 3);

    mpz_pow_ui(y2, y, 2);
    mpz_mul(tmp3, x, y2);
    mpz_mul_ui(tmp3, tmp3, 29);

    mpz_pow_ui(x5, x, 5);
    mpz_mul_si(tmp4, x5, -2);

    mpz_add(result, tmp1, tmp2);
    mpz_add(result, result, tmp3);
    mpz_add(result, result, tmp4);
    mpz_add_ui(result, result, 832);
    mpz_tdiv_q_ui(result, result, 107751);

    gmp_printf("mpz_t:       %Zd\n", result);

    mpz_clears(y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result, NULL);
}

void test_gmp_mpz(unsigned long xi, unsigned long yi)
{
    printf("\n=== GMP mpz_t (C) ===\n");
    mpz_t x, y;
    mpz_inits(x, y, NULL);
    mpz_set_ui(x, xi);
    mpz_set_ui(y, yi);
    func_mpz(x, y);
    printf("Ожидаемый результат: 1783\n");
    mpz_clears(x, y, NULL);
}


int main(void)
{
    unsigned long x_val = 192119201UL;
    unsigned long y_val = 35675640UL;

    printf("Программа для вычисления функции (язык C):\n");
    printf("f(x,y) = (1682*x*y^4 + 3*x^3 + 29*x*y^2 - 2*x^5 + 832) / 107751\n");
    printf("x = %lu, y = %lu\n", x_val, y_val);

    sleep(2);

    test_standard_types(x_val, y_val);
    test_gmp_mpz(x_val, y_val);

    return 0;
}
