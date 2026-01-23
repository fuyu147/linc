#include "matrix.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

bool isSquare(LincMatrix M)
{
        return M.row == M.col;
}

bool isSameSizes(LincMatrix M, LincMatrix N)
{
        return M.row == N.row && M.col == N.col;
}

double matrixGetItem(LincMatrix M, size_t r, size_t c)
{
        return M.items[r][c];
}

void matrixSetItem(LincMatrix M, size_t r, size_t c, double item)
{
        M.items[r][c] = item;
}

LincMatrix matrixInitZeros(size_t rowNumber, size_t colNumber)
{
        LincMatrix M = {};
        M.row        = rowNumber;
        M.col        = colNumber;
        M.items      = (double **)malloc(rowNumber * sizeof(double *));
        for (size_t i = 0; i < rowNumber; i++)
        {
                M.items[i] = (double *)calloc(colNumber, sizeof(double));
        }
        return M;
}

LincMatrix matrixInitWithDefaultValue(size_t rowNumber, size_t colNumber,
                                      double defaultValue)
{
        LincMatrix E = matrixInitZeros(rowNumber, colNumber);

        for (int c = 0; c < colNumber; c++)
        {
                for (int r = 0; r < rowNumber; r++)
                {
                        matrixSetItem(E, r, c, defaultValue);
                }
        }

        return E;
}

LincMatrix matrixInitWithFunction(size_t rowNumber, size_t colNumber,
                                  double (*fn)(size_t, size_t))
{
        LincMatrix F = matrixInitZeros(rowNumber, colNumber);

        for (int c = 0; c < colNumber; c++)
        {
                for (int r = 0; r < rowNumber; r++)
                {
                        matrixSetItem(F, r, c, fn(r, c));
                }
        }

        return F;
}

LincMatrix matrixAdd(LincMatrix M, LincMatrix n)
{
        LincMatrix Z = {};
        if (!isSameSizes(M, n)) return Z;

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

LincMatrix matrixMultiplyK(LincMatrix M, double k)
{
        LincMatrix z = matrixInitZeros(M.row, M.col);

        for (int r = 0; r < z.row; r++)
        {
                for (int c = 0; c < z.col; c++)
                {
                        matrixSetItem(z, r, c, matrixGetItem(M, r, c) * k);
                }
        }

        return z;
}

LincMatrix matrixMultiplyM(LincMatrix M, LincMatrix N)
{
        LincMatrix z = {};

        if (M.col != N.row) return z;

        size_t n = M.col;

        z        = matrixInitZeros(M.row, N.col);

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

double matrixDeterminant(LincMatrix M)
{
        LincMatrix Z = {};
        if (!isSquare(M) || M.row > 3 || M.col > 3) return INT32_MAX;

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

void matrixGauss(LincMatrix M)
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

void matrixGaussJordan(LincMatrix M)
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
                        if (j == k) continue;
                        double factor = M.items[j][k];
                        for (size_t c = 0; c < M.col; c++)
                        {
                                M.items[j][c] -= factor * M.items[k][c];
                        }
                }
        }
}

int matrixRank(LincMatrix M)
{
        LincMatrix Z = {};

        // how the hell should i find the rank of a matrix superior to 2x2...

        if (M.row == 2 && M.col == 2)
        {
                int isEmpty = 1;
                for (int r = 0; r < Z.row; r++)
                {
                        for (int c = 0; c < Z.col; c++)
                        {
                                if (matrixGetItem(M, r, c) != 0)
                                {
                                        isEmpty = 0;
                                }
                        }
                }
                if (isEmpty)
                        return 0;
                else if (matrixDeterminant(M) == 0)
                        return 1;
                else
                        return 2;
        }

        return 0;
}

VectorList matrixToColumnVector(LincMatrix M)
{
        VectorList vlist = {};

        for (int c = 0; c < M.col; c++)
        {
                Vector vcol = {};
                for (int r = 0; r < M.row; r++)
                {
                        vector_append(vcol, matrixGetItem(M, r, c));
                }
                vector_append(vlist, vcol);
        }

        return vlist;
}

VectorList matrixToRowVector(LincMatrix M)
{
        VectorList vlist = {};

        for (int r = 0; r < M.row; r++)
        {
                Vector vrow = {};
                for (int c = 0; c < M.col; c++)
                {
                        vector_append(vrow, matrixGetItem(M, r, c));
                }
                vector_append(vlist, vrow);
        }

        return vlist;
}
