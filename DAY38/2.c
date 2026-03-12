/*You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the max sliding window.
 
Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3Output: [3,3,5,5,6,7]Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:
Input: nums = [1], k = 1Output: [1]
 
Constraints:
1 <= nums.length <= 105
-104 <= nums[i] <= 104
1 <= k <= nums.length.*/

#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int head = 0, tail = 0;
    int idx = 0;

    for (int i = 0; i < numsSize; i++) {
        while (head < tail && nums[deque[tail - 1]] <= nums[i]) {
            tail--;
        }
        deque[tail++] = i;
        if (deque[head] <= i - k) {
            head++;
        }
        if (i >= k - 1) {
            result[idx++] = nums[deque[head]];
        }
    }

    *returnSize = idx;
    free(deque);
    return result;
}

int main() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;

    int* result = maxSlidingWindow(nums, numsSize, k, &returnSize);

    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("%d%s", result[i], (i == returnSize - 1) ? "" : ", ");
    }
    printf("]\n");

    free(result);
    return 0;
}