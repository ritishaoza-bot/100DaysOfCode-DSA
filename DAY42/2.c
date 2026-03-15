/*The median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value, and the median is the mean of the two middle values.
For example, for arr = [2,3,4], the median is 3.
For example, for arr = [2,3], the median is (2 + 3) / 2 = 2.5.
Implement the MedianFinder class:
MedianFinder() initializes the MedianFinder object.
void addNum(int num) adds the integer num from the data stream to the data structure.
double findMedian() returns the median of all elements so far. Answers within 10-5 of the actual answer will be accepted.
 
Example 1:
Input
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]Output
[null, null, null, 1.5, null, 2.0]Explanation
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // return 1.5 (i.e., (1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
 
Constraints:
-105 <= num <= 105
There will be at least one element in the data structure before calling findMedian.
At most 5 * 104 calls will be made to addNum and findMedian. c code for vs code without comments and c code for leetcode without comments. */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* low;
    int* high;
    int lowSize;
    int highSize;
} MedianFinder;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void pushMax(int* heap, int* size, int val) {
    heap[(*size)++] = val;
    int i = *size - 1;
    while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int popMax(int* heap, int* size) {
    int res = heap[0];
    heap[0] = heap[--(*size)];
    int i = 0;
    while (i * 2 + 1 < *size) {
        int j = i * 2 + 1;
        if (j + 1 < *size && heap[j + 1] > heap[j]) j++;
        if (heap[i] >= heap[j]) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
    return res;
}

void pushMin(int* heap, int* size, int val) {
    heap[(*size)++] = val;
    int i = *size - 1;
    while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int popMin(int* heap, int* size) {
    int res = heap[0];
    heap[0] = heap[--(*size)];
    int i = 0;
    while (i * 2 + 1 < *size) {
        int j = i * 2 + 1;
        if (j + 1 < *size && heap[j + 1] < heap[j]) j++;
        if (heap[i] <= heap[j]) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
    return res;
}

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->low = (int*)malloc(50001 * sizeof(int));
    obj->high = (int*)malloc(50001 * sizeof(int));
    obj->lowSize = 0;
    obj->highSize = 0;
    return obj;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    pushMax(obj->low, &obj->lowSize, num);
    pushMin(obj->high, &obj->highSize, popMax(obj->low, &obj->lowSize));
    if (obj->lowSize < obj->highSize) {
        pushMax(obj->low, &obj->lowSize, popMin(obj->high, &obj->highSize));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->lowSize > obj->highSize) return (double)obj->low[0];
    return (obj->low[0] + obj->high[0]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->low);
    free(obj->high);
    free(obj);
}

int main() {
    MedianFinder* mf = medianFinderCreate();
    medianFinderAddNum(mf, 1);
    medianFinderAddNum(mf, 2);
    printf("%.1f\n", medianFinderFindMedian(mf));
    medianFinderAddNum(mf, 3);
    printf("%.1f\n", medianFinderFindMedian(mf));
    medianFinderFree(mf);
    return 0;
}