#include "matrix.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

bool isSquare(Matrix M)
{
        return M.row == M.col;
}

bool isSameSizes(Matrix M, Matrix N)
{
        return M.row == N.row && M.col == N.col;
}

double matrixGetItem(Matrix M, size_t r, size_t c)
{
        return M.items[r][c];
}

void matrixSetItem(Matrix M, size_t r, size_t c, double item)
{
        M.items[r][c] = item;
}

Matrix matrixInitZeros(size_t rowNumber, size_t colNumber)
{
        Matrix M = {};
        M.row    = rowNumber;
        M.col    = colNumber;
        M.items  = (double **)malloc(rowNumber * sizeof(double *));
        for (size_t i = 0; i < rowNumber; i++)
        {
                M.items[i] = (double *)calloc(colNumber, sizeof(double));
        }
        return M;
}

Matrix matrixInitWithDefaultValue(size_t rowNumber, size_t colNumber,
                                  double defaultValue)
{
        Matrix E = matrixInitZeros(rowNumber, colNumber);

        for (int c = 0; c < colNumber; c++)
        {
                for (int r = 0; r < rowNumber; r++)
                {
                        matrixSetItem(E, r, c, defaultValue);
                }
        }

        return E;
}

Matrix matrixInitWithFunction(size_t rowNumber, size_t colNumber,
                              double (*fn)(size_t, size_t))
{
        Matrix F = matrixInitZeros(rowNumber, colNumber);

        for (int c = 0; c < colNumber; c++)
        {
                for (int r = 0; r < rowNumber; r++)
                {
                        matrixSetItem(F, r, c, fn(r, c));
                }
        }

        return F;
}

Matrix matrixAdd(Matrix M, Matrix n)
{
        Matrix Z = {};
        if (!isSameSizes(M, n))
                return Z;

        Z = matrixInitZeros(M.row, M.col);

        for (int r = 0; r < Z.row; r++)
        {
                for (int c = 0; c < Z.col; c++)
                {
                        matrixSetItem(Z, r, c,
                                      matrixGetItem(M, r, c) +
                                          matrixGetItem(n, r, c));
                }
        }

        return Z;
}

Matrix matrixMultiplyK(Matrix M, double k)
{
        Matrix z = matrixInitZeros(M.row, M.col);

        for (int r = 0; r < z.row; r++)
        {
                for (int c = 0; c < z.col; c++)
                {
                        matrixSetItem(z, r, c, matrixGetItem(M, r, c) * k);
                }
        }

        return z;
}

Matrix matrixMultiplyM(Matrix M, Matrix N)
{
        Matrix z = {};

        if (M.col != N.row)
                return z;

        size_t n = M.col;

        z = matrixInitZeros(M.row, N.col);

        for (int i = 0; i < M.row; i++)
                for (int j = 0; j < N.col; j++)
                {
                        // c_ij
                        double sum = 0;
                        for (int k = 0; k < n; k++)
                        {
                                sum += matrixGetItem(M, i, k) *
                                    matrixGetItem(N, k, j);
                        }
                        matrixSetItem(z, i, j, sum);
                }

        return z;
}

double matrixDeterminant(Matrix M)
{
        Matrix Z = {};
        if (!isSquare(M) || M.row > 3 || M.col > 3)
                return INT32_MAX;

        if (M.row == 2)
        {
                double a = matrixGetItem(M, 0, 0);
                double b = matrixGetItem(M, 0, 1);
                double c = matrixGetItem(M, 1, 0);
                double d = matrixGetItem(M, 1, 1);

                return a * d - b * c;
        }
        else if (M.row == 3)
        {
                double a = matrixGetItem(M, 0, 0);
                double b = matrixGetItem(M, 0, 1);
                double c = matrixGetItem(M, 0, 2);
                double d = matrixGetItem(M, 1, 0);
                double e = matrixGetItem(M, 1, 1);
                double f = matrixGetItem(M, 1, 2);
                double g = matrixGetItem(M, 2, 0);
                double h = matrixGetItem(M, 2, 1);
                double i = matrixGetItem(M, 2, 2);

                return a * e * i + b * f * g + c * d * h - c * e * g -
                    b * d * i - a * f * h;
        }
        else
        {
                return INT32_MAX;
        }
}

void matrixGauss(Matrix M)
{
        size_t min_dim = (M.row < M.col) ? M.row : M.col;
        for (size_t k = 0; k < min_dim; k++)
        {
                // Find pivot row
                size_t pivot_row = k;
                for (size_t i = k; i < M.row; i++)
                {
                        if (M.items[i][k] != 0.0)
                        {
                                pivot_row = i;
                                break;
                        }
                }

                if (M.items[pivot_row][k] == 0.0)
                {
                        continue;
                }

                // Swap rows k and pivot_row
                if (pivot_row != k)
                {
                        double *temp       = M.items[k];
                        M.items[k]         = M.items[pivot_row];
                        M.items[pivot_row] = temp;
                }

                // Eliminate below the pivot
                for (size_t j = k + 1; j < M.row; j++)
                {
                        if (M.items[j][k] != 0.0)
                        {
                                double factor = M.items[j][k] / M.items[k][k];
                                for (size_t c = k; c < M.col; c++)
                                {
                                        M.items[j][c] -= factor * M.items[k][c];
                                }
                        }
                }
        }
}

void matrixGaussJordan(Matrix M)
{
        size_t min_dim = (M.row < M.col) ? M.row : M.col;
        for (size_t k = 0; k < min_dim; k++)
        {
                // Find pivot row
                size_t pivot_row = k;
                for (size_t i = k; i < M.row; i++)
                {
                        if (M.items[i][k] != 0.0)
                        {
                                pivot_row = i;
                                break;
                        }
                }
                if (M.items[pivot_row][k] == 0.0)
                {
                        continue;
                }
                // Swap rows k and pivot_row
                if (pivot_row != k)
                {
                        double *temp       = M.items[k];
                        M.items[k]         = M.items[pivot_row];
                        M.items[pivot_row] = temp;
                }
                // Make pivot 1
                double pivot = M.items[k][k];
                for (size_t c = 0; c < M.col; c++)
                {
                        M.items[k][c] /= pivot;
                }
                // Eliminate in all other rows
                for (size_t j = 0; j < M.row; j++)
                {
                        if (j == k)
                                continue;
                        double factor = M.items[j][k];
                        for (size_t c = 0; c < M.col; c++)
                        {
                                M.items[j][c] -= factor * M.items[k][c];
                        }
                }
        }
}

Matrix matrixRank(Matrix M)
{
        Matrix Z = {};
        return Z;
}
