#include "technician.h"

/* Technician Login */
int technicianLogin(void)
{
    char userID[MAX_ID];
    char password[MAX_PASSWORD];
    FILE *file;
    User user;

    printf("\n====================================\n");
    printf("          TECHNICIAN LOGIN\n");
    printf("====================================\n");

    printf("Enter Technician ID: ");
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
            strcmp(user.role, "Technician") == 0)
        {
            fclose(file);

            printf("\nLogin successful. Welcome, %s!\n", user.name);
            return 1;
        }
    }

    fclose(file);

    printf("\nInvalid Technician ID or Password!\n");
    return 0;
}

/* View Assigned Appointments */
void viewAssignedAppointments(void)
{
    FILE *file;
    Appointment appointment;
    char technicianID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("     ASSIGNED APPOINTMENTS\n");
    printf("====================================\n");

    printf("Enter Technician ID: ");
    scanf("%19s", technicianID);

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
        if (strcmp(appointment.technicianID, technicianID) == 0)
        {
            printf("\nAppointment ID : %s\n", appointment.appointmentID);
            printf("Customer ID    : %s\n", appointment.customerID);
            printf("Vehicle Number : %s\n", appointment.vehicleNo);
            printf("Service Type   : %s\n", appointment.serviceType);
            printf("Date           : %s\n", appointment.date);
            printf("Time           : %s\n", appointment.time);
            printf("Status         : %s\n", appointment.status);
            printf("------------------------------------\n");

            found = 1;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nNo appointments assigned to this Technician!\n");
    }
}

/* Update Appointment Status */
void updateAppointmentStatus(void)
{
    FILE *file;
    FILE *tempFile;
    Appointment appointment;
    char appointmentID[MAX_ID];
    char newStatus[20];
    int found = 0;

    printf("\n====================================\n");
    printf("      UPDATE APPOINTMENT STATUS\n");
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
            printf("Enter New Status: ");
            scanf(" %19[^\n]", newStatus);

            strcpy(appointment.status, newStatus);
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

    if (found == 1)
    {
        remove("appointments.txt");
        rename("temp.txt", "appointments.txt");

        printf("\nAppointment status updated successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("\nAppointment ID not found!\n");
    }
}

/* Create Service Record */
void createServiceRecord(void)
{
    FILE *file;
    ServiceRecord record;

    printf("\n====================================\n");
    printf("        CREATE SERVICE RECORD\n");
    printf("====================================\n");

    printf("Enter Service ID: ");
    scanf("%19s", record.serviceID);

    printf("Enter Appointment ID: ");
    scanf("%19s", record.appointmentID);

    printf("Enter Customer ID: ");
    scanf("%19s", record.customerID);

    printf("Enter Vehicle Number: ");
    scanf("%29s", record.vehicleNo);

    printf("Enter Technician ID: ");
    scanf("%19s", record.technicianID);

    printf("Enter Diagnostics: ");
    scanf(" %199[^\n]", record.diagnostics);

    printf("Enter Repairs: ");
    scanf(" %199[^\n]", record.repairs);

    printf("Enter Parts Used: ");
    scanf(" %199[^\n]", record.parts);

    printf("Enter Recommendation: ");
    scanf(" %199[^\n]", record.recommendation);

    printf("Enter Notes: ");
    scanf(" %199[^\n]", record.notes);

    printf("Enter Service Charge: ");
    scanf("%f", &record.charge);

    strcpy(record.status, "In Progress");

    file = fopen("service_records.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open service_records.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s\n",
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
            record.charge,
            record.status);

    fclose(file);

    printf("\nService record created successfully!\n");
}

/* Update Service Record */
void updateServiceRecord(void)
{
    FILE *file;
    FILE *tempFile;
    ServiceRecord record;
    char serviceID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("        UPDATE SERVICE RECORD\n");
    printf("====================================\n");

    printf("Enter Service ID: ");
    scanf("%19s", serviceID);

    file = fopen("service_records.txt", "r");

    if (file == NULL)
    {
        printf("\nNo service records found!\n");
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
        if (strcmp(record.serviceID, serviceID) == 0 && found == 0)
{
    printf("Enter New Diagnostics: ");
    scanf(" %199[^\n]", record.diagnostics);

    printf("Enter New Repairs: ");
    scanf(" %199[^\n]", record.repairs);

    printf("Enter New Parts Used: ");
    scanf(" %199[^\n]", record.parts);

    printf("Enter New Recommendation: ");
    scanf(" %199[^\n]", record.recommendation);

    printf("Enter New Notes: ");
    scanf(" %199[^\n]", record.notes);

    printf("Enter New Service Charge: ");
    scanf("%f", &record.charge);

    found = 1;
}

        fprintf(tempFile,
                "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s\n",
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
                record.charge,
                record.status);
    }

    fclose(file);
    fclose(tempFile);

    if (found == 1)
    {
        remove("service_records.txt");
        rename("temp.txt", "service_records.txt");

        printf("\nService record updated successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("\nService ID not found!\n");
    }
}

/* Complete Service */
void completeService(void)
{
    FILE *file;
    FILE *tempFile;
    ServiceRecord record;
    char serviceID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("          COMPLETE SERVICE\n");
    printf("====================================\n");

    printf("Enter Service ID: ");
    scanf("%19s", serviceID);

    file = fopen("service_records.txt", "r");

    if (file == NULL)
    {
        printf("\nNo service records found!\n");
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
        if (strcmp(record.serviceID, serviceID) == 0)
        {
            strcpy(record.status, "Completed");
            found = 1;
        }

        fprintf(tempFile,
                "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%.2f|%s\n",
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
                record.charge,
                record.status);
    }

    fclose(file);
    fclose(tempFile);

    if (found == 1)
    {
        remove("service_records.txt");
        rename("temp.txt", "service_records.txt");

        printf("\nService completed successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("\nService ID not found!\n");
    }
}


/* Technician Menu */
void technicianMenu(void)
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("          TECHNICIAN MENU\n");
        printf("====================================\n");
        printf("1. View Assigned Appointments\n");
        printf("2. Update Appointment Status\n");
        printf("3. Create Service Record\n");
        printf("4. Update Service Record\n");
        printf("5. Complete Service\n");
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
                viewAssignedAppointments();
                break;

            case 2:
                updateAppointmentStatus();
                break;

            case 3:
                createServiceRecord();
                break;

            case 4:
                updateServiceRecord();
                break;

            case 5:
                completeService();
                break;

            case 0:
                printf("\nTechnician logged out successfully!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);
}

