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
    char *matCells = (char *) calloc(rows * cols, sizeof(char));
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
    mat->p[x * mat->rows + y] = val;
}

char matGet(MATRIX *mat, int x, int y) {
    return mat->p[x * mat->rows + y];
}

void matPrint(MATRIX *mat, char inverse) {
    if (inverse) {
        for (int i = 0; i < mat->rows; i++) {
            for (int j = 0; j < mat->cols; j++) {
                char cell = matGet(mat, i, j);
                printf("%d ", cell);
            }
            printf("\n");
        }
    }
    else { // inverse
        for (int i = (mat->rows - 1); i >= 0; i--) {
            for (int j = 0; j < mat->cols; j++) {
                char cell = matGet(mat, i, j);
                printf("%d ", cell);
            }
            printf("\n");
        }
    }
}