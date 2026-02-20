/*Problem: Given an array of integers, count the number of subarrays whose sum is equal to zero.

Input:
- First line: integer n
- Second line: n integers

Output:
- Print the count of subarrays having sum zero

Example:
Input:
6
1 -1 2 -2 3 -3

Output:
6

Explanation: A subarray is a continuous part of the array. For the input array 1 -1 2 -2 3 -3, the following subarrays have sum zero: [1, -1], [2, -2], [3, -3], [1, -1, 2, -2], [2, -2, 3, -3], and [1, -1, 2, -2, 3, -3]. Since there are 6 such subarrays, the output is 6.*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    long long key;
    int count;
    struct Node* next;
};

#define SIZE 10007

void insert(struct Node** hashTable, long long key) {
    int index = abs(key % SIZE);
    struct Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key) {
            temp->count++;
            return;
        }
        temp = temp->next;
    }
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->count = 1;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

int getCount(struct Node** hashTable, long long key) {
    int index = abs(key % SIZE);
    struct Node* temp = hashTable[index];
    while (temp) {
        if (temp->key == key) return temp->count;
        temp = temp->next;
    }
    return 0;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    long long* arr = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &arr[i]);
    }

    struct Node* hashTable[SIZE] = {NULL};
    long long currentSum = 0;
    long long zeroSumSubarrays = 0;

    insert(hashTable, 0);

    for (int i = 0; i < n; i++) {
        currentSum += arr[i];
        int existingCount = getCount(hashTable, currentSum);
        zeroSumSubarrays += existingCount;
        insert(hashTable, currentSum);
    }

    printf("%lld\n", zeroSumSubarrays);

    for (int i = 0; i < SIZE; i++) {
        struct Node* temp = hashTable[i];
        while (temp) {
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(arr);

    return 0;
}