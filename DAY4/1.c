/*
Sample Test Cases:

Input 1:
4
3 2 2 3
3

Output 1:
2
2 2


Input 2:
8
0 1 2 2 3 0 4 2
2

Output 2:
5
0 1 0 4 3


Input 3:
5
1 1 1 1 1
1

Output 3:
0
*/

#include <stdio.h>

int removeElement(int nums[], int n, int val) {
    int k = 0;   // index for elements not equal to val

    for (int i = 0; i < n; i++) {
        if (nums[i] != val) {
            nums[k] = nums[i];
            k++;
        }
    }
    return k;
}

int main() {
    int n, val;
    scanf("%d", &n);

    int nums[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &nums[i]);
    }

    scanf("%d", &val);

    int k = removeElement(nums, n, val);

    printf("%d\n", k);
    for (int i = 0; i < k; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}