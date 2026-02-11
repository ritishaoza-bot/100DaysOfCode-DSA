/*Given a 2D integer array matrix, return the transpose of matrix.

The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.



 

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[1,4,7],[2,5,8],[3,6,9]]
Example 2:

Input: matrix = [[1,2,3],[4,5,6]]
Output: [[1,4],[2,5],[3,6]]
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
-109 <= matrix[i][j] <= 109*/

#include <stdio.h>
#include <stdlib.h>

int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int m = matrixSize;
    int n = matrixColSize[0];

    *returnSize = n;
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    int** result = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = m;
        result[i] = (int*)malloc(m * sizeof(int));
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

int main() {
    int rows = 2;
    int cols = 3;
    
    int* matrix_data[] = {
        (int[]){1, 2, 3},
        (int[]){4, 5, 6}
    };
    
    int** matrix = matrix_data;
    int matrixColSize[] = {cols, cols};
    int returnSize;
    int* returnColumnSizes;

    int** result = transpose(matrix, rows, matrixColSize, &returnSize, &returnColumnSizes);

    printf("Transposed Matrix:\n");
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < returnSize; i++) free(result[i]);
    free(result);
    free(returnColumnSizes);

    return 0;
}