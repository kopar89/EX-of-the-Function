#include <cstdio>
#include <gmp.h>
#include <unistd.h>
#include <iostream>

void func(mpf_t x, mpf_t y)
{
    mpf_t y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result;
    mpf_inits(y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result, NULL);

    // 1682*x*y^4
    mpf_pow_ui(y4, y, 4);
    mpf_mul(tmp1, x, y4);
    mpf_mul_ui(tmp1, tmp1, 1682);

    // 3*x^3
    mpf_pow_ui(x3, x, 3);
    mpf_mul_ui(tmp2, x3, 3);

    // 29*x*y^2
    mpf_pow_ui(y2, y, 2);
    mpf_mul(tmp3, x, y2);
    mpf_mul_ui(tmp3, tmp3, 29);

    // -2*x^5 (ИСПРАВЛЕНО: использован mpf_mul_si вместо передачи -2 как mpf_t)
    mpf_pow_ui(x5, x, 5);
    mpf_mul_ui(tmp4, x5, 2);
    mpf_neg(tmp4, tmp4);

    // сумма + 832
    mpf_add(result, tmp1, tmp2);
    mpf_add(result, result, tmp3);
    mpf_add(result, result, tmp4);
    mpf_add_ui(result, result, 832);

    // умножаем на lambda = 1/107751
    mpf_div_ui(result, result, 107751);

    gmp_printf("%Ff\n", result);

    mpf_clears(y4, x3, y2, x5, tmp1, tmp2, tmp3, tmp4, result, NULL);
}

void info_for_mpf()
{
    std::cout << "Программа для вычисления функции от двух переменных x и y. "
              << "С помощью библиотеки GMP (тип переменной mpf_t)" << std::endl;

    mpf_t x_1, y_1, x_2, y_2;
    mpf_inits(x_1, y_1, x_2, y_2, NULL);

    std::string formula = "(1682*x*y^4 + 3*x^3 + 29*x*y^2 - 2*x^5 + 832) / 107751";
    std::cout << "Дана следующая функция: " << formula << std::endl;
    std::cout << "Также данные следующие начальные значения: " << std::endl;
    std::cout << "x = " << 192119201 << ", y = " << 35675640 << std::endl;

    sleep(5);

    std::cout << "Хотите протестировать на данных значениях? (y/n): ";
    char choice;
    std::cin >> choice;

    if (choice != 'y' && choice != 'Y') {
        std::cout << "Введите свои значения: " << std::endl;
        std::cout << "x = ";
        gmp_scanf("%Ff", x_2);
        std::cout << "y = ";
        gmp_scanf("%Ff", y_2);
        std::cout << "Ответ: ";
        func(x_2, y_2);
    } else {
        mpf_set_ui(x_1, 192119201);
        mpf_set_ui(y_1, 35675640);
        std::cout << "Ответ: ";
        func(x_1, y_1);
    }

    mpf_clears(x_1, y_1, x_2, y_2, NULL);
}

int main()
{
    mpf_set_default_prec(70);

    info_for_mpf();
    return 0;
}
