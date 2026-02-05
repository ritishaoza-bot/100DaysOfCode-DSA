#include <stdio.h>
#include <stdlib.h>

int main() {
    int p, q;

    // --- Input for Server 1 ---
    if (scanf("%d", &p) != 1) return 1;
    int* log1 = (int*)malloc(p * sizeof(int));
    for (int i = 0; i < p; i++) {
        scanf("%d", &log1[i]);
    }

    // --- Input for Server 2 ---
    if (scanf("%d", &q) != 1) return 1;
    int* log2 = (int*)malloc(q * sizeof(int));
    for (int i = 0; i < q; i++) {
        scanf("%d", &log2[i]);
    }

    // --- Merging Process ---
    int i = 0; // Pointer for log1
    int j = 0; // Pointer for log2

    // Compare and print the smaller value until one log is exhausted
    while (i < p && j < q) {
        if (log1[i] < log2[j]) {
            printf("%d ", log1[i]);
            i++;
        } else {
            printf("%d ", log2[j]);
            j++;
        }
    }

    // Print remaining elements from log1 (if any)
    while (i < p) {
        printf("%d ", log1[i]);
        i++;
    }

    // Print remaining elements from log2 (if any)
    while (j < q) {
        printf("%d ", log2[j]);
        j++;
    }

    printf("\n");

    // Clean up memory
    free(log1);
    free(log2);

    return 0;
}