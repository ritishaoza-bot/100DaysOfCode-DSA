#include <stdio.h>

// The LeetCode function
void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int i = m - 1;
    int j = n - 1;
    int k = m + n - 1;

    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i--];
        } else {
            nums1[k] = nums2[j--];
        }
        k--;
    }

    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

int main() {
    // Example 1 setup
    int nums1[6] = {1, 2, 3, 0, 0, 0};
    int m = 3;
    int nums2[3] = {2, 5, 6};
    int n = 3;

    printf("Before merge: ");
    for (int i = 0; i < m + n; i++) printf("%d ", nums1[i]);
    
    // Call the function
    merge(nums1, 6, m, nums2, 3, n);

    printf("\nAfter merge:  ");
    for (int i = 0; i < m + n; i++) {
        printf("%d ", nums1[i]);
    }
    printf("\n");

    return 0;
}