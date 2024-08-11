#include <stdio.h>
#include "matrix.h"

void multiply_matrices(int A_matrix[M][N], int B_matrix[N][P], int result_matrix[M][P]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            result_matrix[i][j] = 0; // Initialize the element to 0 before summing

            for (int k = 0; k < N; k++) {
                result_matrix[i][j] += A_matrix[i][k] * B_matrix[k][j]; // Accumulate the products
            }
        }
    }
}
// Function to print any matrix with specified rows and columns
void print_matrix(int rows, int cols, int matrix[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int result_matrix[M][P];

    // Multiply matrices
    multiply_matrices(A, B, result_matrix);

    // Print matrix A
    printf("Matrix A:\n");
    print_matrix(M, N, A);  // MxN dimensions for matrix A

    // Print matrix B
    printf("Matrix B:\n");
    print_matrix(N, P, B);  // NxP dimensions for matrix B

    // Print result matrix
    printf("Matrix C (Result):\n");
    print_matrix(M, P, result_matrix);  // MxP dimensions for result matrix

    return 0;
}
