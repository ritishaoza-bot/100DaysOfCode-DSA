#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) return i;
    }
    return -1;
}

struct Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int* postIdx) {
    if (inStart > inEnd) return NULL;

    int curr = postorder[(*postIdx)--];
    struct Node* node = createNode(curr);

    if (inStart == inEnd) return node;

    int inIdx = findIndex(inorder, inStart, inEnd, curr);

    node->right = buildTree(inorder, postorder, inIdx + 1, inEnd, postIdx);
    node->left = buildTree(inorder, postorder, inStart, inIdx - 1, postIdx);

    return node;
}

void printPreorder(struct Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    int* inorder = (int*)malloc(n * sizeof(int));
    int* postorder = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) scanf("%d", &inorder[i]);
    for (int i = 0; i < n; i++) scanf("%d", &postorder[i]);

    int postIdx = n - 1;
    struct Node* root = buildTree(inorder, postorder, 0, n - 1, &postIdx);

    printPreorder(root);
    printf("\n");

    free(inorder);
    free(postorder);
    return 0;
}