#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int type; 
    double x;
    double y;
} Dot;

typedef struct {
      int type;
    double x1, y1;
    double x2, y2;
} Line;
void calculateProperty(void *shapePtr) {
    int type = *(int*)shapePtr;
 if (type == 1) {
        Line *l = (Line*)shapePtr;
            double len = sqrt((l->x2 - l->x1)*(l->x2 - l->x1) + (l->y2 - l->y1)*(l->y2 - l->y1));
printf("Line: (%.4f, %.4f) -> (%.4f, %.4f), Length = %.4f\n",
               l->x1, l->y1, l->x2, l->y2, len);
    }
}
double cross(Dot a, Dot b, Dot c) {
    return (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
}
int compareDots(const void *p1, const void *p2) {
    Dot *a = (Dot*)p1;
 Dot *b = (Dot*)p2;
    if (a->x != b->x) return (a->x < b->x) ? -1 : 1;
 if (a->y != b->y) return (a->y < b->y) ? -1 : 1;
    return 0;
}
Line* computeConvexHull(const Dot *points, int n, int *hullEdgeCount) {
    Dot *pts = malloc(n * sizeof(Dot));
    for (int i = 0; i < n; i++) pts[i] = points[i];
    qsort(pts, n, sizeof(Dot), compareDots);

      Dot *hull = malloc(2 * n * sizeof(Dot));
    int k = 0;
for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(hull[k-2], hull[k-1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
 while (k >= t && cross(hull[k-2], hull[k-1], pts[i]) <= 0) k--;
        hull[k++] = pts[i];
    }

    int hullPoints = k - 1; 
    Line *edges = malloc(hullPoints * sizeof(Line));

    for (int i = 0; i < hullPoints; i++) {
        int j = (i + 1) % hullPoints;
        edges[i].type = 1;
     edges[i].x1 = hull[i].x;
          edges[i].y1 = hull[i].y;
     edges[i].x2 = hull[j].x;
        edges[i].y2 = hull[j].y;
    }

    *hullEdgeCount = hullPoints;
    free(pts);
free(hull);
    return edges;
}
int main() {
    FILE *f = fopen("points.txt", "r");
    if (!f) {
        printf("points.txt not found!\n");
        return 1;
    }

    int N;
       fscanf(f, "%d", &N);

    Dot *points = malloc(N * sizeof(Dot));
for (int i = 0; i < N; i++) {
        points[i].type = 0;
        fscanf(f, "%lf %lf", &points[i].x, &points[i].y);
    }
    fclose(f);
 int edgeCount = 0;
    Line *edges = computeConvexHull(points, N, &edgeCount);
printf("Convex Hull Edges: %d\n", edgeCount);
    double total = 0;
    for (int i = 0; i < edgeCount; i++) {
        calculateProperty(&edges[i]);
           double len = sqrt((edges[i].x2 - edges[i].x1)*(edges[i].x2 - edges[i].x1) +
                          (edges[i].y2 - edges[i].y1)*(edges[i].y2 - edges[i].y1));
        total += len;
    }
      printf("Total Perimeter = %.4f\n", total);
free(points);
    free(edges);
    return 0;
}