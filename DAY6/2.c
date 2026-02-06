#include <stdio.h>
#include <stdlib.h>

void moveZeroes(int* nums, int numsSize) {
    int j = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != 0) {
            int temp = nums[j];
            nums[j] = nums[i];
            nums[i] = temp;
            j++;
        }
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int *nums = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    moveZeroes(nums, n);

    for (int i = 0; i < n; i++) {
        printf("%d%c", nums[i], (i == n - 1 ? '\n' : ' '));
    }

    free(nums);
    return 0;
}