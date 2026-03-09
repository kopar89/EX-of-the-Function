#include <cstdio>
#include <gmp.h>
#include <unistd.h>
#include <iostream>

void func(mpz_t x, mpz_t y)
{
    mpz_t y4,x3,y2,x5,tmp1,tmp2,tmp3,tmp4,result;
    mpz_inits(y4,x3,y2,x5,tmp1,tmp2,tmp3,tmp4,result,NULL);

    // 1682*x*y^4
    mpz_pow_ui(y4,y,4);
    mpz_mul(tmp1,x,y4);
    mpz_mul_ui(tmp1,tmp1,1682);

    // 3*x^3
    mpz_pow_ui(x3,x,3);
    mpz_mul_ui(tmp2,x3,3);

    // 29*x*y^2
    mpz_pow_ui(y2,y,2);
    mpz_mul(tmp3,x,y2);
    mpz_mul_ui(tmp3,tmp3,29);

    // -2*x^5
    mpz_pow_ui(x5,x,5);
    mpz_mul_si(tmp4,x5,-2);

    // сумма + 832
    mpz_add(result,tmp1,tmp2);
    mpz_add(result,result,tmp3);
    mpz_add(result,result,tmp4);
    mpz_add_ui(result,result,832);

    // умножаем на lambda = 1/107751
    mpz_tdiv_q_ui(result,result,107751);

    gmp_printf("%Zd\n",result);

    mpz_clears(y4,x3,y2,x5,tmp1,tmp2,tmp3,tmp4,result,NULL);
}

void info_for_mpz(){
    std::cout << "Программа для вычисления функции от двух переменных x и y. С помощью библиотеки GMP(тип переменной mpz_t)" << std::endl;
    mpz_t x_1, y_1, x_2, y_2, x, y;
    mpz_inits(x_1, y_1, x_2, y_2, x, y, NULL);

    std::string formula = "(1682*x*y^4 + 3*x^3 + 29*x*y^2 - 2*x^5 + 832) / 107751";
    std::cout << "Дана следующая функция: " << formula << std::endl;
    std::cout << "Также данные следующие начальные значения: " << std::endl;
    std::cout << "x = " << 192119201 << ", y = " << 35675640 << std::endl;
    sleep(5);

    std::cout << "Хотите протестировать на данных значениях? (y/n): ";
    char count;
    std::cin >> count;
    if(count != 'y' && count != 'Y'){
        std::cout << "Введите свои значения: " << std::endl;
        std::cout << "x = ";
        gmp_scanf("%Zd", x_2);
        std::cout << "y = ";
        gmp_scanf("%Zd", y_2);
        std::cout << "Ответ: ";
        func(x_2,y_2);

    } else {
        mpz_set_ui(x_1, 192119201);
        mpz_set_ui(y_1 ,35675640);
        std::cout << "Ответ: ";
        func(x_1,y_1);
    }
    mpz_clears(x_1, y_1, x_2, y_2, NULL);
}

int main() {
    info_for_mpz();
    return 0;
}
