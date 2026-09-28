#include <stdio.h>

int main() {
    int totalVehicles, i;
    char vType, uCat, permit, isEmergency;
    int zoneA_cap = 20, zoneB_cap = 40, zoneC_cap = 15;
    int zoneA_occ = 0, zoneB_occ = 0, zoneC_occ = 0;
    int totalProcessed = 0, accepted = 0, rejected = 0;
    int cars = 0, bikes = 0, vans = 0;

    printf("Enter number of vehicles expected: ");
    scanf("%d", &totalVehicles);

    for(i = 1; i <= totalVehicles; i++) {
        printf("\n--- Vehicle %d ---\n", i);

        // Input validation loop
        while(1) {
            printf("Vehicle type (C=Car, B=Bike, V=Van): ");
            scanf(" %c", &vType);
            if(vType=='C' || vType=='B' || vType=='V' || vType=='c' || vType=='b' || vType=='v') break;
            printf("Invalid vehicle type! Enter again.\n");
        }
        while(1) {
            printf("User Category (F=Faculty, S=Student, G=Visitor): ");
            scanf(" %c", &uCat);
            if(uCat=='F' || uCat=='S' || uCat=='G' || uCat=='f' || uCat=='s' || uCat=='g') break;
            printf("Invalid category! Enter again.\n");
        }
        while(1) {
            printf("Valid permit? (Y/N): ");
            scanf(" %c", &permit);
            if(permit=='Y' || permit=='N' || permit=='y' || permit=='n') break;
            printf("Invalid! Enter Y or N.\n");
        }

        totalProcessed++;
        int needSpace = (vType=='V' || vType=='v')? 2 : 1;
        int canPark = 0;
        char assignedZone = 'X';

        // Check permit
        if(permit=='N' || permit=='n') {
            printf("Is Emergency Vehicle? (Y/N): ");
            scanf(" %c", &isEmergency);
            if(isEmergency!='Y' && isEmergency!='y') {
                printf("Rejected: Invalid permit\n");
                rejected++;
                continue;
            }
        }

        // Faculty -> Zone A
        if((uCat=='F' || uCat=='f')) {
            if(zoneA_occ + needSpace <= zoneA_cap) {
                // Faculty van condition
                if((vType=='V' || vType=='v')) {
                    // Faculty van can use Zone A only if space available
                    canPark = 1; assignedZone = 'A';
                } else {
                    canPark = 1; assignedZone = 'A';
                }
            }
        }
        // Student -> Zone B, but Student Van -> Zone C
        else if((uCat=='S' || uCat=='s')) {
            if((vType=='V' || vType=='v')) {
                // Student van redirected to Zone C
                if(zoneC_occ + 2 <= zoneC_cap) {
                    canPark = 1; assignedZone = 'C';
                }
            } else {
                // Student Car/Bike -> Zone B
                if(zoneB_occ + needSpace <= zoneB_cap) {
                    canPark = 1; assignedZone = 'B';
                }
            }
        }
        // Visitor -> Zone C
        else if((uCat=='G' || uCat=='g')) {
            if(zoneC_occ + needSpace <= zoneC_cap) {
                if((vType=='V' || vType=='v') && zoneC_cap - zoneC_occ < 2) {
                    canPark = 0;
                } else {
                    canPark = 1; assignedZone = 'C';
                }
            }
        }

        if(canPark) {
            if(assignedZone=='A') zoneA_occ += needSpace;
            if(assignedZone=='B') zoneB_occ += needSpace;
            if(assignedZone=='C') zoneC_occ += needSpace;

            if(vType=='C' || vType=='c') cars++;
            if(vType=='B' || vType=='b') bikes++;
            if(vType=='V' || vType=='v') vans++;

            accepted++;
            int remaining = 0;
            if(assignedZone=='A') remaining = zoneA_cap - zoneA_occ;
            if(assignedZone=='B') remaining = zoneB_cap - zoneB_occ;
            if(assignedZone=='C') remaining = zoneC_cap - zoneC_occ;

            printf("Accepted: Assigned Zone %c, Remaining in Zone %c: %d\n", assignedZone, assignedZone, remaining);
        } else {
            printf("Rejected: No suitable zone / No space available\n");
            rejected++;
        }
    }

    printf("\n--- PARKING SUMMARY ---\n");
    printf("Total Processed: %d\n", totalProcessed);
    printf("Total Accepted: %d, Total Rejected: %d\n", accepted, rejected);
    printf("Cars: %d, Bikes: %d, Vans: %d\n", cars, bikes, vans);
    printf("Zone A Occupied: %d/%d, Remaining: %d\n", zoneA_occ, zoneA_cap, zoneA_cap-zoneA_occ);
    printf("Zone B Occupied: %d/%d, Remaining: %d\n", zoneB_occ, zoneB_cap, zoneB_cap-zoneB_occ);
    printf("Zone C Occupied: %d/%d, Remaining: %d\n", zoneC_occ, zoneC_cap, zoneC_cap-zoneC_occ);

    // Highest occupancy
    if(zoneA_occ >= zoneB_occ && zoneA_occ >= zoneC_occ) printf("Highest Occupancy: Zone A\n");
    else if(zoneB_occ >= zoneA_occ && zoneB_occ >= zoneC_occ) printf("Highest Occupancy: Zone B\n");
    else printf("Highest Occupancy: Zone C\n");

    if(zoneA_occ==zoneA_cap && zoneB_occ==zoneB_cap && zoneC_occ==zoneC_cap)
        printf("Campus parking facility is FULL\n");
    else
        printf("Campus parking facility is NOT full\n");

    return 0;
}