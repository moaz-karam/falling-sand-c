#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

DLL* dll_create() {

    DLL* dll = malloc(sizeof(DLL));

    dll->sentinel = malloc(sizeof(Node));
    
    dll->sentinel->next = dll->sentinel;
    dll->sentinel->prev = dll->sentinel;
    
    dll->size = 0;
    return dll;
}

void dll_addLast(DLL* dll, void* data) {
    Node* node = malloc(sizeof(Node));

    node->data = data;
    
    node->next = dll->sentinel;
    node->prev = dll->sentinel->prev;

    dll->sentinel->prev = node;
    node->prev->next = node;

    dll->size += 1;
}

void dll_addFirst(DLL* dll, void* data) {
    Node* node = malloc(sizeof(Node));

    node->data = data;

    node->prev = dll->sentinel;
    node->next = dll->sentinel->next;

    dll->sentinel->next = node;
    node->next->prev = node;

    dll->size += 1;
}

void* dll_getLast(DLL* dll) {
    return dll->sentinel->prev->data;
}

void* dll_getFirst(DLL* dll) {
    return dll->sentinel->next->data;
}

void* dll_get(DLL* dll, int i) {

    if (i >= dll->size) {
        printf("Index %i is not in the dll\n", i);
        abort();
    }

    DLL_Iterator* iter = dll_iter_create(dll);

    int index = 0;
    void* temp;
    for (iter; dll_iter_hasNext(iter); dll_iter_next(iter)) {
        if (index == i) {
            temp = dll_iter_data(iter);
            break;
        }
        index += 1;
    }

    dll_iter_end(iter);
    return temp;
}

void* dll_removeLast(DLL* dll) {
    if (dll->size <= 0) {
        return NULL;
    }

    void* data;
    Node* node = dll->sentinel->prev;
    node->prev->next = dll->sentinel;
    dll->sentinel->prev = node->prev;

    data = node->data;
    free(node);

    dll->size -= 1;
    return data;
}

void* dll_removeFirst(DLL* dll) {

    if (dll->size <= 0) {
        return NULL;
    }

    void* temp;
    Node* node = dll->sentinel->next;
    node->next->prev = dll->sentinel;
    dll->sentinel->next = node->next;

    temp = node->data;
    free(node);

    dll->size -= 1;
    return temp;
}

void* dll_remove(DLL* dll, void* data) {
    DLL_Iterator* iter = dll_iter_create(dll);
    void* temp;
    for (iter; dll_iter_hasNext(iter); dll_iter_next(iter)) {
        if (data == dll_iter_data(iter)) {
            temp = dll_iter_remove(iter);
        }
    }
    return temp;
}

void dll_end(DLL* dll) {
    DLL_Iterator* removeIter = dll_iter_create();

    dll_iter_set(removeIter, dll);
    while (dll->size > 0) {
        dll_iter_remove(removeIter);
        dll_iter_next(removeIter);
    }

    dll_iter_end(removeIter);
    free(dll->sentinel);
    free(dll);
}


DLL_Iterator* dll_iter_create() {
    DLL_Iterator* iter = malloc(sizeof(DLL_Iterator));
    return iter;
}

void dll_iter_set(DLL_Iterator* iter, DLL* dll) {
    iter->node = dll->sentinel->next;
    iter->dll = dll;
}

int dll_iter_hasNext(DLL_Iterator* iter) {
    return iter->node != iter->dll->sentinel;
}

void dll_iter_next(DLL_Iterator* iter) {
    iter->node = iter->node->next;
}

void* dll_iter_data(DLL_Iterator* iter) {
    return iter->node->data;
}

void* dll_iter_remove(DLL_Iterator* iter) {

    if (iter->dll->size <= 0) {
        return NULL;
    }

    Node* node = iter->node;
    iter->node = node->prev;

    node->next->prev = node->prev;
    node->prev->next = node->next;

    void* temp = node->data;
    free(node);

    iter->dll->size -= 1;
    return temp;
}

void dll_iter_end(DLL_Iterator* iter) {
    free(iter);
}
