#include <stdio.h>
int main() {
    float q, p, s, d, a, t, final_bill;
    printf("Enter quantity: ");
    scanf("%f", &q);
    printf("Enter price per item: ");
    scanf("%f", &p);
    printf("Enter discount percentage: ");
    scanf("%f", &d);
    printf("Enter tax percentage: ");
    scanf("%f", &t);

    if(q <= 0 || p <= 0 || d < 0 || t < 0) {
        printf("Invalid value! Calculation terminated.\n");
        return 0;
    }
    s = q * p;
    a = s - (s * d / 100);
    final_bill = a + (a * t / 100);

    printf("\n--- Bill ---\n");
    printf("Subtotal (s=q*p): %.2f\n", s);
    printf("Discounted Amount: %.2f\n", a);
    printf("Final Bill: %.2f\n", final_bill);
    return 0;
}