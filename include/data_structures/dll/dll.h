#ifndef DLL_H
#define DLL_H


typedef struct Node {
    void* data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* sentinel;
    int size;
} DLL;

typedef struct {
    Node* node;
    DLL* dll;
} DLL_Iterator;

DLL* dll_create();
void dll_addLast(DLL* dll, void* data);
void dll_addFirst(DLL* dll, void* data);
void* dll_getLast(DLL* dll);
void* dll_getFirst(DLL* dll);
void* dll_get(DLL* dll, int i);
void* dll_removeLast(DLL* dll);
void* dll_removeFirst(DLL* dll);
void* dll_remove(DLL* dll, void* data);
void dll_end(DLL* dll);

DLL_Iterator* dll_iter_create();
void dll_iter_set(DLL_Iterator* iter, DLL* dll);
int dll_iter_hasNext(DLL_Iterator* iter);
void dll_iter_next(DLL_Iterator* iter);
void* dll_iter_data(DLL_Iterator* iter);
void* dll_iter_remove(DLL_Iterator* iter);
void dll_iter_end(DLL_Iterator* iter);



#endif