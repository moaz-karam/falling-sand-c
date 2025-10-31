#ifndef ARRAY_LIST
#define ARRAY_LIST

typedef struct {
    void* data;
    unsigned int size;
    unsigned int length;

    unsigned int typeSize;
} ArrayList;

// sets size to 0 and length to 4
ArrayList* ArrayList_create(unsigned int typeSize);

// sets length and size to the parameter length
ArrayList* ArrayList_createSized(unsigned int typeSize, unsigned int length);




// sets al->data[size] to element
// and increase size by 1
// resizes the array
void ArrayList_push(ArrayList* al, void* element);

// sets element to al->data[size - 1]
// and decrease size by -1
// resizes the array
void ArrayList_pop(ArrayList* al, void* element);




// sets al->data[index] to element
// doesn't resize the array
void ArrayList_set(ArrayList* al, unsigned int index, void* element);

// sets the element to al->data[index]
// doesn't resize the array
void ArrayList_get(ArrayList* al, unsigned int index, void* element);


// gets the address of a given index in the arrayList
void* ArrayList_getAddressOfIndex(ArrayList* al, unsigned int index);


// frees used memory
void ArrayList_end(ArrayList* al);

#endif