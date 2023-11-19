#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Elem{
    char* val;

    struct Elem* back;
    struct Elem* next;
};

struct List {
    int count;

    struct Elem* last;
    struct Elem* first;
};

struct List* new_list()
{
    struct List* res = (struct List*)malloc(sizeof(struct List));

    res->count = 0;
    res->last = NULL;
    res->first = NULL;

    return res;
}

void add_elem(struct List* list, char* val)
{
    struct Elem* elem = (struct Elem*)malloc(sizeof(struct Elem));
    elem->next = NULL;

    elem->val = (char*)calloc(strlen(val), sizeof(char));
    
    strcpy(elem->val, val);

    if (list->count == 0)
    {
        elem->back = NULL;
        list->first = elem;
    }
    else
    {
        elem->back = list->last;
        list->last->next = elem;
    }

    list->last = elem;
    list->count++;
}

void remove_at_list(struct List* list, int index)
{
    struct Elem* elem = list->first;
    int flag = 0;

    for (int i = 0; i < list->count; i++)
    {
        if (index == i)
        {
            flag = 1;
            break;
        }

        elem = elem->next;
    }

    if (flag == 1)
    {
        if (elem->back == NULL)
        {
            list->first = elem->next;
        }
        if (elem->next == NULL)
        {
            list->last = elem->back;
        }

        if (elem->back != NULL && elem->next != NULL)
        {
            elem->back->next = elem->next;
            elem->next->back = elem->back;
        }

        free(elem);

        list->count--;
    }
}

int remove_list(struct List* list, char* str)
{
    struct Elem* elem = list->first;
    int flag = 0;
    int i;
    for (i = 0; i < list->count; i++)
    {
        if (strcmp(elem->val, str) == 0)
        {
            flag = 1;
            break;
        }

        elem = elem->next;
    }

    if (flag == 1)
    {
        remove_at_list(list, i);
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_list(struct List* list)
{
    printf("[");
    struct Elem* elem = list->first;
    for (int i = 0; i < list->count; i++)
    {
        printf("\"%s\"", elem->val);

        if (i+1 != list->count)
        {
            printf(", ");
        }

        elem = elem->next;
    }
    printf("]");
}

int main()
{
    struct List* list = new_list();
    
    char buff[50];
    int i = 0;
    char c;
    while ((c = getc(stdin)) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            buff[i] = '\0';
            add_elem(list, buff);
            i = 0;
            if (c == '\n') break;
            else continue;
        }
        buff[i] = c;
        i++;
    }

    print_list(list);
    printf("\n");
    if (list->count != 0)
    {
        char* val_last = (char*)calloc(strlen(list->last->val), sizeof(char));
        strcpy(val_last, list->last->val);
        while(remove_list(list, val_last) != 0){}
        add_elem(list, val_last);
        print_list(list);
    }
    printf("\n");
    
    return 0;
}