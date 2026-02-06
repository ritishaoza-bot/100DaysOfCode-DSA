#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    int *arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    if (n == 1) {
        printf("%d\n", arr[0]);
        free(arr);
        return 0;
    }

    int j = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] != arr[j]) {
            j++;
            arr[j] = arr[i];
        }
    }

    for (int i = 0; i <= j; i++) {
        printf("%d%c", arr[i], (i == j ? '\n' : ' '));
    }

    free(arr);
    return 0;
}