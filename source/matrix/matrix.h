#pragma once

#include <stddef.h>
#include <stdio.h>

#include "../vector/vector.h"

#define matrix_print(m)                                                        \
        do                                                                     \
        {                                                                      \
                for (size_t r = 0; r < m.row; r++)                             \
                {                                                              \
                        for (size_t c = 0; c < m.col; c++)                     \
                        {                                                      \
                                printf("%5g", m.items[r][c]);                  \
                        }                                                      \
                        printf("\n");                                          \
                }                                                              \
        } while (0)

int matrixExample();

typedef struct LincLincMatrix
{
        double **items;
        size_t   row;
        size_t   col;
} LincMatrix;

double matrixGetItem(LincMatrix M, size_t r, size_t c);
void   matrixSetItem(LincMatrix M, size_t r, size_t c, double item);

LincMatrix matrixInitZeros(size_t rowNumber, size_t colNumber);
LincMatrix matrixInitWithDefaultValue(size_t rowNumber, size_t colNumber,
                                      double defaultValue);

LincMatrix matrixInitWithFunction(size_t rowNumber, size_t colNumber,
                                  double (*fn)(size_t, size_t));

LincMatrix matrixAdd(LincMatrix M, LincMatrix N);
LincMatrix matrixMultiplyK(LincMatrix M, double k);
LincMatrix matrixMultiplyM(LincMatrix M, LincMatrix N);

// currently only allows matrices where row|col <= 3
// returns INT32_MAX if cannot do it
double matrixDeterminant(LincMatrix M);

// these 2 modifies the data of the matrix passed
void matrixGauss(LincMatrix M);
void matrixGaussJordan(LincMatrix M);

// returns the rank of the matrix
// or -1 if it fails
int matrixRank(LincMatrix M);

def_vector_t(Vector, VectorList);

VectorList matrixToColumnVector(LincMatrix M);
VectorList matrixToRowVector(LincMatrix M);
