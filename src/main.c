#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "car_rental.h"

int main() {
    Car cars[MAX_CARS];
    int carCount = 0;
    int choice;
    
    printf("=== Car Rental Management System ===\n");
    
    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Add Car\n");
        printf("2. Show All Cars\n");
        printf("3. Rent Car (Record Date)\n");
        printf("4. Return Car (Generate Bill)\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Clear input buffer
            printf("Invalid input! Please enter a number.\n");
            continue;
        }
        
        switch(choice) {
            case 1: 
                addCar(cars, &carCount);
                break;
            case 2: 
                showCars(cars, carCount);
                break;
            case 3: 
                rentCar(cars, carCount);
                break;
            case 4: 
                returnCar(cars, carCount);
                break;
            case 5: 
                printf("\nThank you for using Car Rental System!\n");
                printf("Exiting safely...\n");
                exit(0);
            default: 
                printf("Invalid option! Choose 1-5 only.\n");
        }
        
        printf("\nPress Enter to continue...");
        getchar();  // Wait for user
        while (getchar() != '\n');  // Clear buffer
    }
    return 0;
}
