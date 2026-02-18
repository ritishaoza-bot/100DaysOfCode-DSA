/*Problem: Given an array of integers, rotate the array to the right by k positions.

Input:
- First line: integer n
- Second line: n integers
- Third line: integer k

Output:
- Print the rotated array

Example:
Input:
5
1 2 3 4 5
2

Output:
4 5 1 2 3*/

#include <stdio.h>
#include <stdlib.h>

void reverse(int* nums, int start, int end) {
    while (start < end) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
        start++;
        end--;
    }
}

void rotate(int* nums, int n, int k) {
    if (n == 0) return;
    k = k % n;
    if (k == 0) return;

    reverse(nums, 0, n - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, n - 1);
}

int main() {
    int n, k;

    if (scanf("%d", &n) != 1) return 0;

    int* nums = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    if (scanf("%d", &k) != 1) {
        free(nums);
        return 0;
    }

    rotate(nums, n, k);

    for (int i = 0; i < n; i++) {
        printf("%d%s", nums[i], (i == n - 1) ? "" : " ");
    }
    printf("\n");

    free(nums);
    return 0;
}