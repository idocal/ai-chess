//
// Created by Ido on 8/13/17.
//

#ifndef PROJECT_MATRIX_H
#define PROJECT_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

/**
 * a matrix interface to efficiently represent and manage game board opertaion
 */

typedef struct matrix {
    int rows;
    int cols;
    char *p;
} MATRIX;

/**
 * constructor for a matrix object.
 * values are set to zero as default
 *
 * @param rows
 * @param cols
 * @return a pointer to the new allocated matrix object
 */

MATRIX *matNew(int rows, int cols);

/**
 * a destructor for a matrix object
 * frees all the matrix associated memory
 *
 * @param mat
 */
void matDestroy(MATRIX * mat);

/**
 * interface for setting a value in a matrix cell
 *
 * @param mat
 * @param x
 * @param y
 * @param val
 */

void matSet(MATRIX *mat, int x, int y, char val);

/**
 * interface for reaching a value saved in a matrix cell
 * @param mat
 * @param x
 * @param y
 * @return
 */

char matGet(MATRIX *mat, int x, int y);

#endif //PROJECT_MATRIX_H
