#include<stdio.h>
int main () {
int N, i, nights, rate, season, room;
float total, discount;
long hoteltotal = 0;
printf("enter N: ");
scanf("%d", &N);
for(i = 1; i<=N; i++){
    printf("\nGuest %d season (peak =1 / off = 0): ",i);
    scanf("%d", &season);
    printf("room (standard = 1/deluxe = 2/suite = 3): ");
    scanf("%d", &room);
    printf("Nights: ");
    scanf("%d", &nights);
    
    if(season == 1){
        if(room == 1)
        rate = 5000;
         else if(room == 2)
        rate = 8000;
        else if(room == 3)
        rate = 12000;
        else rate = 0;}
        else{
            if(room== 1)
rate = 3000;
if(room == 2)
rate = 5000;
if(room == 3)
rate = 8000;
else rate = 0;}
    total = nights * rate;
}
 if(nights > 7){
    discount = total * 15 / 100;
    total = total - discount;
 }
 printf("final price: %.2f\n", total);
 hoteltotal = hoteltotal + total;
printf("\nhotel total revenue = %ld\n", hoteltotal);
return 0;
}
    