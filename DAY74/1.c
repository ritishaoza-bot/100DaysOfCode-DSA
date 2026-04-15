/*Problem Statement
Given an array of candidate names where each name represents a vote cast for that candidate, determine the candidate who received the maximum number of votes. In case of a tie, return the lexicographically smallest candidate name.

Input Format
First line contains an integer n representing number of votes.
Second line contains n space-separated strings representing candidate names.

Output Format
Print the name of the winning candidate followed by the number of votes received.

Sample Input
13
john johnny jackie johnny john jackie jamie jamie john johnny jamie johnny john

Sample Output
john 4

Explanation
Both john and johnny receive 4 votes, but john is lexicographically smaller, so john is declared the winner.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    char **candidates = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        candidates[i] = (char *)malloc(101 * sizeof(char));
        scanf("%s", candidates[i]);
    }

    qsort(candidates, n, sizeof(char *), compare);

    char *winner = candidates[0];
    int max_votes = 0;
    int current_count = 0;

    for (int i = 0; i < n; i++) {
        current_count++;

        if (i == n - 1 || strcmp(candidates[i], candidates[i + 1]) != 0) {
            if (current_count > max_votes) {
                max_votes = current_count;
                winner = candidates[i];
            }
            current_count = 0;
        }
    }

    printf("%s %d\n", winner, max_votes);

    for (int i = 0; i < n; i++) {
        free(candidates[i]);
    }
    free(candidates);

    return 0;
}