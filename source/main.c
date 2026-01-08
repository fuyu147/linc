#include "matrix/matrix.h"
#include <stddef.h>

double identity(size_t row, size_t col)
{
        return row == col ? 1 : 0;
}

int main()
{
        Matrix A = matrixInitZeros(4, 2);
        Matrix B = matrixInitZeros(2, 3);

        // Set values for A (4x2)
        matrixSetItem(A, 0, 0, 1);
        matrixSetItem(A, 0, 1, 2);
        matrixSetItem(A, 1, 0, 3);
        matrixSetItem(A, 1, 1, 4);
        matrixSetItem(A, 2, 0, 5);
        matrixSetItem(A, 2, 1, 6);
        matrixSetItem(A, 3, 0, 7);
        matrixSetItem(A, 3, 1, 8);

        // Set values for B (2x3)
        matrixSetItem(B, 0, 0, 1);
        matrixSetItem(B, 0, 1, 2);
        matrixSetItem(B, 0, 2, 3);
        matrixSetItem(B, 1, 0, 4);
        matrixSetItem(B, 1, 1, 5);
        matrixSetItem(B, 1, 2, 6);

        matrix_print(A);
        printf("---------------------\n");
        matrix_print(B);
        printf("---------------------\n");
        matrix_print(matrixMultiplyM(A, B));

        printf("---------------------\n");
        Matrix D = matrixInitZeros(3, 3);
        printf("det: [%g]\n", matrixDeterminant(D));

        // Example 1: 2x2 matrix [[1,2],[3,4]], det = -2
        Matrix E = matrixInitZeros(2, 2);
        matrixSetItem(E, 0, 0, 1);
        matrixSetItem(E, 0, 1, 2);
        matrixSetItem(E, 1, 0, 3);
        matrixSetItem(E, 1, 1, 4);
        printf("det of 2x2: %g (expected -2)\n", matrixDeterminant(E));

        // Example 2: 3x3 identity, det = 1
        Matrix F = matrixInitWithFunction(3, 3, identity);
        printf("det of 3x3: %g (expected 1)\n", matrixDeterminant(F));

        printf("---------------------\n");
        Matrix G = matrixInitZeros(3, 3);
        matrixSetItem(G, 0, 0, 1);
        matrixSetItem(G, 0, 1, 2);
        matrixSetItem(G, 0, 2, 3);
        matrixSetItem(G, 1, 0, 4);
        matrixSetItem(G, 1, 1, 5);
        matrixSetItem(G, 1, 2, 6);
        matrixSetItem(G, 2, 0, 7);
        matrixSetItem(G, 2, 1, 8);
        matrixSetItem(G, 2, 2, 9);
        printf("Original Matrix for Gauss:\n");
        matrix_print(G);
        matrixGauss(G);
        printf("After Gauss (Row Echelon Form):\n");
        matrix_print(G);

        printf("---------------------\n");
        Matrix H = matrixInitZeros(3, 3);
        matrixSetItem(H, 0, 0, 1);
        matrixSetItem(H, 0, 1, 2);
        matrixSetItem(H, 0, 2, 3);
        matrixSetItem(H, 1, 0, 4);
        matrixSetItem(H, 1, 1, 5);
        matrixSetItem(H, 1, 2, 6);
        matrixSetItem(H, 2, 0, 7);
        matrixSetItem(H, 2, 1, 8);
        matrixSetItem(H, 2, 2, 9);
        printf("Original Matrix for Gauss-Jordan:\n");
        matrix_print(H);
        matrixGaussJordan(H);
        printf("After Gauss-Jordan (Reduced Row Echelon Form):\n");
        matrix_print(H);

        return 0;
}
