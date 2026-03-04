/*Problem: Implement push and pop operations on a stack and verify stack operations.

Input:
- First line: integer n
- Second line: n integers to push
- Third line: integer m (number of pops)

Output:
- Print remaining stack elements from top to bottom

Example:
Input:
5
10 20 30 40 50
2

Output:
30 20 10*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m;
    
    if (scanf("%d", &n) != 1) return 0;
    
    int *stack = (int *)malloc(n * sizeof(int));
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        stack[++top] = val;
    }
    
    scanf("%d", &m);
    
    for (int i = 0; i < m; i++) {
        if (top >= 0) {
            top--;
        }
    }
    
    for (int i = top; i >= 0; i--) {
        printf("%d", stack[i]);
        if (i > 0) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(stack);
    return 0;
}