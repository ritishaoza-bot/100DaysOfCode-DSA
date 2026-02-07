#include <stdio.h>

int fib(int n) {
    if (n <= 1) {
        return n;
    }

    int a = 0;
    int b = 1;
    int sum = 0;

    for (int i = 2; i <= n; i++) {
        sum = a + b;
        a = b;
        b = sum;
    }

    return b;
}

int main() {
    int n = 4;
    printf("F(%d) = %d\n", n, fib(n));
    return 0;
}