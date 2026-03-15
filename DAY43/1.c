/*Problem Statement:
Construct a Binary Tree from the given level-order traversal.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers (-1 represents NULL)

Output Format:
- Print inorder traversal of the constructed tree

Example:
Input:
7
1 2 3 4 5 -1 6

Output:
4 2 5 1 3 6*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left, *right;
};

struct Queue {
    struct TreeNode** data;
    int front, rear, size;
};

struct TreeNode* newNode(int val) {
    if (val == -1) return NULL;
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

struct Queue* createQueue(int cap) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->data = (struct TreeNode**)malloc(cap * sizeof(struct TreeNode*));
    q->front = q->rear = q->size = 0;
    return q;
}

void enqueue(struct Queue* q, struct TreeNode* node) {
    q->data[q->rear++] = node;
    q->size++;
}

struct TreeNode* dequeue(struct Queue* q) {
    q->size--;
    return q->data[q->front++];
}

void inorder(struct TreeNode* root, int* first) {
    if (!root) return;
    inorder(root->left, first);
    if (!(*first)) printf(" ");
    printf("%d", root->val);
    *first = 0;
    inorder(root->right, first);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n == 0) return 0;

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    if (arr[0] == -1) return 0;

    struct TreeNode* root = newNode(arr[0]);
    struct Queue* q = createQueue(n);
    enqueue(q, root);

    int i = 1;
    while (i < n && q->size > 0) {
        struct TreeNode* curr = dequeue(q);

        if (i < n) {
            curr->left = newNode(arr[i++]);
            if (curr->left) enqueue(q, curr->left);
        }
        if (i < n) {
            curr->right = newNode(arr[i++]);
            if (curr->right) enqueue(q, curr->right);
        }
    }

    int first = 1;
    inorder(root, &first);
    printf("\n");

    return 0;
}