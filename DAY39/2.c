/*Given an integer array nums and an integer k, return the k most frequent elements. You may return the answer in any order.

 

Example 1:

Input: nums = [1,1,1,2,2,3], k = 2

Output: [1,2]

Example 2:

Input: nums = [1], k = 1

Output: [1]

Example 3:

Input: nums = [1,2,1,2,1,2,3,1,3,2], k = 2

Output: [1,2]

 

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
k is in the range [1, the number of unique elements in the array].
It is guaranteed that the answer is unique.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int val;
    int count;
} Element;

int compare(const void* a, const void* b) {
    return ((Element*)b)->count - ((Element*)a)->count;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int* freq = (int*)calloc(20001, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i] + 10000]++;
    }

    Element* elements = (Element*)malloc(20001 * sizeof(Element));
    int uniqueCount = 0;
    for (int i = 0; i < 20001; i++) {
        if (freq[i] > 0) {
            elements[uniqueCount].val = i - 10000;
            elements[uniqueCount].count = freq[i];
            uniqueCount++;
        }
    }

    qsort(elements, uniqueCount, sizeof(Element), compare);

    int* result = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        result[i] = elements[i].val;
    }

    free(freq);
    free(elements);
    *returnSize = k;
    return result;
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3};
    int k = 2;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int* result = topKFrequent(nums, numsSize, k, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("%d%s", result[i], (i == returnSize - 1) ? "" : ",");
    }
    printf("]\n");

    free(result);
    return 0;
}