#include <stdio.h>
#include <malloc.h>

void printMatrix(int**matrix, int m, int n);

void quickSort(int**matrix, int m, int n, int sortCol, int L, int R) {
    int i = L - 1;
    int j = L;
    int pivot = R;
    for (; j < pivot; j++) {
        if (matrix[j][sortCol] < matrix[pivot][sortCol]) {
            i++;
            int c = matrix[j][sortCol];
            matrix[j][sortCol] = matrix[i][sortCol];
            matrix[i][sortCol] = c;
        }
    }
    int c = matrix[pivot][sortCol];
    matrix[pivot][sortCol] = matrix[i+1][sortCol];
    matrix[i+1][sortCol] = c;
    pivot = i + 1;
    if (L < pivot - 1) {
        quickSort(matrix, m, n, sortCol, L, pivot - 1);
    }
    if (pivot + 1 < R) {
        quickSort(matrix, m, n, sortCol, pivot + 1, R);
    }
    
}

void quickSort2(int**matrix, int L, int R) {
    int i = L - 1;
    int j = L;
    int pivot = R;
    for (; j < pivot; j++) {
        if (matrix[j][j] < matrix[pivot][pivot]) {
            i++;
            int c = matrix[j][j];
            matrix[j][j] = matrix[i][i];
            matrix[i][i] = c;
        }
    }

    int c = matrix[pivot][pivot];
    matrix[pivot][pivot] = matrix[i+1][i+1];
    matrix[i+1][i+1] = c;
    pivot = i + 1;

    if (L < pivot - 1) {
        quickSort2(matrix, L, pivot - 1);
    }
    if (pivot + 1 < R) {
        quickSort2(matrix, pivot + 1, R);
    }
}

int main() {
    int m = 10;
    int n = 10;
    srand(time(NULL));
    int **matrix = (int**)malloc(sizeof(int*)*m);
    for (int i = 0; i < m; i++) {
        matrix[i] = (int*)malloc(sizeof(int)*n);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 101;
        }
    }
    //matrix[0][2] = 56;
    //matrix[1][2] = 85;
    //matrix[2][2] = 9;
    //matrix[3][2] = 84;
    //matrix[4][2] = 1;
    //matrix[5][2] = 20;
    //printMatrix(matrix, m, n);
    quickSort2(matrix, 0, 9);
    printMatrix(matrix, m, n);
    return 0;
}

void printMatrix(int**matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%3d\t", matrix[i][j]);
        }
        printf("\n");
    }
}