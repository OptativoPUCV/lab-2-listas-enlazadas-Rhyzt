#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *L = (List *)malloc(sizeof(List));
    L -> head = NULL;
    L -> tail = NULL;
    L -> current = NULL;
     return L;
}

void * firstList(List * list) {
    list -> current = list -> head;
    if (list -> current == NULL)
        return NULL;
    return list -> current -> data;
}

void * nextList(List * list) {
    if (list -> current == NULL || list -> current -> next == NULL)
        return NULL;
    list -> current = list -> current -> next;
    if (list -> current == NULL)
        return NULL;
    return list -> current -> data;
}

void * lastList(List * list) {
    if (list -> tail == NULL)
        return NULL;
    list -> current = list -> tail;
    return list -> current -> data;
}

void * prevList(List * list) {
    if (list -> current == NULL || list -> current -> prev == NULL)
        return NULL;
    list -> current = list -> current -> prev;
    return list -> current -> data;
}

void pushFront(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
    if (list -> head == NULL) {
        list -> head = nuevoNodo;
        list -> tail = nuevoNodo;
        return;
    }
    list -> head -> prev = nuevoNodo;
    nuevoNodo -> next = list -> head;
    list -> head = nuevoNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
    if (list -> head == NULL) {
        list -> head = nuevoNodo;
        list -> tail = nuevoNodo;
        return;
    }
    nuevoNodo -> next = list -> current -> next;
    nuevoNodo -> prev = list -> current;
    list -> current -> next = nuevoNodo;
    if (nuevoNodo -> next != NULL)
        list -> current -> next -> prev = nuevoNodo;
    else
        list -> tail = nuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    void *dato;
    Node *aux;
    if (list -> current -> prev == NULL) {
        list -> current -> next -> prev = NULL;
        list -> head = list -> current -> next;
        dato = list -> current -> data;
        aux = list -> current -> next;
        free(list -> current);
        list -> current = aux;
    }
    else if (list -> current -> next == NULL) {
        list -> current -> prev -> next = NULL;
        list -> tail = list -> current -> prev;
        dato = list -> current -> data;
        aux = list -> current -> prev;
        free(list -> current);
        list -> current = aux; 
    }
    else {
        list -> current -> prev -> next = list -> current -> next;
        list -> current -> next -> prev = list -> current -> prev;
        dato = list -> current -> data;
        aux = list -> current -> next;
        free(list -> current);
        list -> current = aux;
    }
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}