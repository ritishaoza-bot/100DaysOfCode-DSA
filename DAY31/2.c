/*Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

Example 3:

Input: s = "(]"

Output: false

Example 4:

Input: s = "([])"

Output: true

Example 5:

Input: s = "([)]"

Output: false

 

Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

bool isValid(char* s) {
    int n = strlen(s);
    if (n % 2 != 0) return false;

    char* stack = (char*)malloc(n);
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            if (top == -1) {
                free(stack);
                return false;
            }
            if ((c == ')' && stack[top] != '(') ||
                (c == '}' && stack[top] != '{') ||
                (c == ']' && stack[top] != '[')) {
                free(stack);
                return false;
            }
            top--;
        }
    }

    bool result = (top == -1);
    free(stack);
    return result;
}

int main() {
    char* tests[] = {"()", "()[]{}", "(]", "([)]", "{[]}"};
    for (int i = 0; i < 5; i++) {
        printf("Input: %s -> Output: %s\n", tests[i], isValid(tests[i]) ? "true" : "false");
    }
    return 0;
}