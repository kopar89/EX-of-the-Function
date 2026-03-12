#include <cmath>
#include <iostream>
#include <mpreal.h>
#include <unistd.h>

void func(mpfr::mpreal x, mpfr::mpreal y)
{
    mpfr::mpreal y1, x1, y2, y4, x3, tmp1, tmp2, tmp3, tmp4, result;
    
    // 1682*x*y^4
    y1 = mpfr::pow(y, 4, MPFR_RNDN);
    tmp1 = x * y1 * 1682;

    // 3*x^3
    x1 = mpfr::pow(x, 3, MPFR_RNDN);
    tmp2 = x1 * 3;

    // 29*x*y^2

    y2 = mpfr::pow(y, 2, MPFR_RNDN);
    tmp3 = x * y2 * 29;

    // -2*x^5
    x3 = mpfr::pow(x, 5, MPFR_RNDN);
    tmp4 = x3 * (-2);

    // сумма + 832
    //mpreal::set_default_rnd(MPFR_RNDN);
    result = tmp1 + tmp2 + tmp3 + tmp4 + 832;

    // умножаем на lambda = 1/107751
    result /= 107751;

    std::cout << result << std::endl;
}

void info_for_mpz(){
    std::cout << "Программа для вычисления функции от двух переменных x и y. С помощью библиотеки GMP(тип переменной mpz_t)" << std::endl;
    mpfr::mpreal x_1, y_1, x_2, y_2, x, y;
    mpfr::mpreal const_x = 192119201;
    mpfr::mpreal const_y = 35675640;


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
        std::cin >> x_2;
        std::cout << "y = ";
        std::cin >> y_2;
        std::cout << "Ответ: ";
        func(x_2,y_2);

    } else {
        x_1 = const_x;
        y_1 = const_y;

        std::cout << "Ответ: ";
        func(x_1,y_1);
    }
}


int main(){

    mpfr::mpreal::set_default_prec(256);
    info_for_mpz();
    return 0;


}
