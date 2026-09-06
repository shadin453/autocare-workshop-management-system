#include "customer.h"

/* Customer Login Function */
int customerLogin(void)
{
    char userID[MAX_ID];
    char password[MAX_PASSWORD];
    FILE *file;
    User user;

    printf("\n====================================\n");
    printf("           CUSTOMER LOGIN\n");
    printf("====================================\n");

    printf("Enter Customer ID: ");
    scanf("%19s", userID);

    printf("Enter Password: ");
    scanf("%29s", password);

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return 0;
    }

    while (fscanf(file,
                  "%19[^|]|%49[^|]|%29[^|]|%29[^|]|%19[^|]|%99[^|]|%49[^\n]\n",
                  user.userID,
                  user.name,
                  user.password,
                  user.role,
                  user.contact,
                  user.email,
                  user.department) == 7)
    {
        if (strcmp(user.userID, userID) == 0 &&
            strcmp(user.password, password) == 0 &&
            strcmp(user.role, "Customer") == 0)
        {
            fclose(file);

            printf("\nLogin successful. Welcome, %s!\n", user.name);
            return 1;
        }
    }

    fclose(file);

    printf("\nInvalid Customer ID or Password!\n");
    return 0;
}

/* Book Appointment */
void bookAppointment(void)
{
    FILE *file;
    Appointment appointment;

    printf("\n====================================\n");
    printf("          BOOK APPOINTMENT\n");
    printf("====================================\n");

    printf("Enter Appointment ID: ");
    scanf("%19s", appointment.appointmentID);

    printf("Enter Customer ID: ");
    scanf("%19s", appointment.customerID);

    printf("Enter Vehicle Number: ");
    scanf("%29s", appointment.vehicleNo);

    printf("Enter Technician ID: ");
    scanf("%19s", appointment.technicianID);

    printf("Enter Service Type: ");
    scanf(" %49[^\n]", appointment.serviceType);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%14s", appointment.date);

    printf("Enter Time (HH:MM): ");
    scanf("%9s", appointment.time);

    strcpy(appointment.status, "Booked");

    file = fopen("appointments.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open appointments.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%s|%s|%s|%s|%s\n",
            appointment.appointmentID,
            appointment.customerID,
            appointment.vehicleNo,
            appointment.technicianID,
            appointment.serviceType,
            appointment.date,
            appointment.time,
            appointment.status);

    fclose(file);

    printf("\nAppointment booked successfully!\n");
}

/* View Customer Appointments */
void viewAppointments(void)
{
    FILE *file;
    Appointment appointment;
    char customerID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("         VIEW APPOINTMENTS\n");
    printf("====================================\n");

    printf("Enter Customer ID: ");
    scanf("%19s", customerID);

    file = fopen("appointments.txt", "r");

    if (file == NULL)
    {
        printf("\nNo appointment records found!\n");
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%19[^|]|%29[^|]|%19[^|]|%49[^|]|%14[^|]|%9[^|]|%19[^\n]\n",
                  appointment.appointmentID,
                  appointment.customerID,
                  appointment.vehicleNo,
                  appointment.technicianID,
                  appointment.serviceType,
                  appointment.date,
                  appointment.time,
                  appointment.status) == 8)
    {
        if (strcmp(appointment.customerID, customerID) == 0)
        {
            printf("\nAppointment ID : %s\n", appointment.appointmentID);
            printf("Vehicle Number : %s\n", appointment.vehicleNo);
            printf("Technician ID : %s\n", appointment.technicianID);
            printf("Service Type  : %s\n", appointment.serviceType);
            printf("Date          : %s\n", appointment.date);
            printf("Time          : %s\n", appointment.time);
            printf("Status        : %s\n", appointment.status);
            printf("------------------------------------\n");

            found = 1;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nNo appointments found for this Customer ID!\n");
    }
}

/* Reschedule Appointment */
void rescheduleAppointment(void)
{
    FILE *file;
    FILE *tempFile;
    Appointment appointment;
    char appointmentID[MAX_ID];
    char newDate[15];
    char newTime[10];
    int found = 0;

    printf("\n====================================\n");
    printf("       RESCHEDULE APPOINTMENT\n");
    printf("====================================\n");

    printf("Enter Appointment ID: ");
    scanf("%19s", appointmentID);

    file = fopen("appointments.txt", "r");

    if (file == NULL)
    {
        printf("\nNo appointment records found!\n");
        return;
    }

    tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL)
    {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%19[^|]|%29[^|]|%19[^|]|%49[^|]|%14[^|]|%9[^|]|%19[^\n]\n",
                  appointment.appointmentID,
                  appointment.customerID,
                  appointment.vehicleNo,
                  appointment.technicianID,
                  appointment.serviceType,
                  appointment.date,
                  appointment.time,
                  appointment.status) == 8)
    {
        if (strcmp(appointment.appointmentID, appointmentID) == 0)
        {
            printf("Enter New Date (DD-MM-YYYY): ");
            scanf("%14s", newDate);

            printf("Enter New Time (HH:MM): ");
            scanf("%9s", newTime);

            strcpy(appointment.date, newDate);
            strcpy(appointment.time, newTime);
            strcpy(appointment.status, "Rescheduled");

            found = 1;
        }

        fprintf(tempFile,
                "%s|%s|%s|%s|%s|%s|%s|%s\n",
                appointment.appointmentID,
                appointment.customerID,
                appointment.vehicleNo,
                appointment.technicianID,
                appointment.serviceType,
                appointment.date,
                appointment.time,
                appointment.status);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("appointments.txt");
        rename("temp.txt", "appointments.txt");

        printf("\nAppointment rescheduled successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("\nAppointment ID not found!\n");
    }
}

/* Cancel Appointment */
void cancelAppointment(void)
{
    FILE *file;
    FILE *tempFile;
    Appointment appointment;
    char appointmentID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("        CANCEL APPOINTMENT\n");
    printf("====================================\n");

    printf("Enter Appointment ID: ");
    scanf("%19s", appointmentID);

    file = fopen("appointments.txt", "r");

    if (file == NULL)
    {
        printf("\nNo appointment records found!\n");
        return;
    }

    tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL)
    {
        printf("\nError creating temporary file!\n");
        fclose(file);
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%19[^|]|%29[^|]|%19[^|]|%49[^|]|%14[^|]|%9[^|]|%19[^\n]\n",
                  appointment.appointmentID,
                  appointment.customerID,
                  appointment.vehicleNo,
                  appointment.technicianID,
                  appointment.serviceType,
                  appointment.date,
                  appointment.time,
                  appointment.status) == 8)
    {
        if (strcmp(appointment.appointmentID, appointmentID) == 0)
        {
            strcpy(appointment.status, "Cancelled");
            found = 1;
        }

        fprintf(tempFile,
                "%s|%s|%s|%s|%s|%s|%s|%s\n",
                appointment.appointmentID,
                appointment.customerID,
                appointment.vehicleNo,
                appointment.technicianID,
                appointment.serviceType,
                appointment.date,
                appointment.time,
                appointment.status);
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove("appointments.txt");
        rename("temp.txt", "appointments.txt");

        printf("\nAppointment cancelled successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("\nAppointment ID not found!\n");
    }
}

/* View Service History */
void viewServiceHistory(void)
{
    FILE *file;
    ServiceRecord record;
    char customerID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("         SERVICE HISTORY\n");
    printf("====================================\n");

    printf("Enter Customer ID: ");
    scanf("%19s", customerID);

    file = fopen("service_records.txt", "r");

    if (file == NULL)
    {
        printf("\nNo service records found!\n");
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%19[^|]|%19[^|]|%29[^|]|%19[^|]|%199[^|]|%199[^|]|%199[^|]|%199[^|]|%199[^|]|%f|%19[^\n]\n",
                  record.serviceID,
                  record.appointmentID,
                  record.customerID,
                  record.vehicleNo,
                  record.technicianID,
                  record.diagnostics,
                  record.repairs,
                  record.parts,
                  record.recommendation,
                  record.notes,
                  &record.charge,
                  record.status) == 12)
    {
        if (strcmp(record.customerID, customerID) == 0)
        {
            printf("\nService ID       : %s\n", record.serviceID);
            printf("Appointment ID   : %s\n", record.appointmentID);
            printf("Vehicle Number   : %s\n", record.vehicleNo);
            printf("Technician ID    : %s\n", record.technicianID);
            printf("Diagnosis        : %s\n", record.diagnostics);
            printf("Repair           : %s\n", record.repairs);
            printf("Parts Used       : %s\n", record.parts);
            printf("Recommendation   : %s\n", record.recommendation);
            printf("Notes            : %s\n", record.notes);
            printf("Charge           : %.2f\n", record.charge);
            printf("Status           : %s\n", record.status);
            printf("------------------------------------\n");

            found = 1;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nNo service history found for this Customer ID!\n");
    }
}

/* View Billing */
void viewBilling(void)
{
    FILE *file;
    Bill bill;
    char appointmentID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("            VIEW BILLING\n");
    printf("====================================\n");

    printf("Enter Appointment ID: ");
    scanf("%19s", appointmentID);

    file = fopen("billing.txt", "r");

    if (file == NULL)
    {
        printf("\nNo billing records found!\n");
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%19[^|]|%f|%f|%f|%19[^|]|%19[^\n]\n",
                  bill.billID,
                  bill.appointmentID,
                  &bill.serviceCharge,
                  &bill.partsCost,
                  &bill.total,
                  bill.paymentStatus,
                  bill.date) == 7)
    {
        if (strcmp(bill.appointmentID, appointmentID) == 0)
        {
            printf("\nBill ID          : %s\n", bill.billID);
            printf("Appointment ID   : %s\n", bill.appointmentID);
            printf("Service Charge   : %.2f\n", bill.serviceCharge);
            printf("Parts Cost       : %.2f\n", bill.partsCost);
            printf("Total Amount     : %.2f\n", bill.total);
            printf("Payment Status   : %s\n", bill.paymentStatus);
            printf("Date             : %s\n", bill.date);
            printf("------------------------------------\n");

            found = 1;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nNo billing record found for this Appointment ID!\n");
    }
}

/* Customer Menu */
void customerMenu(void)
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("           CUSTOMER MENU\n");
        printf("====================================\n");
        printf("1. Book Appointment\n");
        printf("2. View Appointments\n");
        printf("3. Reschedule Appointment\n");
        printf("4. Cancel Appointment\n");
        printf("5. View Service History\n");
        printf("6. View Billing\n");
        printf("0. Logout\n");
        printf("====================================\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");
            clearInputBuffer();
            choice = -1;
            continue;
        }

        switch (choice)
        {
            case 1:
                bookAppointment();
                break;

            case 2:
                viewAppointments();
                break;

            case 3:
                rescheduleAppointment();
                break;

            case 4:
                cancelAppointment();
                break;

            case 5:
                viewServiceHistory();
                break;

            case 6:
                viewBilling();
                break;

            case 0:
                printf("\nCustomer logged out successfully!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);
}

