//
// Created by okleinfeld on 5/18/2017.
//

#include "SPArrayList.h"

SPArrayList* spArrayListCreate(int maxSize){

    if (maxSize <= 0){ // Maximum size of array is non-negative
        return NULL;
    }

    SPArrayList *arrayListPointer = (SPArrayList *) malloc(sizeof(SPArrayList));
    if (arrayListPointer == NULL){
        return NULL;
    }

    arrayListPointer->elements = (int *) calloc(maxSize, sizeof(int));
    if (arrayListPointer->elements == NULL){
        free(arrayListPointer);
        return NULL;
    }

    arrayListPointer->actualSize = 0;
    arrayListPointer->maxSize = maxSize;
    return arrayListPointer;
}

SPArrayList* spArrayListCopy(SPArrayList* src){

    if (src == NULL){ // If passed NULL argument
        return NULL;
    }

    int srcMaxSize = src->maxSize;
    int srcActualSize = src->actualSize;

    SPArrayList *cpyArrayList = spArrayListCreate(srcMaxSize);
    if (cpyArrayList == NULL){
        return NULL;
    }

    // Iterate through each cell in source array and copy to new one
    for (int i = 0; i < srcActualSize; i++){
        *(cpyArrayList->elements + i) = *(src->elements + i);
    }
    cpyArrayList->actualSize = srcActualSize;

    return cpyArrayList;
}

void spArrayListDestroy(SPArrayList* src){
    if (src != NULL){
        free(src->elements);
        free(src);
    }
}

SP_ARRAY_LIST_MESSAGE spArrayListClear(SPArrayList* src){

    if (src == NULL){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }

    // Iterate through array and fill with 0s
    for (int i = 0; i < src->actualSize; i++){
        (src->elements)[i] = 0;
    }
    src->actualSize = 0;

    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddAt(SPArrayList* src, int elem, int index){

    if (src == NULL || index < 0 || index > src->actualSize){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }

    if (src->actualSize == src->maxSize){
        return SP_ARRAY_LIST_FULL;
    }

    int *arrayPointer = src->elements + src->actualSize;
    int numIter = src->actualSize - index;

    // Iterate through array until index and move exceeding elements
    for (int i = 0; i < numIter; i++){
        *arrayPointer = *(arrayPointer - 1);
        arrayPointer--;
    }
    *arrayPointer = elem;
    src->actualSize += 1;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListAddFirst(SPArrayList* src, int elem){
    return spArrayListAddAt(src, elem, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListAddLast(SPArrayList* src, int elem){
    return spArrayListAddAt(src, elem, src->actualSize);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveAt(SPArrayList* src, int index){

    if (src == NULL || index < 0 || index >= src->actualSize){
        return SP_ARRAY_LIST_INVALID_ARGUMENT;
    }

    if (src->actualSize == 0){
        return SP_ARRAY_LIST_EMPTY;
    }

    int *arrayPointer = src->elements + index;
    int numIter = src->actualSize -(index+1);

    // Iterate through array until index and move exceeding elements
    for (int i = 0; i < numIter; i++){
        *arrayPointer = *(arrayPointer + 1);
        arrayPointer++;
    }

    src->actualSize -= 1;
    return SP_ARRAY_LIST_SUCCESS;
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveFirst(SPArrayList* src){
    return spArrayListRemoveAt(src, 0);
}

SP_ARRAY_LIST_MESSAGE spArrayListRemoveLast(SPArrayList* src){
    return spArrayListRemoveAt(src, src->actualSize-1);
}

int spArrayListGetAt(SPArrayList* src, int index){
    if (src == NULL || index < 0 || index > src->actualSize -1){
        return -99;
    }
    return *(src->elements + index);
}

int spArrayListGetFirst(SPArrayList* src){
    return spArrayListGetAt(src, 0);
}

int spArrayListGetLast(SPArrayList* src){
    return spArrayListGetAt(src, src->actualSize -1);
}

int spArrayListMaxCapacity(SPArrayList* src){
    if (src == NULL){
        return -99;
    }
    return src->maxSize;
}

int spArrayListSize(SPArrayList* src){
    if (src == NULL){
        return -99;
    }
    return src->actualSize;
}

bool spArrayListIsFull(SPArrayList* src){
    if (src == NULL || src->actualSize < src->maxSize){
        return false;
    }
    else{
        return true;
    }
}

bool spArrayListIsEmpty(SPArrayList* src){
    if (src == NULL || src->actualSize > 0){
        return false;
    }
    else{
        return true;
    }
}
