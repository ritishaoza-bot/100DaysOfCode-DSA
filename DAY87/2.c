/*Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
Return the minimum integer k such that she can eat all the bananas within h hours.
 
Example 1:
Input: piles = [3,6,7,11], h = 8Output: 4
Example 2:
Input: piles = [30,11,23,4,20], h = 5Output: 30
Example 3:
Input: piles = [30,11,23,4,20], h = 6Output: 23
 
Constraints:
1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109.*/

#include <stdio.h>

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int max_val = 0;
    for (int i = 0; i < pilesSize; i++) {
        if (piles[i] > max_val) max_val = piles[i];
    }

    int left = 1, right = max_val;
    int result = max_val;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        long long total_hours = 0;

        for (int i = 0; i < pilesSize; i++) {
            total_hours += (piles[i] + mid - 1) / mid;
        }

        if (total_hours <= h) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return result;
}

int main() {
    int piles[] = {3, 6, 7, 11};
    int pilesSize = 4;
    int h = 8;

    int result = minEatingSpeed(piles, pilesSize, h);
    printf("Minimum eating speed k: %d\n", result);

    return 0;
}