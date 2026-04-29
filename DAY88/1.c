/*Problem Statement
Given n stalls located at different positions along a straight line and k cows, place the cows in the stalls such that the minimum distance between any two cows is maximized.

This is an optimization problem where binary search on the answer is required.

Input Format
n k
n space-separated integers representing stall positions

Output Format
Print the maximum possible minimum distance between any two cows.

Sample Input
5 3
1 2 8 4 9

Sample Output
3

Explanation
Cows can be placed at positions 1, 4, and 8. The minimum distance between any two cows is 3, which is the maximum possible.*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int canPlaceCows(int* stalls, int n, int k, int minDist) {
    int count = 1;
    int lastPos = stalls[0];

    for (int i = 1; i < n; i++) {
        if (stalls[i] - lastPos >= minDist) {
            count++;
            lastPos = stalls[i];
            if (count >= k) return 1;
        }
    }
    return 0;
}

int solve() {
    int n, k;
    if (scanf("%d %d", &n, &k) != 2) return 0;

    int* stalls = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &stalls[i]);
    }

    qsort(stalls, n, sizeof(int), compare);

    int low = 1;
    int high = stalls[n - 1] - stalls[0];
    int result = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canPlaceCows(stalls, n, k, mid)) {
            result = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    free(stalls);
    return result;
}

int main() {
    printf("%d\n", solve());
    return 0;
}