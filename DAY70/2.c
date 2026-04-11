/*There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.
You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
 
Example 1:
Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1Output: 700Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
Example 2:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1Output: 200Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.
Example 3:
Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0Output: 500Explanation:
The graph is shown above.
The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.
 
Constraints:
2 <= n <= 100
0 <= flights.length <= (n * (n - 1) / 2)
flights[i].length == 3
0 <= fromi, toi < n
fromi != toi
1 <= pricei <= 104
There will not be any multiple flights between two cities.
0 <= src, dst, k < n
src != dst.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1e9

int findCheapestPrice(int n, int** flights, int flightsSize, int src, int dst, int k) {
    int* dist = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;

    for (int i = 0; i <= k; i++) {
        int* temp = (int*)malloc(sizeof(int) * n);
        memcpy(temp, dist, sizeof(int) * n);
        for (int j = 0; j < flightsSize; j++) {
            int u = flights[j][0];
            int v = flights[j][1];
            int w = flights[j][2];
            if (dist[u] != INF && dist[u] + w < temp[v]) {
                temp[v] = dist[u] + w;
            }
        }
        free(dist);
        dist = temp;
    }

    int result = dist[dst] == INF ? -1 : dist[dst];
    free(dist);
    return result;
}

int main() {
    int n = 4;
    int src = 0, dst = 3, k = 1;
    int flightsData[5][3] = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    int flightsSize = 5;

    int** flights = (int**)malloc(sizeof(int*) * flightsSize);
    for (int i = 0; i < flightsSize; i++) {
        flights[i] = (int*)malloc(sizeof(int) * 3);
        for (int j = 0; j < 3; j++) {
            flights[i][j] = flightsData[i][j];
        }
    }

    int result = findCheapestPrice(n, flights, flightsSize, src, dst, k);
    printf("%d\n", result);

    for (int i = 0; i < flightsSize; i++) free(flights[i]);
    free(flights);

    return 0;
}