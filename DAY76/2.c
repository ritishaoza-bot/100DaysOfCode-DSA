/*Given a reference of a node in a connected undirected graph.
Return a deep copy (clone) of the graph.
Each node in the graph contains a value (int) and a list (List[Node]) of its neighbors.
class Node {
    public int val;
    public List<Node> neighbors;
}
 
Test case format:
For simplicity, each node's value is the same as the node's index (1-indexed). For example, the first node with val == 1, the second node with val == 2, and so on. The graph is represented in the test case using an adjacency list.
An adjacency list is a collection of unordered lists used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.
The given node will always be the first node with val = 1. You must return the copy of the given node as a reference to the cloned graph.
 
Example 1:
Input: adjList = [[2,4],[1,3],[2,4],[1,3]]Output: [[2,4],[1,3],[2,4],[1,3]]Explanation: There are 4 nodes in the graph.
1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
Example 2:
Input: adjList = [[]]Output: [[]]Explanation: Note that the input contains one empty list. The graph consists of only one node with val = 1 and it does not have any neighbors.
Example 3:
Input: adjList = []Output: []Explanation: This an empty graph, it does not have any nodes.
 
Constraints:
The number of nodes in the graph is in the range [0, 100].
1 <= Node.val <= 100
Node.val is unique for each node.
There are no repeated edges and no self-loops in the graph.
The Graph is connected and all nodes can be visited starting from the given node.*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

struct Node* visited[101];

struct Node* dfs(struct Node* node) {
    if (!node) return NULL;
    if (visited[node->val]) return visited[node->val];

    struct Node* clone = (struct Node*)malloc(sizeof(struct Node));
    clone->val = node->val;
    clone->numNeighbors = node->numNeighbors;
    visited[node->val] = clone;

    if (clone->numNeighbors > 0) {
        clone->neighbors = (struct Node**)malloc(clone->numNeighbors * sizeof(struct Node*));
        for (int i = 0; i < node->numNeighbors; i++) {
            clone->neighbors[i] = dfs(node->neighbors[i]);
        }
    } else {
        clone->neighbors = NULL;
    }

    return clone;
}

struct Node* cloneGraph(struct Node* s) {
    if (!s) return NULL;
    for (int i = 0; i < 101; i++) visited[i] = NULL;
    return dfs(s);
}

int main() {
    struct Node* n1 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n3 = (struct Node*)malloc(sizeof(struct Node));
    struct Node* n4 = (struct Node*)malloc(sizeof(struct Node));

    n1->val = 1; n1->numNeighbors = 2;
    n2->val = 2; n2->numNeighbors = 2;
    n3->val = 3; n3->numNeighbors = 2;
    n4->val = 4; n4->numNeighbors = 2;

    n1->neighbors = (struct Node**)malloc(2 * sizeof(struct Node*));
    n1->neighbors[0] = n2; n1->neighbors[1] = n4;

    n2->neighbors = (struct Node**)malloc(2 * sizeof(struct Node*));
    n2->neighbors[0] = n1; n2->neighbors[1] = n3;

    n3->neighbors = (struct Node**)malloc(2 * sizeof(struct Node*));
    n3->neighbors[0] = n2; n3->neighbors[1] = n4;

    n4->neighbors = (struct Node**)malloc(2 * sizeof(struct Node*));
    n4->neighbors[0] = n1; n4->neighbors[1] = n3;

    struct Node* cloned = cloneGraph(n1);

    if (cloned != n1 && cloned->val == n1->val) {
        printf("Cloned Node Address: %p, Original Node Address: %p\n", (void*)cloned, (void*)n1);
        printf("Success: Node %d cloned.\n", cloned->val);
    }

    return 0;
}