#include <iostream>
#include <string>
#include <unistd.h>
#include <gmp.h>


double func_double(double x, double y)
{
    return (1682.0*x*y*y*y*y + 3.0*x*x*x + 29.0*x*y*y - 2.0*x*x*x*x*x + 832.0) / 107751.0;
}

long double func_long_double(long double x, long double y)
{
    return (1682.0L*x*y*y*y*y + 3.0L*x*x*x + 29.0L*x*y*y - 2.0L*x*x*x*x*x + 832.0L) / 107751.0L;
}

void test_standard_types()
{
    std::cout << "\n=== Стандартные типы (C++) ===" << std::endl;

    double xd = 192119201.0, yd = 35675640.0;
    long double xl = 192119201.0L, yl = 35675640.0L;

    std::cout << "double:      " << func_double(xd, yd)      << std::endl;
    std::cout << "long double: " << func_long_double(xl, yl) << std::endl;
    std::cout << "Ожидаемый результат: 1783" << std::endl;
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

void info_mpz()
{
    std::cout << "\n=== GMP mpz_t (C++) ===" << std::endl;

    mpz_t x_1, y_1;
    mpz_inits(x_1, y_1, NULL);

    std::cout << "x = 192119201, y = 35675640" << std::endl;
    sleep(2);


    mpz_set_ui(x_1, 192119201);
    mpz_set_ui(y_1, 35675640);
    std::cout << "Ответ: ";
    func_mpz(x_1, y_1);
    

    std::cout << "Ожидаемый результат: 1783" << std::endl;
    mpz_clears(x_1, y_1, NULL);
}


int main()
{
    std::string formula = "(1682*x*y^4 + 3*x^3 + 29*x*y^2 - 2*x^5 + 832) / 107751";
    std::cout << "Программа для вычисления функции (C++):" << std::endl;
    std::cout << "f(x,y) = " << formula << std::endl;

    test_standard_types();
    info_mpz();

    return 0;
}
