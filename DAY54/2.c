/*Given the root of a binary tree, return the zigzag level order traversal of its nodes' values. (i.e., from left to right, then right to left for the next level and alternate between).

 

Example 1:


Input: root = [3,9,20,null,null,15,7]
Output: [[3],[20,9],[15,7]]
Example 2:

Input: root = [1]
Output: [[1]]
Example 3:

Input: root = []
Output: []
 

Constraints:

The number of nodes in the tree is in the range [0, 2000].
-100 <= Node.val <= 100*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if (!root) {
        *returnSize = 0;
        return NULL;
    }
    int** res = malloc(2000 * sizeof(int*));
    *returnColumnSizes = malloc(2000 * sizeof(int));
    *returnSize = 0;
    struct TreeNode* queue[2000];
    int head = 0, tail = 0;
    queue[tail++] = root;
    bool leftToRight = true;
    while (head < tail) {
        int levelSize = tail - head;
        int* levelVals = malloc(levelSize * sizeof(int));
        (*returnColumnSizes)[*returnSize] = levelSize;
        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[head++];
            int index = leftToRight ? i : (levelSize - 1 - i);
            levelVals[index] = node->val;
            if (node->left) queue[tail++] = node->left;
            if (node->right) queue[tail++] = node->right;
        }
        res[(*returnSize)++] = levelVals;
        leftToRight = !leftToRight;
    }
    return res;
}

int main() {
    struct TreeNode* root = newNode(3);
    root->left = newNode(9);
    root->right = newNode(20);
    root->right->left = newNode(15);
    root->right->right = newNode(7);

    int returnSize;
    int* returnColumnSizes;
    int** result = zigzagLevelOrder(root, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d%s", result[i][j], (j == returnColumnSizes[i] - 1) ? "" : ",");
        }
        printf("] ");
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}