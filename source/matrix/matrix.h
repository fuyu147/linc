#pragma once

#include <stddef.h>
#include <stdio.h>

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

typedef struct
{
        double **items;
        size_t   row;
        size_t   col;
} Matrix;

double matrixGetItem(Matrix M, size_t r, size_t c);
void   matrixSetItem(Matrix M, size_t r, size_t c, double item);

Matrix matrixInitZeros(size_t rowNumber, size_t colNumber);
Matrix matrixInitWithDefaultValue(size_t rowNumber, size_t colNumber,
                                  double defaultValue);

Matrix matrixInitWithFunction(size_t rowNumber, size_t colNumber,
                              double (*fn)(size_t, size_t));

Matrix matrixAdd(Matrix M, Matrix N);
Matrix matrixMultiplyK(Matrix M, double k);
Matrix matrixMultiplyM(Matrix M, Matrix N);

// only allows matrices where row|col <= 3
// returns INT32_MAX if cannot do it
double matrixDeterminant(Matrix M);

// these 2 modifies the matrix passed
void matrixGauss(Matrix M);
void matrixGaussJordan(Matrix M);

Matrix matrixRank(Matrix M);
