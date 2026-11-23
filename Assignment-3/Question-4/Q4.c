#include <stdio.h>
int main() {
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    if (N % 2 == 0) {
        printf("Please enter an odd value of N.\n");
        return 0;
    }
int mid = N / 2;
    int width = 2 * mid + 1; 
    int i, j;
    int left, right;
 for (i = 0; i < N; i++) {
        if (i <= mid) {
            left = mid - i;
            right = mid + i;
        }
        else if (i < N - 1) {
            left = 0;
            right = width - 1;
        }
        else {
            left = 0;
            right = width - 1;
        }

        for (j = 0; j < width; j++) {
            if (i == N - 1) {
                printf("*");
            }
            else if (j == left || j == right) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}