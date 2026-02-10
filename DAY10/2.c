/*Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must appear as many times as it shows in both arrays and you may return the result in any order.

 

Example 1:

Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
Example 2:

Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
Explanation: [9,4] is also accepted.
 

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 1000
 */

#include <stdio.h>
#include <stdlib.h>

int* intersect(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    int counts[1001] = {0};
    for (int i = 0; i < nums1Size; i++) {
        counts[nums1[i]]++;
    }

    int minSize = nums1Size < nums2Size ? nums1Size : nums2Size;
    int* result = (int*)malloc(minSize * sizeof(int));
    int count = 0;

    for (int i = 0; i < nums2Size; i++) {
        if (counts[nums2[i]] > 0) {
            result[count++] = nums2[i];
            counts[nums2[i]]--;
        }
    }

    *returnSize = count;
    return result;
}

int main() {
    int nums1[] = {4, 9, 5};
    int nums2[] = {9, 4, 9, 8, 4};
    int returnSize;
    
    int* result = intersect(nums1, 3, nums2, 5, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("%d%s", result[i], i == returnSize - 1 ? "" : ",");
    }
    printf("]\n");

    free(result);
    return 0;
}