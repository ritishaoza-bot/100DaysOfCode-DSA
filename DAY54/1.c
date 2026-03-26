/*Problem Statement:
Perform zigzag (spiral) level order traversal of a binary tree. Alternate levels should be traversed left-to-right and right-to-left.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print traversal in zigzag order

Example:
Input:
7
1 2 3 4 5 6 7

Output:
1 3 2 4 5 6 7

Explanation:
Level 1 is printed left-to-right, level 2 right-to-left, and so on.*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* newNode(int data) {
    if (data == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void zigzagTraversal(struct Node* root) {
    if (!root) return;

    struct Node* s1[2000]; 
    struct Node* s2[2000]; 
    int top1 = -1, top2 = -1;

    s1[++top1] = root;

    while (top1 != -1 || top2 != -1) {
        while (top1 != -1) {
            struct Node* temp = s1[top1--];
            printf("%d ", temp->data);
            if (temp->left) s2[++top2] = temp->left;
            if (temp->right) s2[++top2] = temp->right;
        }

        while (top2 != -1) {
            struct Node* temp = s2[top2--];
            printf("%d ", temp->data);
            if (temp->right) s1[++top1] = temp->right;
            if (temp->left) s1[++top1] = temp->left;
        }
    }
}

struct Node* buildTree(int n, int* arr) {
    if (n == 0 || arr[0] == -1) return NULL;
    struct Node* root = newNode(arr[0]);
    struct Node* queue[2000];
    int head = 0, tail = 0;
    queue[tail++] = root;
    int i = 1;
    while (i < n && head < tail) {
        struct Node* curr = queue[head++];
        curr->left = newNode(arr[i++]);
        if (curr->left) queue[tail++] = curr->left;
        if (i < n) {
            curr->right = newNode(arr[i++]);
            if (curr->right) queue[tail++] = curr->right;
        }
    }
    return root;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(n, arr);
    zigzagTraversal(root);
    printf("\n");

    return 0;
}