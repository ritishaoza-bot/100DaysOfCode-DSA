/*Given the root of a binary tree, return the inorder traversal of its nodes' values.

 

Example 1:

Input: root = [1,null,2,3]

Output: [1,3,2]

Explanation:



Example 2:

Input: root = [1,2,3,4,5,null,8,null,null,6,7,9]

Output: [4,2,6,5,7,1,3,9,8]

Explanation:



Example 3:

Input: root = []

Output: []

Example 4:

Input: root = [1]

Output: [1]

 

Constraints:

The number of nodes in the tree is in the range [0, 100].
-100 <= Node.val <= 100
 */

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void traverse(struct TreeNode* root, int* res, int* size) {
    if (!root) return;
    traverse(root->left, res, size);
    res[(*size)++] = root->val;
    traverse(root->right, res, size);
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int* res = (int*)malloc(100 * sizeof(int));
    *returnSize = 0;
    traverse(root, res, returnSize);
    return res;
}

int main() {
    struct TreeNode* root = newNode(1);
    root->right = newNode(2);
    root->right->left = newNode(3);

    int size;
    int* result = inorderTraversal(root, &size);

    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}