/*There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.

 

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.
 

Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int val;
    struct Node* next;
};

bool isCyclic(int v, struct Node** adj, bool* visited, bool* recStack) {
    visited[v] = true;
    recStack[v] = true;

    struct Node* temp = adj[v];
    while (temp) {
        int neighbor = temp->val;
        if (!visited[neighbor]) {
            if (isCyclic(neighbor, adj, visited, recStack)) return true;
        } else if (recStack[neighbor]) {
            return true;
        }
        temp = temp->next;
    }

    recStack[v] = false;
    return false;
}

int main() {
    int numCourses = 2;
    int preCount = 2;
    int prerequisites[2][2] = {{1, 0}, {0, 1}};

    struct Node** adj = calloc(numCourses, sizeof(struct Node*));
    for (int i = 0; i < preCount; i++) {
        struct Node* newNode = malloc(sizeof(struct Node));
        newNode->val = prerequisites[i][0];
        newNode->next = adj[prerequisites[i][1]];
        adj[prerequisites[i][1]] = newNode;
    }

    bool* visited = calloc(numCourses, sizeof(bool));
    bool* recStack = calloc(numCourses, sizeof(bool));
    bool possible = true;

    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            if (isCyclic(i, adj, visited, recStack)) {
                possible = false;
                break;
            }
        }
    }

    if (possible) printf("true\n");
    else printf("false\n");

    return 0;
}