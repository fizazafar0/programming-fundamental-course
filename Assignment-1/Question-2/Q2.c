#include <stdio.h>
int main() {
    int N, i, current = 0, req;
    printf("Enter number of requests N: ");
    scanf("%d", &N);
    printf("Elevator starts at Floor 0\n");
    for(i = 1; i <= N; i++) {
        printf("Enter request %d: ", i);
        scanf("%d", &req);
        if(req > current) {
            printf("Moving Up\n");
        } else if(req < current) {
            printf("Moving Down\n");
        } else {
            printf("Doors Opening\n");
        }
        current = req;
        printf("Current Floor: %d\n", current);
    }
    return 0;
}