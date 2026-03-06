/*Given a string s which represents an expression, evaluate this expression and return its value. 

The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].

Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

 

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5
 

Constraints:

1 <= s.length <= 3 * 105
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 231 - 1].
The answer is guaranteed to fit in a 32-bit integer.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int calculate(char *s) {
    int len = strlen(s);
    if (len == 0) return 0;
    int *stack = (int *)malloc(sizeof(int) * len);
    int top = -1;
    long currentNumber = 0;
    char operation = '+';

    for (int i = 0; i < len; i++) {
        char currentChar = s[i];
        if (isdigit(currentChar)) {
            currentNumber = (currentNumber * 10) + (currentChar - '0');
        }
        if ((!isdigit(currentChar) && !isspace(currentChar)) || i == len - 1) {
            if (operation == '+') {
                stack[++top] = currentNumber;
            } else if (operation == '-') {
                stack[++top] = -currentNumber;
            } else if (operation == '*') {
                stack[top] = stack[top] * currentNumber;
            } else if (operation == '/') {
                stack[top] = stack[top] / currentNumber;
            }
            operation = currentChar;
            currentNumber = 0;
        }
    }

    int result = 0;
    while (top != -1) {
        result += stack[top--];
    }
    free(stack);
    return result;
}

int main() {
    char s[] = "3+5 / 2";
    printf("Result: %d\n", calculate(s));
    return 0;
}