#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Define Matrix and Thread Data Structures
typedef struct {
    int (*A)[N];
    int (*B)[P];
    int (*C)[P];
    int rowStart;
    int rowEnd;
    int n; // Number of columns in A and rows in B
    int p; // Number of columns in B
} ThreadData;

// Matrix Multiplication Function
void *multiply_matrices(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int (*A)[N] = data->A;
    int (*B)[P] = data->B;
    int (*C)[P] = data->C;
    int rowStart = data->rowStart;
    int rowEnd = data->rowEnd;
    int n = data->n;
    int p = data->p;

    for (int i = rowStart; i < rowEnd; i++) {
        for (int j = 0; j < p; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    pthread_exit(NULL);
}

// Main Function
int main() {
    int numThreads = 4; // Number of threads to use

    // Allocate result matrix
    int (*C)[P] = malloc(M * sizeof(*C));

    // Create threads
    pthread_t threads[numThreads];
    ThreadData threadData[numThreads];
    int rowsPerThread = M / numThreads;

    for (int i = 0; i < numThreads; i++) {
        threadData[i].A = A;
        threadData[i].B = B;
        threadData[i].C = C;
        threadData[i].rowStart = i * rowsPerThread;
        threadData[i].rowEnd = (i == numThreads - 1) ? M : (i + 1) * rowsPerThread;
        threadData[i].n = N;
        threadData[i].p = P;
        pthread_create(&threads[i], NULL, multiply_matrices, (void *)&threadData[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result matrix C
    printf("Result matrix C:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    free(C);

    return 0;
}
