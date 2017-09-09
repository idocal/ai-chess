//
// Created by Ido on 9/9/17.
//

#include "GenericWindow.h"

GenericWindow *createGenericWindow(int(*drawFunc)(GenericWindow*)) {
    GenericWindow *genericWindow = calloc(sizeof(GenericWindow), sizeof(char));
    if (genericWindow == NULL) return NULL;

    (*drawFunc)(genericWindow);
    return genericWindow;
}