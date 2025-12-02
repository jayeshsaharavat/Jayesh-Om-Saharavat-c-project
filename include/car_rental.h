#ifndef CAR_RENTAL_H
#define CAR_RENTAL_H

#include <time.h>

#define MAX_CARS 100
#define LATE_FEE 50

typedef struct {
    int id;
    char name[50];
    int rentPerDay;
    char status[20];
    time_t rentDate;      // Timestamp when rented
    int daysRented;       // Days rented (calculated on return)
} Car;

void addCar(Car cars[], int *count);
void showCars(Car cars[], int count);
void rentCar(Car cars[], int count);
void returnCar(Car cars[], int count);
time_t getCurrentTime();

#endif
