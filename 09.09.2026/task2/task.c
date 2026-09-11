#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct {
    int rows;
    int cols;
    double** data;
    double* row_sums;
    double* col_sums;
} Matrix;

Matrix createMatrix(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;

    m.data = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        m.data[i] = (double*)malloc(cols * sizeof(double));
    }

    m.row_sums = (double*)calloc(rows, sizeof(double));
    m.col_sums = (double*)calloc(cols, sizeof(double));
    
    return m;
}

void freeMatrix(Matrix* m) {
    if (m->data != NULL) {
        for (int i = 0; i < m->rows; i++) {
            free(m->data[i]);
        }
        free(m->data);
        m->data = NULL;
    }
    if (m->row_sums != NULL) {
        free(m->row_sums);
        m->row_sums = NULL;
    }
    if (m->col_sums != NULL) {
        free(m->col_sums);
        m->col_sums = NULL;
    }
}

void inputMatrix(Matrix* m) {
    printf("Введите элементы матрицы (%dx%d):\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            while (printf("Элемент [%d][%d]: ", i, j) && scanf("%lf", &m->data[i][j]) != 1) {
                printf("Ошибка ввода! Введите число.\n");
                while (getchar() != '\n'); 
            }
        }
    }
}

void printMatrix(const Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%10.2f ", m->data[i][j]);
        }
        printf("\n");
    }
}

void findMaxElement(const Matrix* m) {
    if (m->rows <= 0 || m->cols <= 0) return;
    
    double max_val = m->data[0][0];
    int max_row = 0;
    int max_col = 0;
    
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (m->data[i][j] > max_val) {
                max_val = m->data[i][j];
                max_row = i;
                max_col = j;
            }
        }
    }
    printf("\nМаксимальный элемент: %.2f (Индексы: строка %d, столбец %d)\n", max_val, max_row, max_col);
}

void calculateSums(Matrix* m) {

    for (int i = 0; i < m->rows; i++) m->row_sums[i] = 0;
    for (int j = 0; j < m->cols; j++) m->col_sums[j] = 0;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->row_sums[i] += m->data[i][j];
            m->col_sums[j] += m->data[j][i];
        }
    }
}

void printSums(const Matrix* m) {
    printf("\nСуммы строк: ");
    for (int i = 0; i < m->rows; i++) printf("%.2f  ", m->row_sums[i]);
    printf("\nСуммы столбцов: ");
    for (int j = 0; j < m->cols; j++) printf("%.2f  ", m->col_sums[j]);
    printf("\n");
}

void normalizeMatrix(Matrix* m) {
    calculateSums(m);
    
    for (int i = 0; i < m->rows; i++) {
        if (m->row_sums[i] == 0.0) {
            printf("\nПредупреждение: Сумма строки %d равна 0. Нормализация этой строки пропущена во избежание деления на ноль.\n", i);
            continue;
        }
        for (int j = 0; j < m->cols; j++) {
            m->data[i][j] /= m->row_sums[i];
        }
    }
}

Matrix multiplyMatrices(const Matrix* m1, const Matrix* m2, int* success) {
    if (m1->cols != m2->rows) {
        printf("\nОшибка: Матрицы несогласованы для умножения! (Кол-во столбцов А != Кол-ву строк В)\n");
        *success = 0;
        Matrix empty = {0, 0, NULL, NULL, NULL};
        return empty;
    }
    
    Matrix result = createMatrix(m1->rows, m2->cols);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->cols; j++) {
            result.data[i][j] = 0;
            for (int k = 0; k < m1->cols; k++) {
                result.data[i][j] += m1->data[i][k] * m2->data[k][j];
            }
        }
    }
    *success = 1;
    return result;
}

void findSaddlePoints(const Matrix* m) {
    int found = 0;
    printf("\nПоиск седловых точек (минимум в строке, максимум в столбце):\n");
    
    for (int i = 0; i < m->rows; i++) {
        double min_in_row = m->data[i][0];
        for (int j = 1; j < m->cols; j++) {
            if (m->data[i][j] < min_in_row) {
                min_in_row = m->data[i][j];
            }
        }

        for (int j = 0; j < m->cols; j++) {
            if (m->data[i][j] == min_in_row) {
                int is_saddle = 1;
                for (int k = 0; k < m->rows; k++) {
                    if (m->data[k][j] > min_in_row) {
                        is_saddle = 0;
                        break;
                    }
                }
                if (is_saddle) {
                    printf("Седловая точка найдена на позиции [%d][%d] со значением: %.2f\n", i, j, min_in_row);
                    found = 1;
                }
            }
        }
    }
    if (!found) {
        printf("Седловых точек в матрице не обнаружено.\n");
    }
}

int main() {
    int m, n;

    printf("Введите количество строк M: ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        printf("Некорректный размер строк.\n");
        return 1;
    }
    printf("Введите количество столбцов N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Некорректный размер столбцов.\n");
        return 1;
    }

    Matrix mat = createMatrix(m, n);
    inputMatrix(&mat);
    
    printf("\nИсходная матрица:\n");
    printMatrix(&mat);

    findMaxElement(&mat);

    calculateSums(&mat);
    printSums(&mat);

    findSaddlePoints(&mat);
    printf("Выполняется нормализация матрицы...");
    normalizeMatrix(&mat);
    printf("Матрица после нормализации:");
    printMatrix(&mat);
    
    printf("Демонстрация умножения матриц (A * B)");
    printf("Создадим вторую матрицу B для умножения на текущую матрицу A.");
    printf("Матрица B должна иметь %d строк.\nУкажите число столбцов для матрицы B: ", mat.cols);
    int b_cols;
    if (scanf("%d", &b_cols) == 1 && b_cols > 0) {
        Matrix matB = createMatrix(mat.cols, b_cols);
        inputMatrix(&matB);
        
        int success;
        Matrix matRes = multiplyMatrices(&mat, &matB, &success);
        if (success) {
            printf("\nРезультат умножения матриц:\n");
            printMatrix(&matRes);
            freeMatrix(&matRes);
        }
        freeMatrix(&matB);
    } else {
        printf("Пропущено или некорректный ввод столбцов.\n");
    }
    freeMatrix(&mat);
    return 0;
}
