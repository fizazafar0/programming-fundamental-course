#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void fft1D(float *real, float *imag, int N) {
    for (int i = 1, j = 0; i < N; i++) {
        int bit = N >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) {
            float t = real[i]; real[i] = real[j]; real[j] = t;
            t = imag[i]; imag[i] = imag[j]; imag[j] = t;
        }
    }
    for (int len = 2; len <= N; len <<= 1) {
        float ang = -2 * 3.14159265f / len;
        float wr = cosf(ang), wi = sinf(ang);
        for (int i = 0; i < N; i += len) {
            float cwr = 1, cwi = 0;
            for (int k = 0; k < len / 2; k++) {
                int u = i + k, v = i + k + len / 2;
                float vr = real[v] * cwr - imag[v] * cwi;
                float vi = real[v] * cwi + imag[v] * cwr;
                real[v] = real[u] - vr; imag[v] = imag[u] - vi;
                real[u] += vr; imag[u] += vi;
                float nwr = cwr * wr - cwi * wi;
                cwi = cwr * wi + cwi * wr; cwr = nwr;
            }
        }
    }
}
void fft2D(float **real_sheet, float **imag_sheet, int N) {
    for (int i = 0; i < N; i++) fft1D(real_sheet[i], imag_sheet[i], N);
    float *tr = malloc(N * sizeof(float));
    float *ti = malloc(N * sizeof(float));
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) { tr[i] = real_sheet[i][j]; ti[i] = imag_sheet[i][j]; }
        fft1D(tr, ti, N);
        for (int i = 0; i < N; i++) { real_sheet[i][j] = tr[i]; imag_sheet[i][j] = ti[i]; }
    }
    free(tr); free(ti);
}

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <grid3d.txt>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) { printf("Error: not found\n"); return 1; }

    int N; fscanf(fp, "%d", &N);
    int N2 = N * N, N3 = N * N * N;
    float *real_block = malloc(N3 * sizeof(float));
    float *imag_block = calloc(N3, sizeof(float));
    float ***real_vol = malloc(N * sizeof(float**));
    float ***imag_vol = malloc(N * sizeof(float**));
    for (int z = 0; z < N; z++) {
        real_vol[z] = malloc(N * sizeof(float*));
        imag_vol[z] = malloc(N * sizeof(float*));
        for (int y = 0; y < N; y++) {
            real_vol[z][y] = &real_block[(z * N + y) * N];
            imag_vol[z][y] = &imag_block[(z * N + y) * N];
        }
    }
    for (int i = 0; i < N3; i++) fscanf(fp, "%f", &real_block[i]);
    fclose(fp);
    for (int z = 0; z < N; z++) fft2D(real_vol[z], imag_vol[z], N);
    float *t_real_block = malloc(N3 * sizeof(float));
    float *t_imag_block = malloc(N3 * sizeof(float));
    float ***t_real = malloc(N * sizeof(float**));
    float ***t_imag = malloc(N * sizeof(float**));
    for (int z = 0; z < N; z++) {
        t_real[z] = malloc(N * sizeof(float*));
        t_imag[z] = malloc(N * sizeof(float*));
        for (int y = 0; y < N; y++) {
            t_real[z][y] = &t_real_block[(z * N + y) * N];
            t_imag[z][y] = &t_imag_block[(z * N + y) * N];
        }
    }
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            for (int z = 0; z < N; z++) {
                t_real[z][y][x] = real_vol[x][y][z];
                t_imag[z][y][x] = imag_vol[x][y][z];
            }
    for (int z = 0; z < N; z++) fft2D(t_real[z], t_imag[z], N);

    
    printf("Magnitude Spectrum (z = 0):\n");
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            float mag = sqrtf(t_real[0][y][x]*t_real[0][y][x] + t_imag[0][y][x]*t_imag[0][y][x]);
            printf("%.2f ", mag);
        }
        printf("\n");
    }

    
    for (int z = 0; z < N; z++) { free(real_vol[z]); free(imag_vol[z]); free(t_real[z]); free(t_imag[z]); }
    free(real_vol); free(imag_vol); free(t_real); free(t_imag);
    free(real_block); free(imag_block); free(t_real_block); free(t_imag_block);
    return 0;
}