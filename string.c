#include <malloc.h>
#include <stdio.h>
char **splitBySpace(char *str) {
    int n = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
        n++;
        }
    }
    int w = n + 1;
    char **r = malloc(sizeof(char *) * (w + 1));
    int *p = malloc(sizeof(int) * (n + 2));

    int x = 0;
    for (int i = 0; str[i]; i++)
        if (str[i] == ' ')
            p[x++] = i;

    p[x] = strlen(str);

    int start = 0;
    for (int i = 0; i < w; i++) {
        int l = p[i] - start;
        r[i] = malloc(l + 1);

        for (int j = 0; j < l; j++)
            r[i][j] = str[start + j];

        r[i][l] = '\0';
        start = p[i] + 1;
    }

    r[w] = NULL;
    free(p);
    return r;
}

int main() {
    char str[] = "Hello world! I'm an app developed by Oleksii";
    char **r = splitBySpace(str);

    for (int i = 0; r[i]; i++)
        printf("%s\n", r[i]);

    for (int i = 0; r[i]; i++)
        free(r[i]);
    free(r);
    
    char* a = (char *)malloc(sizeof(char) * 1000);
    scanf("%s", a);
    for (char* p = a; *p != '\0'; p++) {
        if (*p >= 'a' && *p <= 'z') {
            *p = *p - ('a' - 'A');
        }
    }
    printf("%s\n", a); // Abc
    // char* p = a + strlen(a) - 1;
    // for (; p >= a; p--) {
    //     printf("%c", *p);
    // }
    char* h = a + strlen(a);
    char* l = a;
    char* k = a + strlen(a) / 2;
    for (; a != k; a++){
        h--;
        char g = *a;
        *a = *h;
        *h = g;
    }
    printf("%s", l); // cbA
    //free(a);
    return 0;
}