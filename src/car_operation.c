#include <stdio.h>
#include <string.h>
#include <time.h>
#include "car_rental.h"

time_t getCurrentTime() {
    return time(NULL);
}

void addCar(Car cars[], int *count) {
    if (*count >= MAX_CARS) {
        printf("Maximum cars limit reached!\n");
        return;
    }
    
    Car *newCar = &cars[*count];
    printf("Enter Car ID: ");
    scanf("%d", &newCar->id);
    printf("Enter Car Name: ");
    scanf(" %[^\n]", newCar->name);  // Read string with spaces
    printf("Enter Rent per Day (Rs): ");
    scanf("%d", &newCar->rentPerDay);
    
    strcpy(newCar->status, "Available");
    newCar->rentDate = 0;
    newCar->daysRented = 0;
    
    (*count)++;
    printf("Car added successfully!\n");
}

void showCars(Car cars[], int count) {
    if (count == 0) {
        printf("No cars available!\n");
        return;
    }
    
    printf("\n=== CARS LIST ===\n");
    printf("ID | Name           | Rent/Day | Status    | Days Rented\n");
    printf("--|---------------|----------|-----------|------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-2d| %-14s | %-8d | %-9s | %-10d\n", 
               cars[i].id, cars[i].name, cars[i].rentPerDay, 
               cars[i].status, cars[i].daysRented);
    }
}

void rentCar(Car cars[], int count) {
    if (count == 0) {
        printf("No cars available to rent!\n");
        return;
    }
    
    int id;
    printf("Enter car ID to rent: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (cars[i].id == id && strcmp(cars[i].status, "Available") == 0) {
            strcpy(cars[i].status, "Rented");
            cars[i].rentDate = getCurrentTime();
            cars[i].daysRented = 0;
            printf("Car rented successfully on %s", ctime(&cars[i].rentDate));
            return;
        }
    }
    printf("Car ID %d not found or not available!\n", id);
}

void returnCar(Car cars[], int count) {
    if (count == 0) {
        printf("No cars to return!\n");
        return;
    }
    
    int id;
    printf("Enter car ID to return: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (cars[i].id == id && strcmp(cars[i].status, "Rented") == 0) {
            time_t currentTime = getCurrentTime();
            double daysDiff = difftime(currentTime, cars[i].rentDate) / (60*60*24);
            cars[i].daysRented = (int)(daysDiff + 0.5);  // Round to nearest day
            
            int totalCost = cars[i].rentPerDay * cars[i].daysRented;
            int lateFee = (daysDiff > 7) ? LATE_FEE : 0;
            if (lateFee > 0) totalCost += lateFee;
            
            printf("\n=== BILL RECEIPT ===\n");
            printf("Car: %s (ID: %d)\n", cars[i].name, cars[i].id);
            printf("Rented: %s", ctime(&cars[i].rentDate));
            printf("Returned: %s", ctime(&currentTime));
            printf("Days Rented: %d\n", cars[i].daysRented);
            printf("Rent per Day: Rs. %d\n", cars[i].rentPerDay);
            printf("Late Fee (>7 days): Rs. %d\n", lateFee);
            printf("TOTAL BILL: Rs. %d\n", totalCost);
            printf("====================\n");
            
            strcpy(cars[i].status, "Available");
            printf("Car returned successfully!\n");
            return;
        }
    }
    printf("Car ID %d not found or not rented!\n", id);
}
