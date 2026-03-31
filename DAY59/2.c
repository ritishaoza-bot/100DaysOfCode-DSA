/*Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]
 

Constraints:

1 <= inorder.length <= 3000
postorder.length == inorder.length
-3000 <= inorder[i], postorder[i] <= 3000
inorder and postorder consist of unique values.
Each value of postorder also appears in inorder.
inorder is guaranteed to be the inorder traversal of the tree.
postorder is guaranteed to be the postorder traversal of the tree.*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* build(int* inorder, int inStart, int inEnd, int* postorder, int* postIndex) {
    if (inStart > inEnd) return NULL;

    int rootVal = postorder[(*postIndex)--];
    struct TreeNode* root = createNode(rootVal);

    int inIndex = 0;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == rootVal) {
            inIndex = i;
            break;
        }
    }

    root->right = build(inorder, inIndex + 1, inEnd, postorder, postIndex);
    root->left = build(inorder, inStart, inIndex - 1, postorder, postIndex);

    return root;
}

struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    int postIndex = postorderSize - 1;
    return build(inorder, 0, inorderSize - 1, postorder, &postIndex);
}

void printPreOrder(struct TreeNode* node) {
    if (!node) return;
    printf("%d ", node->val);
    printPreOrder(node->left);
    printPreOrder(node->right);
}

int main() {
    int inorder[] = {9, 3, 15, 20, 7};
    int postorder[] = {9, 15, 7, 20, 3};
    int size = 5;

    struct TreeNode* root = buildTree(inorder, size, postorder, size);

    printPreOrder(root);
    return 0;
}