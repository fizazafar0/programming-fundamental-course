//Name: fiza zafar
//roll no : 26k-0048
//Question #1:Cinema hall seat booking mangement system
#include <stdio.h>
int main () {
int seat[100][100];
int rows, cols;
int k;
printf("enter number of rows: ");
scanf("%d", &rows);
printf("enter number of cols: ");
scanf("%d", &cols);
printf("enter seating status(0 for available 1 for booked): ");
for(int i=0; i < rows; i++){
    for(int j=0;j < cols; j++){
        scanf("%d", &seat[i][j]);
    }
}
// display seating arrangement
printf("\nseating arrangement (_ = free, x= booked):\n");
printf("    ");
for(int j=0; j < cols; j++)printf("%d", j);
printf("\n");
for(int i=0; i < rows; i++){
    printf("R%d: ", i);
    for(int j=0; j< cols; j++){
        if(seat[i][j]==0) printf("-");//avaible
        else printf("x");
    }
    printf("\n");
}
//seat availablity
int totalfree = 0;
printf("\nfree seats per row: ");
for(int i = 0; i< rows ;i++){
    int freeinrow = 0;
    for(int j =0; j< cols; j++){
        if (seat[i][j]== 0) freeinrow++;
    }
    printf("%d", freeinrow);
    totalfree+= freeinrow;
}
printf("total free : %d\n", totalfree);
// group booking
printf("\nenter number of customers in group (k): ");
scanf("%d", &k);
if(k <=0 || k > cols){
    printf("invalid group size! must be > 0 and <= %d\n", cols);
    return 0;
}
//seat allocation 
int middle = rows/2;
int order[100];
int orderindex = 0;
for( int d= 0; d < rows; d++){
    int r1 = middle - d;
    int r2 = middle + d;
    if(d==0){
        if(r1 >= 0 && r1 < rows )order[orderindex++]= r1;
    } else {
         if(r1 >= 0 && r1 < rows && r2 >= 0 && r2 < rows ){
            if(r1 < r2){
                order[orderindex++] = r1;
                  order[orderindex++] = r2;
            }else {
                order[orderindex++] = r2;
                  order[orderindex++] = r1;
            }
         }else if (r1 >= 0 && r1 < rows ){
            order[orderindex++] = r1;
            }else if (r1 >= 0 && r1 < rows ){
            order[orderindex++] = r2;
         }
    }
}
int foundrow = -1;
int foundstartseat = -1;
for(int o=0 ; o < rows ; o++){
    int i = order[0];
    int count = 0;
    for(int j=0; j < cols; j++){
        if (seat[i][j]==0){
count++;
if(count==k){
    foundrow = i;
    foundstartseat = j-k+1;
    break;
}
        
}else{
        count=0;
    }
}
if(foundrow!= -1)break;
}
if (foundrow!= -1){
    printf("\ngroup of %d seated in row %d, seats %d to \n%d", k,
    foundrow, foundstartseat,foundstartseat + k-1);
for(int j = foundstartseat; j < foundstartseat +k;j++){
    seat[foundrow][j] = 1;
}
printf("\nupdated seating arrangment:\n");
printf("   ");
for(int j =0; j < cols;j++){
    printf("%d", j);
    for(int i =0; i < rows ; i++){
if (seat[i][j] == 0)
printf("-");
else printf("x");
    }
    printf("\n");
}
int remaining =0;
for(int i=0; i < rows; i++){
for(int j =0 ; j < cols ; j++){

if(seat[i][j]== 0){
remaining++;
}
}
}
printf("\nremaining available seats : %d\n", remaining);
}else {
    printf("\nbooking failed: no row contains %d consecutive available. seating plan unchanged.\n", k);
}
return 0;
}