#include <stdio.h>
int main() {
    int N, i, j, marks, sum, fail;
    float avg;
    printf("Enter number of students: ");
    scanf("%d", &N);
    for(i = 1; i <= N; i++) {
        sum = 0;
        fail = 0;
        printf("\nStudent %d - Enter 5 subject marks:\n", i);
        for(j = 1; j <= 5; j++) {
            scanf("%d", &marks);
            sum += marks;
            if(marks < 33) fail = 1;
        }
        avg = sum / 5.0;
        printf("Sum=%d, Avg=%.2f, ", sum, avg);
        if(fail == 1) {
            printf("Result: Fail - Subject Deficiency\n");
        } else if(avg >= 80) {
            printf("Result: Distinction\n");
        } else if(avg >= 60) {
            printf("Result: Pass\n");
        } else {
            printf("Result: Fail\n");
        }
    }
    return 0;
}