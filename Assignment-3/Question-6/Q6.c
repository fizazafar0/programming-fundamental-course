#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long sum;
    int a;
    int b;
} Node;
typedef struct {
    Node *arr;
      int size;
    int capacity;
} Heap;
void heap_swap(Node *x, Node *y) {
    Node t = *x; *x = *y; *y = t;
}

void heap_push(Heap *h, unsigned long long sum, int a, int b) {
    if (h->size == h->capacity) {
        h->capacity = h->capacity == 0 ? 16 : h->capacity * 2;
 h->arr = realloc(h->arr, h->capacity * sizeof(Node));
        if (!h->arr) { printf("Memory allocation failed\n"); exit(1); }
    }
 int i = h->size++;
 h->arr[i].sum = sum;
    h->arr[i].a = a;
    h->arr[i].b = b;
    
    while (i > 0) {
  int parent = (i - 1) / 2;
        if (h->arr[i].sum < h->arr[parent].sum) {
            heap_swap(&h->arr[i], &h->arr[parent]);
            i = parent;
        } else break;
    }
}

Node heap_pop(Heap *h) {
 Node top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
int i = 0;
    while (1) {
        int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
  if (left < h->size && h->arr[left].sum < h->arr[smallest].sum)
            smallest = left;
 if (right < h->size && h->arr[right].sum < h->arr[smallest].sum)
            smallest = right;
     if (smallest != i) {
            heap_swap(&h->arr[i], &h->arr[smallest]);
            i = smallest;
        } else break;
    }
    return top;
}

static unsigned long long cube(int x) {
       unsigned long long v = (unsigned long long)x;
    return v * v * v;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
           printf("Usage: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N < 1) {
        printf("N must be >= 1\n");
        return 1;
    }

    Heap h = {NULL, 0, 0};
    heap_push(&h, cube(1) + cube(1), 1, 1);

    unsigned long long prev_sum = 0;
    int prev_a = -1, prev_b = -1;
    int prev_reported = 0; 
    int found = 0;

    while (found < N) {
        Node cur = heap_pop(&h);

        
        heap_push(&h, cube(cur.a) + cube(cur.b + 1), cur.a, cur.b + 1);
        if (cur.a == cur.b) {
            heap_push(&h, cube(cur.a + 1) + cube(cur.a + 1), cur.a + 1, cur.a + 1);
        }

        if (cur.sum == prev_sum) {
            if (!prev_reported && !(cur.a == prev_a && cur.b == prev_b)) {
                found++;
     printf("%d. %llu = %d^3 + %d^3 = %d^3 + %d^3\n",
                       found, cur.sum, prev_a, prev_b, cur.a, cur.b);
                prev_reported = 1;
            }
        } else {
            prev_reported = 0;
        }

        prev_sum = cur.sum;
        prev_a = cur.a;
        prev_b = cur.b;
    }

    free(h.arr);
    return 0;
}