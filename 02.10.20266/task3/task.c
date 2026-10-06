#include <stdio.h>
#include <stdbool.h>

bool isEven(int n) {
    return n % 2 == 0;
}

int main() {
    printf("Чётные числа от 1 до 20:\n");

    for (int i = 1; i <= 20; i++) {
        if (isEven(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}
