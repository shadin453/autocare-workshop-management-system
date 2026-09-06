#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_NAME 50
#define MAX_PASSWORD 30
#define MAX_CONTACT 20
#define MAX_EMAIL 100
#define MAX_ROLE 30
#define MAX_DEPARTMENT 50

#define MAX_ID 20
#define MAX_VEHICLE 30
#define MAX_SERVICE_TYPE 50
#define MAX_DATE 15
#define MAX_TIME 10
#define MAX_STATUS 20

/* User Structure */
typedef struct {
    char userID[MAX_ID];
    char name[MAX_NAME];
    char password[MAX_PASSWORD];
    char role[MAX_ROLE];
    char contact[MAX_CONTACT];
    char email[MAX_EMAIL];
    char department[MAX_DEPARTMENT];
} User;

/* Appointment Structure */
typedef struct {
    char appointmentID[MAX_ID];
    char customerID[MAX_ID];
    char vehicleNo[MAX_VEHICLE];
    char technicianID[MAX_ID];
    char serviceType[MAX_SERVICE_TYPE];
    char date[MAX_DATE];
    char time[MAX_TIME];
    char status[MAX_STATUS];
} Appointment;

/* Technician Schedule Structure */
typedef struct {
    char technicianID[MAX_ID];
    char date[MAX_DATE];
    char time[MAX_TIME];
    char availabilityStatus[MAX_STATUS];
} Schedule;

/* Service Record Structure */
typedef struct {
    char serviceID[MAX_ID];
    char appointmentID[MAX_ID];
    char customerID[MAX_ID];
    char vehicleNo[MAX_VEHICLE];
    char technicianID[MAX_ID];
    char diagnostics[200];
    char repairs[200];
    char parts[200];
    char recommendation[200];
    char notes[200];
    float charge;
    char status[MAX_STATUS];
} ServiceRecord;

/* Spare Parts Structure */
typedef struct {
    char partID[MAX_ID];
    char name[MAX_NAME];
    char category[50];
    int quantity;
    float unitPrice;
    char supplier[100];
    char warrantyStart[MAX_DATE];
    char warrantyExpiry[MAX_DATE];
} Part;

/* Billing Structure */
typedef struct {
    char billID[MAX_ID];
    char appointmentID[MAX_ID];
    float serviceCharge;
    float partsCost;
    float total;
    char paymentStatus[MAX_STATUS];
    char date[MAX_DATE];
} Bill;

/* Common Function */
void clearInputBuffer(void);

#endif