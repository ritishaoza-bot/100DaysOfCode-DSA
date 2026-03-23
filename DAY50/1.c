/*Problem: BST Search

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* searchBST(struct TreeNode* root, int val) {
    if (root == NULL || root->val == val) {
        return root;
    }
    if (val < root->val) {
        return searchBST(root->left, val);
    }
    return searchBST(root->right, val);
}

int main() {
    struct TreeNode* root = createNode(4);
    root->left = createNode(2);
    root->right = createNode(7);
    root->left->left = createNode(1);
    root->left->right = createNode(3);

    int target = 2;
    struct TreeNode* result = searchBST(root, target);

    if (result != NULL) {
        printf("Found node with value: %d\n", result->val);
    } else {
        printf("Value not found.\n");
    }

    return 0;
}