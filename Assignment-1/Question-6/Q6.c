#include <stdio.h>

int main() {
    char vType, member, disabled, stationAvail;
    int soc, reqLevel, parkingHours, currentTime;
    int requiredCharging;
    int isPeak, rate;
    float chargingCost = 0, parkingCost = 0, discount = 0, finalAmount = 0;
    char priority[30] = "Normal Charging";

    printf("Vehicle type (E=Electric, H=Hybrid): ");
    scanf(" %c", &vType);
    printf("Battery charge level SOC %%: ");
    scanf("%d", &soc);
    printf("Required charging level %%: ");
    scanf("%d", &reqLevel);
    printf("Expected parking duration in hours: ");
    scanf("%d", &parkingHours);
    printf("Current time in 24-hour format (0-23): ");
    scanf("%d", &currentTime);
    printf("Parking membership (Y/N): ");
    scanf(" %c", &member);
    printf("Disabled-person priority (Y/N): ");
    scanf(" %c", &disabled);
    printf("Charging station available (Y/N): ");
    scanf(" %c", &stationAvail);

    // Rule 1: Station unavailable
    if(stationAvail=='N' || stationAvail=='n') {
        if(vType=='H' || vType=='h') {
            printf("Charging unavailable - Parking only.\n");
        } else {
            printf("No charging slot available.\n");
        }
        // Still parking can be done, so we don't return
    } else {
        // Rule 2: Hybrid check
        if((vType=='H' || vType=='h') && soc >= 40) {
            printf("Vehicle does not qualify for EV charging.\n");
            return 0;
        }
        // Rule 3: Required charging calculation
        requiredCharging = reqLevel - soc;
        if(requiredCharging <= 0) {
            printf("No charging required.\n");
            return 0;
        }

        // Rule 4: Priority Assignment
        int isEmergency = 0;
        if(soc <= 15 && reqLevel >= 80) {
            isEmergency = 1;
            printf("Priority: Emergency Charging Priority\n");
        } else if((disabled=='Y' || disabled=='y') || ((member=='Y' || member=='y') && soc <= 30)) {
            printf("Priority: Priority Charging\n");
        } else {
            printf("Priority: Normal Charging\n");
        }

        // Rule 5: Rates
        if(currentTime >= 17 && currentTime <= 22) { // 5 PM to 10 PM
            isPeak = 1;
            rate = 50;
            printf("Peak hours (5 PM to 10 PM) - Rate Rs. 50/unit\n");
        } else {
            isPeak = 0;
            rate = 35;
            printf("Off-peak hours - Rate Rs. 35/unit\n");
        }

        chargingCost = requiredCharging * rate;

        // Discount
        if(isEmergency == 0) { // No discount for emergency
            if(isPeak==0 && (member=='Y' || member=='y')) {
                discount = chargingCost * 20 / 100;
                chargingCost = chargingCost - discount;
                printf("Member discount 20%% on charging: %.2f\n", discount);
            } else if(isPeak==1 && (member=='Y' || member=='y')) {
                discount = chargingCost * 10 / 100;
                chargingCost = chargingCost - discount;
                printf("Member discount 10%% on charging: %.2f\n", discount);
            }
        }
        printf("Required Charging Units: %d\n", requiredCharging);
        printf("Charging Cost: %.2f\n", chargingCost);
    }

    // Parking charges
    if(parkingHours <= 2) parkingCost = 200;
    else if(parkingHours <= 5) parkingCost = 400;
    else parkingCost = 700;

    printf("Parking Cost before discount: %.2f\n", parkingCost);

    float parkingDiscount = 0;
    if(disabled=='Y' || disabled=='y') {
        parkingDiscount = parkingCost;
        parkingCost = 0;
        printf("Free parking for disabled priority\n");
    } else if(member=='Y' || member=='y') {
        parkingDiscount = parkingCost * 20 / 100;
        parkingCost = parkingCost - parkingDiscount;
        printf("Member parking discount 20%%: %.2f\n", parkingDiscount);
    }

    finalAmount = chargingCost + parkingCost;

    printf("\n--- FINAL BILL ---\n");
    printf("Vehicle Type: %c\n", vType);
    printf("Current Battery: %d%%\n", soc);
    printf("Required Level: %d%%\n", reqLevel);
    printf("Parking Hours: %d\n", parkingHours);
    printf("Parking Cost: %.2f\n", parkingCost);
    printf("Charging Cost: %.2f\n", chargingCost);
    printf("Final Payable Amount: %.2f\n", finalAmount);

    if(parkingHours > 8) {
        printf("Long-stay warning: Please relocate your vehicle after charging.\n");
    } else {
        printf("Standard parking duration.\n");
    }

    return 0;
}