#include <stdio.h>
#include <mpfr.h>
#include <unistd.h>

void func(mpfr_t x, mpfr_t y)
{
    mpfr_t y1, x1, y2, y4, x3, x4, tmp1, tmp2, tmp3, tmp4, result;
    mpfr_inits(y1, x1, y2, y4, x3, x4, tmp1, tmp2, tmp3, tmp4, result, NULL);

    // 1682*x*y^4
    mpfr_pow_ui(y1, y, 4, MPFR_RNDN);
    mpfr_mul(y1, y1, x, MPFR_RNDN);
    mpfr_mul_ui(tmp1, y1, 1682, MPFR_RNDN);

    // 3*x^3
    mpfr_pow_ui(x1, x, 3, MPFR_RNDN);
    mpfr_mul_ui(tmp2, x1, 3, MPFR_RNDN);

    // 29*x*y^2
    mpfr_pow_ui(y2, y, 2, MPFR_RNDN);
    mpfr_mul(x3, y2, x, MPFR_RNDN);
    mpfr_mul_ui(tmp3, x3, 29, MPFR_RNDN);

    // -2*x^5
    mpfr_pow_ui(x4, x, 5, MPFR_RNDN);
    mpfr_mul_si(tmp4, x4, -2, MPFR_RNDN);

    mpfr_add(result, tmp1, tmp2, MPFR_RNDN);
    mpfr_add(result, result, tmp3, MPFR_RNDN);
    mpfr_add(result, result, tmp4, MPFR_RNDN);
    mpfr_add_ui(result, result, 832, MPFR_RNDN);
    mpfr_div_ui(result, result, 107751, MPFR_RNDN);
    
    mpfr_printf("%.3Re\n", result);
 
    mpfr_clears(y1, x1, y2, y4, x3, x4, tmp1, tmp2, tmp3, tmp4, result, NULL); 
}

void info_for_mpfr(void)
{
    mpfr_t x_1, y_1, x_2, y_2;
    mpfr_inits(x_1, y_1, x_2, y_2, NULL);
 
    printf("Программа для вычисления функции от двух переменных x и y.\n");
    printf("С помощью библиотеки MPFR (тип переменной mpfr_t)\n");
    printf("Дана следующая функция: (1682*x*y^4 + 3*x^3 + 29*x*y^2 - 2*x^5 + 832) / 107751\n");
    printf("Также данные следующие начальные значения:\n");
    printf("x = 192119201, y = 35675640\n");
 
    sleep(5);
 
    printf("Хотите протестировать на данных значениях? (y/n): ");
    char choice;
    scanf(" %c", &choice);
 
    if (choice != 'y' && choice != 'Y') {
        char buf[256];
        printf("Введите свои значения:\n");
        printf("x = ");
        scanf("%s", buf);
        mpfr_set_str(x_2, buf, 10, MPFR_RNDN);
        printf("y = ");
        scanf("%255s", buf);
        mpfr_set_str(y_2, buf, 10, MPFR_RNDN);
        printf("Ответ: ");
        func(x_2, y_2);
    } else {
        mpfr_set_str(x_1, "192119201", 10, MPFR_RNDN);
        mpfr_set_str(y_1, "35675640",  10, MPFR_RNDN);
        printf("Ответ: ");
        func(x_1, y_1);
    }
 
    mpfr_clears(x_1, y_1, x_2, y_2, NULL);
}


int main(){

    mpfr_set_default_prec(256);
    info_for_mpfr();
    return 0;


}
