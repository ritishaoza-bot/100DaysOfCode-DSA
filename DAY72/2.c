/*int dp[1 << 15][15];

int solve(int mask, int u, int n, int cost[15][15]) {
    if (mask == (1 << n) - 1) {
        return cost[u][0];
    }
    if (dp[mask][u] != -1) {
        return dp[mask][u];
    }

    int ans = 1e9;
    for (int v = 0; v < n; v++) {
        if (!(mask & (1 << v))) {
            int temp = cost[u][v] + solve(mask | (1 << v), v, n, cost);
            if (temp < ans) {
                ans = temp;
            }
        }
    }
    return dp[mask][u] = ans;
}

int total_cost(int n, int cost[15][15]) {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    return solve(1, 0, n, cost);
}*/

#include <stdio.h>
#include <string.h>

#define INF 1e9

int dp[1 << 15][15];

int min(int a, int b) {
    return (a < b) ? a : b;
}

int tsp(int mask, int pos, int n, int cost[15][15]) {
    if (mask == (1 << n) - 1) {
        return cost[pos][0];
    }
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }

    int res = INF;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            int newRes = cost[pos][city] + tsp(mask | (1 << city), city, n, cost);
            res = min(res, newRes);
        }
    }
    return dp[mask][pos] = res;
}

int main() {
    int n = 3;
    int cost[15][15] = {
        {0, 1000, 5000},
        {5000, 0, 1000},
        {1000, 5000, 0}
    };

    memset(dp, -1, sizeof(dp));
    
    int result = tsp(1, 0, n, cost);
    printf("%d\n", result);

    return 0;
}