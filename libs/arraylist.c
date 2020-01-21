//
// Created by diego on 20/01/2020.
//

#include "arraylist.h"
#include <stdlib.h>

list *new_list() {
    list *l = (list *) calloc(sizeof(list), 1);
    return l;
}

void push(int val, list *l) {
    if (l == NULL)
        return;

    node *n = (node *) malloc(sizeof(node));
    n->value = val;
    n->next = NULL;

    if (l->first == NULL) {
        l->first = n;
        return;
    } else {
        node *a = l->first;
        while (a->next != NULL) {
            a = a->next;
        }
        a->next = n;
        return;;
    }
}

int search_list(int val, list *l) {
    if (l == NULL)
        return -1;

    node *n = l->first;

    while (n != NULL) {
        if (n->value == val) return 1;
        n = n->next;
    }

    return 0;
}

int size_list(list *l) {
    if (l == NULL)
        return -1;

    node *n = l->first;
    int i = 0;

    while (n != NULL) {
        i++;
        n = n->next;
    }

    return i;
}

void delete_list(list *l) {
    if (l == NULL)
        return;

    node *n = l->first;

    while (n != NULL) {
        node *tmp = n;
        n = n->next;
        free(tmp);
    }

    free(l);
}