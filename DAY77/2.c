/*There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:


Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
Example 2:

Input: n = 2, connections = [[0,1]]
Output: [[0,1]]
 

Constraints:

2 <= n <= 105
n - 1 <= connections.length <= 105
0 <= ai, bi <= n - 1
ai != bi
There are no repeated connections.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct Edge {
    int to;
    int next;
};

void findBridges(int u, int p, int* timer, int* disc, int* low, int* head, struct Edge* edges, int** res, int* resSize) {
    disc[u] = low[u] = ++(*timer);
    for (int i = head[u]; i != -1; i = edges[i].next) {
        int v = edges[i].to;
        if (v == p) continue;
        if (disc[v]) {
            low[u] = MIN(low[u], disc[v]);
        } else {
            findBridges(v, u, timer, disc, low, head, edges, res, resSize);
            low[u] = MIN(low[u], low[v]);
            if (low[v] > disc[u]) {
                res[*resSize] = (int*)malloc(2 * sizeof(int));
                res[*resSize][0] = u;
                res[*resSize][1] = v;
                (*resSize)++;
            }
        }
    }
}

int main() {
    int n = 4;
    int connData[4][2] = {{0,1}, {1,2}, {2,0}, {1,3}};
    int connectionsSize = 4;

    struct Edge* edges = (struct Edge*)malloc(2 * connectionsSize * sizeof(struct Edge));
    int* head = (int*)malloc(n * sizeof(int));
    memset(head, -1, n * sizeof(int));
    
    int edgeIdx = 0;
    for (int i = 0; i < connectionsSize; i++) {
        int u = connData[i][0];
        int v = connData[i][1];
        edges[edgeIdx] = (struct Edge){v, head[u]};
        head[u] = edgeIdx++;
        edges[edgeIdx] = (struct Edge){u, head[v]};
        head[v] = edgeIdx++;
    }

    int* disc = (int*)calloc(n, sizeof(int));
    int* low = (int*)calloc(n, sizeof(int));
    int** res = (int**)malloc(connectionsSize * sizeof(int*));
    int timer = 0, resSize = 0;

    findBridges(0, -1, &timer, disc, low, head, edges, res, &resSize);

    printf("Critical Connections:\n");
    for (int i = 0; i < resSize; i++) {
        printf("[%d, %d]\n", res[i][0], res[i][1]);
        free(res[i]);
    }

    free(res);
    free(edges);
    free(head);
    free(disc);
    free(low);

    return 0;
}