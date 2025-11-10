#include <stdio.h>
#include <malloc.h>
#include <memory.h>

void printMatrix(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%3d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void quickSortMatrix3d(int***matrix3d, int l, int m, int n, int L, int R) {
    if (L >= R) return;
    int i = L - 1;
    int j = L;
    int pivot = R;
    int *a = (int *)malloc(sizeof(int) * n);
    for (; j < pivot; j++) {
        if (matrix3d[j][0][0] < matrix3d[pivot][0][0]) {
            i++;
            for (int x = 0; x < m; x++) {
                memcpy(a, matrix3d[j][x], sizeof(int)*n);
                memcpy(matrix3d[j][x], matrix3d[i+1][x], sizeof(int)*n);
                memcpy(matrix3d[i+1][x], a, sizeof(int)*n);
            }
        }
    }
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            memcpy(a, matrix3d[j][y], sizeof(int)*n);
            memcpy(matrix3d[j][y], matrix3d[i+1][y], sizeof(int)*n);
            memcpy(matrix3d[i+1][y], a, sizeof(int)*n);
        }
    }
    pivot = i + 1;
    if (L < pivot - 1)
        quickSortMatrix3d(matrix3d, l, m, n, L, pivot - 1);
    if (pivot + 1 < R)
        quickSortMatrix3d(matrix3d, l, m, n, pivot + 1, R);
}

int main()
{
    int m = 10;
    int n = 10;
    int l = 10;
    srand(time(NULL));
    int ***matrix3d = (int ***)malloc(sizeof(int **) * l);
    for (int k = 0; k < l; k++)
    {
        int **matrix = (int **)malloc(sizeof(int *) * m);
        for (int i = 0; i < m; i++)
        {
            matrix[i] = (int *)malloc(sizeof(int) * n);
        }
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = rand() % 101;
            }
        }
        matrix3d[k] = matrix;
    }
    int** c = matrix3d[0];
    matrix3d[0] = matrix3d[1];
    matrix3d[1] = c;
    quickSortMatrix3d(matrix3d, l, m, n, 0, l-1);
    printf("%d", matrix3d[4][0][0]);
    for (int k = 0; k < l; k++) 
    {
        printf("\n%d\n", k);
        printMatrix(matrix3d[k], m, n);
    }
    return 0;
}