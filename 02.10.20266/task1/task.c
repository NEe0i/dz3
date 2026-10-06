#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}

int main() {
    int num1, num2, result;
    
    printf("Введите первое число: ");
    scanf("%d", &num1);

    printf("Введите второе число: ");
    scanf("%d", &num2);
   
    result = sum(num1, num2);

    printf("Сумма чисел %d и %d равна %d\n", num1, num2, result);
    
    return 0;
}
