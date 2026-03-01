/*Problem: Rotate Linked List Right by k Places - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers
- Third line: integer k

Output:
- Print the linked list elements after rotation, space-separated

Example:
Input:
5
10 20 30 40 50
2

Output:
40 50 10 20 30

Explanation:
Connect last node to head forming circular list. Traverse to (n-k)th node, set next to NULL, update head to (n-k+1)th node.*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n, k, val;
    if (scanf("%d", &n) != 1 || n <= 0) return 0;

    struct Node *head = NULL, *tail = NULL;
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &val) != 1) break;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = val;
        newNode->next = NULL;
        if (!head) head = newNode;
        else tail->next = newNode;
        tail = newNode;
    }

    if (scanf("%d", &k) != 1) k = 0;
    k = k % n;

    if (k > 0) {
        tail->next = head; 
        int steps = n - k;
        for (int i = 0; i < steps; i++) {
            tail = tail->next;
        }
        head = tail->next;
        tail->next = NULL;
    }

    struct Node* temp = head;
    while (temp) {
        printf("%d%s", temp->data, temp->next ? " " : "");
        struct Node* toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    return 0;
}