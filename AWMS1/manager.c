#include "manager.h"

/* Clear input buffer */
void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

/* Manager Login Function */
int managerLogin(void)
{
    char userID[MAX_ID];
    char password[MAX_PASSWORD];
    FILE *file;
    User user;

    printf("\n====================================\n");
    printf("            MANAGER LOGIN\n");
    printf("====================================\n");

    printf("Enter Manager ID: ");
    scanf("%19s", userID);

    printf("Enter Password: ");
    scanf("%29s", password);

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return 0;
    }

    while (fscanf(file, "%19[^|]|%49[^|]|%29[^|]|%29[^|]|%19[^|]|%99[^|]|%49[^\n]\n",
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
            strcmp(user.role, "Manager") == 0)
        {
            fclose(file);

            printf("\nLogin successful. Welcome, %s!\n", user.name);
            return 1;
        }
    }

    fclose(file);

    printf("\nInvalid Manager ID or Password!\n");
    return 0;
}

/* Add New Administrator */
void addAdministrator(void)
{
    FILE *file;
    FILE *checkFile;
    User newAdmin;
    User existingUser;
    int duplicate = 0;

    printf("\n====================================\n");
    printf("        ADD NEW ADMINISTRATOR\n");
    printf("====================================\n");

    printf("Enter Administrator ID: ");
    scanf("%19s", newAdmin.userID);

    /* Check for duplicate ID */
    checkFile = fopen("users.txt", "r");

    if (checkFile != NULL)
    {
        while (fscanf(checkFile,
                      "%19[^|]|%49[^|]|%29[^|]|%29[^|]|%19[^|]|%99[^|]|%49[^\n]\n",
                      existingUser.userID,
                      existingUser.name,
                      existingUser.password,
                      existingUser.role,
                      existingUser.contact,
                      existingUser.email,
                      existingUser.department) == 7)
        {
            if (strcmp(existingUser.userID, newAdmin.userID) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        fclose(checkFile);
    }

    if (duplicate)
    {
        printf("\nError: User ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", newAdmin.name);

    printf("Enter Password: ");
    scanf("%29s", newAdmin.password);

    strcpy(newAdmin.role, "Administrator");

    printf("Enter Contact Number: ");
    scanf("%19s", newAdmin.contact);

    printf("Enter Email: ");
    scanf("%99s", newAdmin.email);

    printf("Enter Department: ");
    scanf(" %49[^\n]", newAdmin.department);

    file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%s|%s|%s|%s\n",
            newAdmin.userID,
            newAdmin.name,
            newAdmin.password,
            newAdmin.role,
            newAdmin.contact,
            newAdmin.email,
            newAdmin.department);

    fclose(file);

    printf("\nAdministrator added successfully!\n");
}

/* Search Administrator */
void searchAdministrator(void)
{
    FILE *file;
    User user;
    char searchID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("       SEARCH ADMINISTRATOR\n");
    printf("====================================\n");

    printf("Enter Administrator ID: ");
    scanf("%19s", searchID);

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
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
        if (strcmp(user.userID, searchID) == 0 &&
            strcmp(user.role, "Administrator") == 0)
        {
            printf("\nAdministrator Found!\n");
            printf("------------------------------------\n");
            printf("ID         : %s\n", user.userID);
            printf("Name       : %s\n", user.name);
            printf("Role       : %s\n", user.role);
            printf("Contact    : %s\n", user.contact);
            printf("Email      : %s\n", user.email);
            printf("Department : %s\n", user.department);
            printf("------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
    {
        printf("\nAdministrator not found!\n");
    }
}

/* View All Administrators */
void viewAdministrators(void)
{
    FILE *file;
    User user;
    int count = 0;

    printf("\n====================================\n");
    printf("        ALL ADMINISTRATORS\n");
    printf("====================================\n");

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
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
        if (strcmp(user.role, "Administrator") == 0)
        {
            count++;

            printf("\nAdministrator %d\n", count);
            printf("------------------------------------\n");
            printf("ID         : %s\n", user.userID);
            printf("Name       : %s\n", user.name);
            printf("Contact    : %s\n", user.contact);
            printf("Email      : %s\n", user.email);
            printf("Department : %s\n", user.department);
            printf("------------------------------------\n");
        }
    }

    fclose(file);

    if (count == 0)
    {
        printf("\nNo administrator records found!\n");
    }
    else
    {
        printf("\nTotal Administrators: %d\n", count);
    }
}


/* Staff Report */
void staffReport(void)
{
    FILE *file;
    User user;

    int adminCount = 0;
    int technicianCount = 0;
    int inventoryCount = 0;
    int totalStaff = 0;

    printf("\n====================================\n");
    printf("            STAFF REPORT\n");
    printf("====================================\n");

    file = fopen("users.txt", "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
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
        if (strcmp(user.role, "Administrator") == 0)
        {
            printf("\nID: %s\n", user.userID);
            printf("Name: %s\n", user.name);
            printf("Role: %s\n", user.role);
            printf("Department: %s\n", user.department);

            adminCount++;
            totalStaff++;
        }

        else if (strcmp(user.role, "Technician") == 0)
        {
            printf("\nID: %s\n", user.userID);
            printf("Name: %s\n", user.name);
            printf("Role: %s\n", user.role);
            printf("Department: %s\n", user.department);

            technicianCount++;
            totalStaff++;
        }

        else if (strcmp(user.role, "InventoryOfficer") == 0)
        {
            printf("\nID: %s\n", user.userID);
            printf("Name: %s\n", user.name);
            printf("Role: %s\n", user.role);
            printf("Department: %s\n", user.department);

            inventoryCount++;
            totalStaff++;
        }
    }

    fclose(file);

    printf("\n====================================\n");
    printf("           STAFF SUMMARY\n");
    printf("====================================\n");

    printf("Total Administrators    : %d\n", adminCount);
    printf("Total Technicians       : %d\n", technicianCount);
    printf("Total Inventory Officers: %d\n", inventoryCount);
    printf("------------------------------------\n");
    printf("Total Staff             : %d\n", totalStaff);
}

/* Service Sales Report */
void serviceSalesReport(void)
{
    FILE *file;
    Bill bill;
    int totalSales = 0;
    float totalRevenue = 0;

    printf("\n====================================\n");
    printf("        SERVICE SALES REPORT\n");
    printf("====================================\n");

    file = fopen("billing.txt", "r");

    if (file == NULL)
    {
        printf("\nError: Unable to open billing.txt file.\n");
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%19[^|]|%f|%f|%f|%19[^|]|%14[^\n]\n",
                  bill.billID,
                  bill.appointmentID,
                  &bill.serviceCharge,
                  &bill.partsCost,
                  &bill.total,
                  bill.paymentStatus,
                  bill.date) == 7)
    {
        printf("\nBill ID          : %s\n", bill.billID);
        printf("Appointment ID   : %s\n", bill.appointmentID);
        printf("Service Charge   : RM %.2f\n", bill.serviceCharge);
        printf("Parts Cost       : RM %.2f\n", bill.partsCost);
        printf("Total           : RM %.2f\n", bill.total);
        printf("Payment Status  : %s\n", bill.paymentStatus);
        printf("Date            : %s\n", bill.date);

        totalSales++;
        totalRevenue += bill.total;
    }

    fclose(file);

    printf("\n====================================\n");
    printf("           SALES SUMMARY\n");
    printf("====================================\n");

    if (totalSales == 0)
    {
        printf("No sales records found!\n");
    }
    else
    {
        printf("Total Number of Sales : %d\n", totalSales);
        printf("Total Revenue         : RM %.2f\n", totalRevenue);
    }
}

/* Manager Menu */
void managerMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("====================================\n");
        printf("             MANAGER MENU\n");
        printf("====================================\n");
        printf("1. Add Administrator\n");
        printf("2. Search Administrator\n");
        printf("3. View All Administrators\n");
        printf("4. Staff Report\n");
        printf("5. Service Sales Report\n");
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
                addAdministrator();
                break;

            case 2:
                searchAdministrator();
                break;

            case 3:
                viewAdministrators();
                break;

            case 4:
                staffReport();
                break;

            case 5:
                serviceSalesReport();
                break;

            case 0:
                printf("\nLogging out from Manager account...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);
}