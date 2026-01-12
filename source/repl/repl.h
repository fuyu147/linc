#pragma once

#include <stddef.h>

#include "../matrix/matrix.h"
#include "../vector/vector.h"

// syntax for vector : {1, 2, 3, ...}
// syntax for matrix : [[1, 2], [1, 2]]
//
// prefix to call vector operators/functions: v
// prefix to call matrix operators/functions: m
//
// operators for vectors:
//      a v- b -> substraction                  (vec vec -> vec)
//      a v+ b -> addition                      (vec vec -> vec)
//      a v* b -> cross product                 (vec vec -> vec)
//      a v. b -> dot product                   (vec vec -> double)
//      a v~ b -> element-wise product          (vec vec -> vec)
//
// operators for matrices:
//      A m- B -> substraction                  (mat mat -> mat)
//      A m+ B -> addition                      (mat mat -> mat)
//      A m* B -> multiplication by scalar      (mat k -> mat | k mat -> mat)
//      A m. B -> multiplication with matrix    (mat mat -> mat)
//
// functions for matrices:
//      mDET(A)                                 (where A is Matrix and returns a
//      scalar) mGAUSS(A)                               (where A is Matrix and
//      returns a matrix) mRREF(A)                                (where A is
//      Matrix and returns a matrix)

typedef enum Token
{
        // to call matrix functions
        TOKEN_matrixPrefix = 'm',
        TOKEN_vectorPrefix = 'v',

        TOKEN_ParenOpen = '(', // X(A) where X is either D, G or R (like above)
                               // and A is a matrix
        TOKEN_ParenClose  = ')',

        TOKEN_vectorOpen  = '{', // vector has syntax: {1, 2, 3, ..., n}
        TOKEN_vectorClose = '}',

        TOKEN_matrixOpen =
            '[', // matrix has syntax: [[1, 2, 3], [1, 2, 3], ...]
        TOKEN_matrixClose   = ']',

        TOKEN_operatorMinus = '-', // available for matrix (m-) & vector (v-)
        TOKEN_operatorPlus  = '+', // available for matrix (m+) & vector (v+)
        TOKEN_operatorStar  = '*', // available for matrix (m*) & vector (v*)
        TOKEN_operatorDot   = '.', // available for matrix (m.) & vector (v.)
        TOKEN_operatorTilde = '~', // available for vector (v~)
} Token;

typedef enum Operator
{
        OPERATOR_minus,
        OPERATOR_plus,
        OPERATOR_star,
        OPERATOR_dot,
        OPERATOR_tilde
} Operator;

typedef enum Function
{
        FUNCTION_det,
        FUNCTION_gauss,
        FUNCTION_rref
} Function;

typedef enum ArgumentKind
{
        ARGUMENT_KIND_matrix,
        ARGUMENT_KIND_vector,
        ARGUMENT_KIND_operator,
        ARGUMENT_KIND_functionMatrix,
} ArgumentKind;

typedef struct ReplArgument
{
        const char  *item;
        ArgumentKind kind;
} ReplArgument;

def_vector_t(ReplArgument, ReplArguments);

typedef struct ParseResult
{
        enum
        {
                RESULT_MATRIX,
                RESULT_VECTOR,
                RESULT_DOUBLE
        } type;
        union {
                Matrix m;
                Vector v;
                double d;
        } value;
} ParseResult;

// this returns 0 on success, 1 on failure
int handleLine(const char *str, int strLen);

// these returns 0 on success, 1 on failure
int parseResultMatrixArgument(const char *str, Matrix *out);
int parseResultVectorArgument(const char *str, Vector *out);
int parseResultOperatorArgument(char op, enum Operator *out);
int parseResultFunctionsArgument(const char *str, ParseResult *result);
