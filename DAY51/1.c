/*Problem Statement:
Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Search Tree.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
6 2 8 0 4 7 9
2 8

Output:
6*/

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

struct TreeNode* insert(struct TreeNode* root, int val) {
    if (root == NULL) return createNode(val);
    if (val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

struct TreeNode* lowestCommonAncestor(struct TreeNode* root, int p, int q) {
    while (root != NULL) {
        if (p < root->val && q < root->val) {
            root = root->left;
        } else if (p > root->val && q > root->val) {
            root = root->right;
        } else {
            return root;
        }
    }
    return NULL;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    struct TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    int p_val, q_val;
    scanf("%d %d", &p_val, &q_val);

    struct TreeNode* lca = lowestCommonAncestor(root, p_val, q_val);
    if (lca != NULL) {
        printf("%d\n", lca->val);
    }

    return 0;
}