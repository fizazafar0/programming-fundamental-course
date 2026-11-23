#include <stdio.h>
#include <math.h>
#define PI 3.14159265
int main() {
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    if (N % 2 == 0) {
        printf("Please enter an odd value of N.\n");
        return 0;
    }
int H = N * 2;
    int W = N * 2 + 1;
    char canvas[100][100];
int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            canvas[i][j] = ' ';
        }
    }

    double cx = W / 2.0;
    double cy = H / 2.0;
    double R = N;          
    double r = N * 0.42;   
    double px[10], py[10];

    for (i = 0; i < 10; i++) {
        double angle = -90 + i * 36;
        double rad = (i % 2 == 0) ? R : r; 
        px[i] = cx + rad * cos(angle * PI / 180.0);
        py[i] = cy + rad * sin(angle * PI / 180.0);
    }
    for (i = 0; i < 10; i++) {
        int next = (i + 1) % 10;
        int steps = 100;
        int s;
        for (s = 0; s <= steps; s++) {
            double t = (double)s / steps;
            int x = (int)(px[i] + (px[next] - px[i]) * t + 0.5);
            int y = (int)(py[i] + (py[next] - py[i]) * t + 0.5);
            if (x >= 0 && x < W && y >= 0 && y < H) {
                canvas[y][x] = '*';
            }
        }
    }
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
 return 0;
}