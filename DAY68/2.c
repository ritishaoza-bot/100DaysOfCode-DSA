/*A new alien language uses the English alphabet, but the order of letters is unknown. You are given a list of words[] from the alien language’s dictionary, where the words are claimed to be sorted lexicographically according to the language’s rules.

Your task is to determine the correct order of letters in this alien language based on the given words. If the order is valid, return a string containing the unique letters in lexicographically increasing order as per the new language's rules. If there are multiple valid orders, return any one of them.

However, if the given arrangement of words is inconsistent with any possible letter ordering, return an empty string ("").

A string a is lexicographically smaller than a string b if, at the first position where they differ, the character in a appears earlier in the alien language than the corresponding character in b. If all characters in the shorter word match the beginning of the longer word, the shorter word is considered smaller.

Note: Your implementation will be tested using a driver code. It will print true if your returned order correctly follows the alien language’s lexicographic rules; otherwise, it will print false.

Examples:

Input: words[] = ["baa", "abcd", "abca", "cab", "cad"]
Output: true
Explanation: A possible correct order of letters in the alien dictionary is "bdac".
The pair "baa" and "abcd" suggests 'b' appears before 'a' in the alien dictionary.
The pair "abcd" and "abca" suggests 'd' appears before 'a' in the alien dictionary.
The pair "abca" and "cab" suggests 'a' appears before 'c' in the alien dictionary.
The pair "cab" and "cad" suggests 'b' appears before 'd' in the alien dictionary.
So, 'b' → 'd' → 'a' → 'c' is a valid ordering.
Input: words[] = ["caa", "aaa", "aab"]
Output: true
Explanation: A possible correct order of letters in the alien dictionary is "cab".
The pair "caa" and "aaa" suggests 'c' appears before 'a'.
The pair "aaa" and "aab" suggests 'a' appear before 'b' in the alien dictionary. 
So, 'c' → 'a' → 'b' is a valid ordering.
Input: words[] = ["ab", "cd", "ef", "ad"]
Output: ""
Explanation: No valid ordering of letters is possible.
The pair "ab" and "ef" suggests "a" appears before "e".
The pair "ef" and "ad" suggests "e" appears before "a", which contradicts the ordering rules.
Constraints:
1 ≤ words.length ≤ 500
1 ≤ words[i].length ≤ 100
words[i] consists only of lowercase English letters.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void solve() {
    // Example Input
    char words[][100] = {"baa", "abcd", "abca", "cab", "cad"};
    int n = 5;
    
    int adj[26][26] = {0};
    int inDegree[26];
    for(int i=0; i<26; i++) inDegree[i] = -1; // -1 means char not present

    // Initialize present characters
    for(int i=0; i<n; i++) {
        for(int j=0; words[i][j]; j++) {
            if(inDegree[words[i][j]-'a'] == -1) inDegree[words[i][j]-'a'] = 0;
        }
    }

    // Build Adjacency Matrix
    for(int i=0; i < n-1; i++) {
        char *s1 = words[i], *s2 = words[i+1];
        int len1 = strlen(s1), len2 = strlen(s2);
        int found = 0;
        for(int j=0; j < (len1 < len2 ? len1 : len2); j++) {
            if(s1[j] != s2[j]) {
                if(!adj[s1[j]-'a'][s2[j]-'a']) {
                    adj[s1[j]-'a'][s2[j]-'a'] = 1;
                    inDegree[s2[j]-'a']++;
                }
                found = 1;
                break;
            }
        }
        if(!found && len1 > len2) {
            printf("Invalid Order\n");
            return;
        }
    }

    // Kahn's Algorithm
    int queue[26], front=0, rear=0;
    int count = 0;
    for(int i=0; i<26; i++) {
        if(inDegree[i] == 0) queue[rear++] = i;
        if(inDegree[i] != -1) count++;
    }

    char res[27];
    int idx = 0;
    while(front < rear) {
        int u = queue[front++];
        res[idx++] = (char)(u + 'a');
        for(int v=0; v<26; v++) {
            if(adj[u][v]) {
                inDegree[v]--;
                if(inDegree[v] == 0) queue[rear++] = v;
            }
        }
    }
    res[idx] = '\0';

    if(idx < count) {
        printf("No valid order (Cycle detected)\n");
    } else {
        printf("Alien Language Order: %s\n", res);
    }
}

int main() {
    solve();
    return 0;
}