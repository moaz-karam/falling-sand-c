#include <stdlib.h>
#include <string.h>

#include "./array_list.h"

ArrayList* ArrayList_create(unsigned int typeSize) {
    ArrayList* al = malloc(sizeof(ArrayList));

    al->size = 0;
    al->length = 4;
    al->typeSize = typeSize;

    al->data = malloc(typeSize * al->length);
    return al;
}

ArrayList* ArrayList_createSized(unsigned int typeSize, unsigned int length) {

    ArrayList* al = malloc(sizeof(ArrayList));
    al->size = length;
    al->length = length;
    al->typeSize = typeSize;
    
    al->data = malloc(typeSize * al->length);
    return al;
}









void ArrayList_resizeUp(ArrayList* al) {
    if ((float)al->size / (float)al->length < 1) {
        return;
    }
    al->length *= 2;
    al->data = realloc(al->data, al->typeSize * al->length);
}

void ArrayList_resizeDown(ArrayList* al) {
    if (al->length < 16 || (float)al->size / (float)al->length > 0.25) {
       return;
    }
    al->length *= 0.5;
    al->data = realloc(al->data, al->typeSize * al->length);
}


void ArrayList_push(ArrayList* al, void* element) {
    ArrayList_resizeUp(al);
    memcpy(al->data + (al->size * al->typeSize), element, al->typeSize);
    al->size += 1;
}

void ArrayList_pop(ArrayList* al, void* element) {
    ArrayList_resizeDown(al);
    
    memcpy(element, al->data + ((al->size - 1) * al->typeSize), al->typeSize);
    al->size -= 1;
}







void ArrayList_set(ArrayList* al, unsigned int index, void* element) {
    memcpy(al->data + (index * al->typeSize), element, al->typeSize);
}

void ArrayList_get(ArrayList* al, unsigned int index, void* element) {
    memcpy(element, al->data + (index * al->typeSize), al->typeSize);
}

void* ArrayList_getAddressOfIndex(ArrayList* al, unsigned int index) {
    return al->data + (index * al->typeSize);
}



void ArrayList_end(ArrayList* al) {
    free(al->data);
    free(al);
}