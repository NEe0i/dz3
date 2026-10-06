#include <stdio.h>

double power(double base, int exp) {
    double result = 1.0;

    long long exp_positive = exp;
    if (exp_positive < 0) {
        base = 1.0 / base;
        exp_positive = -exp_positive;
    }
    
    for (long long i = 0; i < exp_positive; i++) {
        result *= base;
    }
    
    return result;
}

int main() {
    double base;
    int exp;

    printf("Введите основание (double) и степень (int): ");
    if (scanf("%lf %d", &base, &exp) != 2) {
        printf("Ошибка ввода.\n");
        return 1;
    }

    double res = power(base, exp);
    printf("%.4f в степени %d равно %.4f\n", base, exp, res);

    return 0;
}
