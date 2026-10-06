#include <stdio.h>

int maxOfThree(int a, int b, int c) {
    int max = a;

    if (b > max) {
        max = b;
    }
    
    if (c > max) {
        max = c;
    }

    return max;
}

int main() {
    int num1, num2, num3;
    printf("Введите три целых числа через пробел: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    int max_num = maxOfThree(num1, num2, num3);
    printf("Наибольшее число: %d\n", max_num);

    return 0;
}
