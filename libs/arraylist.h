//
// Created by diego on 20/01/2020.
//

#ifndef HOTEL_ARRAYLIST_H
#define HOTEL_ARRAYLIST_H

#endif //HOTEL_ARRAYLIST_H

typedef struct n {
    int value;
    struct n *next;
} node;

typedef struct {
    node *first;
} list;

list *new_list();

void push(int val, list *l);

int search_list(int val, list *l);

int size_list(list *l);

void delete_list(list *l);