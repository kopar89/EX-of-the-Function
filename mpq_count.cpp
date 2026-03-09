#include <cstdio>
#include <gmp.h>
#include <unistd.h>
#include <iostream>

void mpq_pow_ui_custom(mpq_t rop, const mpq_t op, unsigned long int n)
{
    mpz_pow_ui(mpq_numref(rop), mpq_numref(op), n);
    mpz_pow_ui(mpq_denref(rop), mpq_denref(op), n);
    mpq_canonicalize(rop);
}

void mpq_mul_si_custom(mpq_t rop, const mpq_t op, signed long n)
{
    mpq_t tmp;
    mpq_init(tmp);
    mpq_set_si(tmp, n, 1);      
    mpq_mul(rop, op, tmp);      
    mpq_clear(tmp);
}

void mpq_mul_ui_custom(mpq_t rop, const mpq_t op, unsigned long n)
{
    mpq_t tmp;
    mpq_init(tmp);
    mpq_set_ui(tmp, n, 1);      
    mpq_mul(rop, op, tmp);      
    mpq_clear(tmp);
}

void func(mpq_t x, mpq_t y)
{
    mpq_t y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result;
    mpq_inits(y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result, NULL);

    // 1682*x*y^4
    mpq_pow_ui_custom(y4,y,4);
    mpq_mul(tmp1,x,y4);
    mpq_mul_ui_custom(tmp1,tmp1,1682);

    // 3*x^3
    mpq_pow_ui_custom(x3,x,3);
    mpq_mul_ui_custom(tmp2,x3,3);

    // 29*x*y^2
    mpq_pow_ui_custom(y2,y,2);
    mpq_mul(tmp3,x,y2);
    mpq_mul_ui_custom(tmp3,tmp3,29);

    // -2*x^5
    mpq_pow_ui_custom(x5,x,5);
    mpq_mul_si_custom(tmp4,x5,-2);

    // сумма + 832
    mpq_add(result, tmp1, tmp2);
    mpq_add(result, result, tmp3);
    mpq_add(result, result, tmp4);

    mpq_t c;
    mpq_init(c);
    mpq_set_ui(c, 832, 1);
    mpq_add(result, result, c);

    // деление на 107751
    mpq_set_ui(c, 1, 107751);
    mpq_mul(result, result, c);

    mpq_canonicalize(result);

    gmp_printf("%Qd\n",result);

    mpq_clears(y4,x3,y2,x5,tmp1,tmp2,tmp3,tmp4,result,c,NULL);
}

void info_for_mpq(){
    std::cout << "Программа для вычисления функции от двух переменных x и y. С помощью библиотеки GMP (тип переменной mpq_t)" << std::endl;

    char count;

    mpq_t x_1, y_1, x_2, y_2;
    mpq_inits(x_1, y_1, x_2, y_2, NULL);

    std::string formula = "(1682*x*y^4 + 3*x^3 + 29*x*y^2 - 2*x^5 + 832) / 107751";

    std::cout << "Дана следующая функция: " << formula << std::endl;
    std::cout << "Также данные следующие начальные значения: " << std::endl;

    std::cout << "x = 192119201, y = 35675640" << std::endl;

    sleep(5);

    std::cout << "Хотите протестировать на данных значениях? (y/n): ";
    std::cin >> count;

    if(count != 'y' && count != 'Y'){
        std::cout << "Введите свои значения: " << std::endl;

        std::cout << "x = ";
        gmp_scanf("%Qd", x_2);

        std::cout << "y = ";
        gmp_scanf("%Qd", y_2);

        std::cout << "Ответ: ";
        func(x_2,y_2);

    } else {

        mpq_set_ui(x_1, 192119201, 1);
        mpq_set_ui(y_1, 35675640, 1);

        std::cout << "Ответ: ";
        func(x_1,y_1);
    }

    mpq_clears(x_1, y_1, x_2, y_2, NULL);
}

int main() {
    info_for_mpq();
    return 0;
}
