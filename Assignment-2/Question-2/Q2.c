//Name: fiza zafar
//roll no : 26k-0048
//Question #2


#include <stdio.h>
#include <math.h>

// Part 3: Function to return sum of proper divisors
int sumProperDivisors(int x) {
    if (x <= 1) {
        return 0;
    }
    int sum = 1; // 1 is always a divisor
    int sq = (int)sqrt(x);

    for (int i = 2; i <= sq; i++) {
        if (x % i == 0) {
            int other = x / i;
            sum += i;
            if (other != i && other != x) {
                sum += other;
            }
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter n: ");
    scanf("%d", &n);

    printf("\nAmicable pairs up to %d:\n", n);
    int totalPairs = 0;

    for (int a = 2; a <= n; a++) {
        int b = sumProperDivisors(a);

        // Rule 2: numbers must be different (no perfect numbers like 6, 28)
        // Rule 1: display only once, smaller first -> so b > a
        if (b > a && b <= n) {
            if (sumProperDivisors(b) == a) {
                printf("(%d, %d)\n", a, b);
                totalPairs++;
            }
        }
    }

    // Rule 4
    if (totalPairs == 0) {
        printf("No amicable pairs found up to %d\n", n);
    } else {
        printf("Total pairs: %d\n", totalPairs);
    }

    return 0;
}