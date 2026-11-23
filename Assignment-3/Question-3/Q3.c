#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DISTANCE 0
#define LENGTH 1
#define AREA 2
#define PERIMETER 3


typedef struct 
{ int type; double x, y; }Dot;
typedef struct
    { int type; double x1, y1, x2, y2; } Line;
typedef struct
{ int type; double x1, y1, x2, y2, x3, y3; } Triangle;
typedef struct 
    { int type; double x, y, side; } Square;
  typedef struct 
{ int type; double x, y, width, height; } Rectangle;

double dist(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

double calculateProperty(void *shapePtr, int propertyType) {
    int type = *(int*)shapePtr;
switch (type) {
        case 0: { 
               Dot *d = (Dot*)shapePtr;
     if (propertyType == DISTANCE) return sqrt(d->x*d->x + d->y*d->y);
            return 0;
        }
case 1: { 
            Line *l = (Line*)shapePtr;
                  if (propertyType == LENGTH) return dist(l->x1, l->y1, l->x2, l->y2);
            return 0;
        }
case 2: { 
            Triangle *t = (Triangle*)shapePtr;
            if (propertyType == AREA) {
 return 0.5 * fabs(t->x1*(t->y2 - t->y3) + t->x2*(t->y3 - t->y1) + t->x3*(t->y1 - t->y2));
            }
            if (propertyType == PERIMETER) {
                return dist(t->x1,t->y1,t->x2,t->y2) + dist(t->x2,t->y2,t->x3,t->y3) + dist(t->x3,t->y3,t->x1,t->y1);
            }
            return 0;
        }
case 3: { 
            Square *s = (Square*)shapePtr;
            if (propertyType == AREA) return s->side * s->side;
                  if (propertyType == PERIMETER) return 4 * s->side;
            return 0;
        }
 case 4: { 
            Rectangle *r = (Rectangle*)shapePtr;
               if (propertyType == AREA) return r->width * r->height;
     if (propertyType == PERIMETER) return 2 * (r->width + r->height);
            return 0;
        }
    }
    return -1;
}

int main()
 {
    Dot *dot = malloc(sizeof(Dot));
         Line *line = malloc(sizeof(Line));
Triangle *tri = malloc(sizeof(Triangle));
    Square *sq = malloc(sizeof(Square));
        Rectangle *rect = malloc(sizeof(Rectangle));

    dot->type = 0; dot->x = 6; dot->y = 8;
    line->type = 1; line->x1 = 0; line->y1 = 0; line->x2 = 6; line->y2 = 8;
    tri->type = 2; tri->x1 = 0; tri->y1 = 0; tri->x2 = 4; tri->y2 = 0; tri->x3 = 0; tri->y3 = 8;
    sq->type = 3; sq->x = 0; sq->y = 0; sq->side = 10;
    rect->type = 4; rect->x = 0; rect->y = 0; rect->width = 8; rect->height = 6;

    void *shapes[5] = {dot, line, tri, sq, rect};

    printf("Dot Distance from origin: %.2f\n", calculateProperty(shapes[0], DISTANCE));
    
printf("Line Length: %.2f\n", calculateProperty(shapes[1], LENGTH)); 
     printf("Triangle Area: %.2f\n", calculateProperty(shapes[2], AREA));
 printf("Triangle Perimeter: %.2f\n", calculateProperty(shapes[2], PERIMETER));
         printf("Square Area: %.2f\n", calculateProperty(shapes[3], AREA));
    printf("Square Perimeter: %.2f\n", calculateProperty(shapes[3], PERIMETER));
 printf("Rectangle Area: %.2f\n", calculateProperty(shapes[4], AREA));
    printf("Rectangle Perimeter: %.2f\n", calculateProperty(shapes[4], PERIMETER));

    free(dot); free(line); free(tri); free(sq); free(rect);
    return 0;
}