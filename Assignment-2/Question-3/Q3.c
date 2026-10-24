//Name: fiza zafar
//roll no : 26k-0048
//Question #3: greenhouse temperature monitoring system


#include <stdio.h>
#define MAX 100

// Task 2: Input Function
void inputReadings(int sensors, int readings, int temp[MAX][MAX]) {
    for (int i = 0; i < sensors; i++) {
        printf("Enter %d readings for Sensor %d: ", readings, i+1);
        for (int j = 0; j < readings; j++) {
            scanf("%d", &temp[i][j]);
        }
    }
}

// Task 3: Sensor Analysis Function
void analyzeSensor(int readings, int sensorData[MAX], int *total, double *avg, int *max, int *min, int *critical, int *warning, int *longestStreak) {
    *total = 0;
    *max = sensorData[0];
    *min = sensorData[0];
    *critical = 0;
    *warning = 0;
    *longestStreak = 0;
    
    int currentStreak = 0;

    for (int j = 0; j < readings; j++) {
        int t = sensorData[j];
        *total += t;

        if (t > *max) *max = t;
        if (t < *min) *min = t;

        if (t >= 40) (*critical)++;
        if (t >= 35 && t <= 39) (*warning)++;

        // Longest streak of >=35
        if (t >= 35) {
            currentStreak++;
            if (currentStreak > *longestStreak) {
                *longestStreak = currentStreak;
            }
        } else {
            currentStreak = 0;
        }
    }
    *avg = (double)(*total) / readings;
}

// Task 5: Highest Average Function
int findHighestAvgSensor(int sensors, double avgs[MAX]) {
    int index = 0;
    double highest = avgs[0];
    for (int i = 1; i < sensors; i++) {
        if (avgs[i] > highest) {
            highest = avgs[i];
            index = i;
        }
    }
    return index; // 0-based index
}

int main() {
    int sensors, readings;
    int temp[MAX][MAX];
    double avgs[MAX];

    // Task 1: Input Data
    printf("Enter number of sensors: ");
    scanf("%d", &sensors);
    printf("Enter number of hourly readings: ");
    scanf("%d", &readings);

    inputReadings(sensors, readings, temp);

    printf("\n--- Individual Reports ---\n");
    for (int i = 0; i < sensors; i++) {
        int total, max, min, critical, warning, longest;
        double avg;

        analyzeSensor(readings, temp[i], &total, &avg, &max, &min, &critical, &warning, &longest);
        avgs[i] = avg;

        // Task 4: Individual Reports
        printf("Sensor %d: Total=%d Avg=%.2f Max=%d Min=%d\n", i+1, total, avg, max, min);
        printf("          Critical=%d Warning=%d Longest hot streak=%d\n", critical, warning, longest);
    }

    // Task 6: Final Report
    int highestIndex = findHighestAvgSensor(sensors, avgs);
    printf("\nHighest average: Sensor %d (%.2f)\n", highestIndex + 1, avgs[highestIndex]);

    return 0;
}