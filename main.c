#include <stdio.h>
#include <malloc.h>

typedef struct s_list
{
    int value;
    struct s_list *next;
} list;

list *addList(list *first, int value)
{
    list *second = (list *)malloc(sizeof(list));
    second->value = value;
    second->next = NULL;
    if (first == NULL)
    {
        return second;
    }
    for (; first->next != NULL; first = first->next)
    {
    }
    first->next = second;
    return second;
}

list *removeList(list *first, int index)
{
    list *second;
    second = first;
    if (first == NULL || index < 0)
    {
        return NULL;
    }
    for (int i = 0; i < index - 1; i++)
    {
        second = second->next;
        if (second == NULL)
        {
            return NULL;
        }
    }
    if (index == 0)
    {
        list *third = second->next;
        free(second);
        return third;
    }
    else
    {

        list *delete;
        if (second->next == NULL)
        {
            return NULL;
        }
        delete = second->next;
        second->next = delete->next;
        free(delete);
        return first;
    }
}

void printList(list *first)
{
    for (; first != NULL; first = first->next)
    {
        printf("%d\n", first->value);
    }
}

void freeList(list *first)
{
    for (list *nnext; first != NULL; first = nnext)
    {
        nnext = first->next;
        free(first);
    }
}

int sizeList(list *first)
{
    int i = 0;
    for (; first != NULL; first = first->next)
    {
        i++;
    }
    return i;
}

int atList(list *first, int index)
{

    for (int i = 0; i < index; i++)
    {
        if (first != NULL)
        {
            first = first->next;
        }
        else
        {
            return -1;
        }
    }
    if (first == NULL)
    {
        return -1;
    }
    return first->value;
}

void swap(list *first, int index1, int index2)
{
    if (index1 == index2)
    {
        return;
    }
    if (index1 > index2)
    {
        int k = index1;
        index1 = index2;
        index2 = k;
    }
    if (first == NULL)
    {
        return first;
    }
    list *second;
    second = first;
    for (int i = 0; i < index1 - 1; i++)
    {
        second = second->next;
        if (second == NULL)
        {
            return NULL;
        }
    }
    list *third;
    third = first;
    for (int i = 0; i < index2 - 1; i++)
    {
        third = third->next;
        if (third == NULL)
        {
            return NULL;
        }
    }
    list *swap1 = second->next;
    list *swap2 = third->next;

    if (swap1 == third)
    {
        second->next = swap2;
        swap1->next = swap2->next;
        swap2->next = swap1;
    }
    else
    {
        list *swapp = swap2->next;
        second->next = swap2;
        third->next = swap1;
        swap2->next = swap1->next;
        swap1->next = swapp;
    }
}

void sortList(list *first, int size) {
    if (first == NULL || size < 2) {
        return;
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            list *second = first;
            list *third = first;
            for (int k = 0; k < j; k++) {
                if (second == NULL) return; 
                second = second->next;
            }
            for (int k = 0; k < j + 1; k++) {
                if (third == NULL) return; 
                third = third->next;
            }
            if (second == NULL || third == NULL) {
                return;
            }
            if (second->value > third->value) {
                swap(first, j, j + 1);
            }
        }
    }
}

int main()
{
    list *sm = (list *)malloc(sizeof(list));
    sm->value = 5;
    list *sm1 = (list *)malloc(sizeof(list));
    sm->next = sm1;
    sm1->value = 8;
    list *sm2 = (list *)malloc(sizeof(list));
    sm1->next = sm2;
    sm2->value = 7;
    sm2->next = NULL;
    int size = sizeList(sm);
    for (int i = 0; i < size; i++) {
        printf("%d\n", atList(sm, i));
    }
    //printList(sm);
    //freeList(sm);
    //sm = NULL;
    //printf("%d\n", sizeList(sm));
    //printf("%d\n", atList(sm, 3));
    sortList(sm, size);
    //swap(sm, 1, 2);
    printList(sm);
    return 0;
}