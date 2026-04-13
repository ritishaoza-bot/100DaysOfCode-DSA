/*Problem Statement
Implement a hash table using quadratic probing with formula:

h(k, i) = (h(k) + i*i) % m

Input Format
Same as previous.

Output Format
Result of SEARCH operations.

Sample Input
7
4
INSERT 49
INSERT 56
SEARCH 49
SEARCH 15

Sample Output
FOUND
NOT FOUND

Explanation
Collisions resolved using i² jumps. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(int* table, int m, int key) {
    for (int i = 0; i < m; i++) {
        int index = (key % m + i * i) % m;
        if (table[index] == -1) {
            table[index] = key;
            return;
        }
    }
}

void search(int* table, int m, int key) {
    for (int i = 0; i < m; i++) {
        int index = (key % m + i * i) % m;
        if (table[index] == key) {
            printf("FOUND\n");
            return;
        }
        if (table[index] == -1) {
            break;
        }
    }
    printf("NOT FOUND\n");
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;

    int* table = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        table[i] = -1;
    }

    char op[10];
    int key;
    for (int i = 0; i < n; i++) {
        scanf("%s %d", op, &key);
        if (strcmp(op, "INSERT") == 0) {
            insert(table, m, key);
        } else if (strcmp(op, "SEARCH") == 0) {
            search(table, m, key);
        }
    }

    free(table);
    return 0;
}