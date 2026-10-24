//Name: fiza zafar
//roll no : 26k-0048
//Question #4:bakery festival management system


#include <stdio.h>

//int getValidDays()
int getValidDays() {
    int days;
    do {
        printf("Enter number of festival days (1-7): ");
        scanf("%d", &days);
        if (days < 1 || days > 7) {
            printf("Invalid! Please enter between 1 and 7.\n");
        }
    } while (days < 1 || days > 7);
    return days;
}

//float calculateDailySales(int dayNumber)
float calculateDailySales(int dayNumber) {
    int orders;
    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orders);

    float total = 0, highest = 0;
    
    for (int i = 1; i <= orders; i++) {
        float amount;
        do {
            printf("Order %d amount: Rs. ", i);
            scanf("%f", &amount);
            if (amount <= 0) {
                printf("Invalid amount! Must be greater than 0.\n");
            }
        } while (amount <= 0);

        total += amount;
        if (i == 1 || amount > highest) {
            highest = amount;
        }
    }

    float average = total / orders;
    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", average);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

// int findHighestSalesDay(float dailySales[], int numberOfDays)
int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int highestDay = 1;
    float highestSale = dailySales[0];

    for (int i = 1; i < numberOfDays; i++) {
        if (dailySales[i] > highestSale) {
            highestSale = dailySales[i];
            highestDay = i + 1; // Day number starts from 1
        }
    }
    return highestDay;
}

//void displayBarChart(float dailySales[], int numberOfDays)
void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\n------ DAILY SALES BAR CHART ------\n");
    for (int i = 0; i < numberOfDays; i++) {
        int stars = (int)(dailySales[i] / 100);
        printf("Day %d: ", i + 1);
        for (int j = 0; j < stars; j++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[i]);
    }
}

int main() {
    float dailySales[7];
    
    int days = getValidDays();

    //Daily Order Processing
    for (int i = 0; i < days; i++) {
        dailySales[i] = calculateDailySales(i + 1);
    }

    //Festival Summary
    float festivalTotal = 0;
    for (int i = 0; i < days; i++) {
        festivalTotal += dailySales[i];
    }

    int bestDay = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", bestDay);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[bestDay - 1]);

    //Bar Chart
    displayBarChart(dailySales, days);

    return 0;
}