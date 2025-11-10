#include <stdio.h>
#include <malloc.h>

void addTen(int *pointer) {
    if (pointer != NULL) {
        *pointer += 10;
    }
}

int main() {
    int a = 0;
    int *b = &a;
    *b += 5;
    int **c = &b;
    addTen(NULL);
    printf("%d %p %p %p %d\n", a, b, c, *c, **c);
    int *d = (int *)malloc(sizeof(int)*10);
    *d = 99;
    *(d+1) = 5;
    *(d+2) = 17;
    *(d+3) = 24; 
    d++;
    printf("%d %p %d %d %d\n", d[0], d, *d+1, d[2], d[3]);
    for (; *d>=0; (*d)--) {
        printf("Hello");
    }
    free(d-1);
    return 0;
}