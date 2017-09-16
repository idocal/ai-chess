//
// Created by Ido on 8/13/17.
//

#include "Matrix.h"

MATRIX *matNew(int rows, int cols) {
    MATRIX *mat = (MATRIX *) malloc(sizeof(MATRIX));
    if (mat == NULL) {
        return NULL;
    }

    // Create all cells of matrix
    size_t size_t_rows = (size_t ) rows;
    size_t size_t_cols = (size_t) cols;
    char *matCells = (char *) calloc(size_t_rows * size_t_cols, sizeof(char));
    if (matCells == NULL) {
        free(mat);
        return NULL;
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->p = matCells;

    return mat;
}

void matDestroy(MATRIX *mat) {
    free(mat->p);
    free(mat);
}

void matSet(MATRIX *mat, int x, int y, char val) {
    if (x >=0 && x <= 7 && y >= 0 && y <= 7) {
        mat->p[x * mat->rows + y] = val;
    }
}


char matGet(MATRIX *mat, int x, int y) {
    if (x >=0 && x <= 7 && y >= 0 && y <= 7) {
        return mat->p[x * mat->rows + y];
    }
    else {
        return '\0';
    }
}

