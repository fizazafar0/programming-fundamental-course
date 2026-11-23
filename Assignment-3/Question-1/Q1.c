#include <stdio.h>
#include <stdlib.h>
int** allocateGrid(int n) {
    int** grid = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        grid[i] = (int*)malloc(n * sizeof(int));
    }
    return grid;
}
void freeGrid(int** grid, int n) {
    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
}

void printGrid(int** grid, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int countNeighbours(int** grid, int n, int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (grid[nx][ny] == 1) count++;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input.txt>\n", argv[0]);
        return 1;
    }
FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error: not found\n");
        return 1;
    }
int N, G;
    fscanf(file, "%d", &N);
    fscanf(file, "%d", &G);
    int** curr_grid = allocateGrid(N);
    int** next_grid = allocateGrid(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(file, "%d", &curr_grid[i][j]);
        }
    }
    fclose(file);
 printf("Generation 0:\n");
    printGrid(curr_grid, N);
    for (int gen = 1; gen <= G; gen++) {
 for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
 int live = countNeighbours(curr_grid, N, i, j);
 if (curr_grid[i][j] == 1) {
 if (live < 2) next_grid[i][j] = 0; 
 else if (live == 2 || live == 3) next_grid[i][j] = 1; 
 else next_grid[i][j] = 0; 
    } else {
 if (live == 3) next_grid[i][j] = 1; 
     else next_grid[i][j] = 0;
                }
            }
        }
  int** temp = curr_grid;
 curr_grid = next_grid;
     next_grid = temp;

 printf("Generation %d:\n", gen);
 printGrid(curr_grid, N);
    }
freeGrid(curr_grid, N);
    freeGrid(next_grid, N);

    return 0;
}