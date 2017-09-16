//
// Created by Ido on 8/13/17.
//

#ifndef PROJECT_MATRIX_H
#define PROJECT_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

typedef struct matrix {
    int rows;
    int cols;
    char *p;
} MATRIX;

MATRIX *matNew(int rows, int cols);

void matDestroy(MATRIX * mat);

void matSet(MATRIX *mat, int x, int y, char val);

char matGet(MATRIX *mat, int x, int y);

#endif //PROJECT_MATRIX_H
