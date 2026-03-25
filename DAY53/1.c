/*Problem Statement:
Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

Input Format:
- First line contains integer N (number of nodes)
- Second line contains N space-separated integers representing level-order traversal (-1 indicates NULL)

Output Format:
- Print nodes column by column from leftmost to rightmost vertical line

Example:
Input:
7
1 2 3 4 5 6 7

Output:
4
2
1 5 6
3
7

Explanation:
Vertical lines are formed based on horizontal distance from root. Nodes sharing the same distance are printed together.*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct QueueItem {
    struct Node* node;
    int hd;
};

struct NodeList {
    int data[100];
    int size;
};

struct Node* newNode(int data) {
    if (data == -1) return NULL;
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node* buildTree() {
    int n;
    if (scanf("%d", &n) != 1 || n <= 0) return NULL;
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    struct Node* root = newNode(arr[0]);
    struct Node** queue = (struct Node**)malloc(n * sizeof(struct Node*));
    int head = 0, tail = 0;
    queue[tail++] = root;

    int i = 1;
    while (head < tail && i < n) {
        struct Node* curr = queue[head++];
        if (i < n) {
            curr->left = newNode(arr[i++]);
            if (curr->left) queue[tail++] = curr->left;
        }
        if (i < n) {
            curr->right = newNode(arr[i++]);
            if (curr->right) queue[tail++] = curr->right;
        }
    }
    free(arr);
    free(queue);
    return root;
}

void printVerticalOrder(struct Node* root) {
    if (!root) return;

    struct NodeList map[200];
    for (int i = 0; i < 200; i++) map[i].size = 0;

    struct QueueItem queue[2000];
    int head = 0, tail = 0;

    queue[tail++] = (struct QueueItem){root, 0};
    int minHd = 0, maxHd = 0;

    while (head < tail) {
        struct QueueItem curr = queue[head++];
        int hd = curr.hd;
        
        if (hd < minHd) minHd = hd;
        if (hd > maxHd) maxHd = hd;

        int mapIdx = hd + 100;
        map[mapIdx].data[map[mapIdx].size++] = curr.node->data;

        if (curr.node->left) 
            queue[tail++] = (struct QueueItem){curr.node->left, hd - 1};
        if (curr.node->right) 
            queue[tail++] = (struct QueueItem){curr.node->right, hd + 1};
    }

    for (int i = minHd; i <= maxHd; i++) {
        int idx = i + 100;
        for (int j = 0; j < map[idx].size; j++) {
            printf("%d ", map[idx].data[j]);
        }
        printf("\n");
    }
}

int main() {
    struct Node* root = buildTree();
    printVerticalOrder(root);
    return 0;
}