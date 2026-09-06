#include "administrator.h"

/* Administrator Login Function */
int administratorLogin(void)
{
    char userID[MAX_ID];
    char password[MAX_PASSWORD];
    FILE *file;
    User user;

    printf("\n====================================\n");
    printf("         ADMINISTRATOR LOGIN\n");
    printf("====================================\n");

    printf("Enter Administrator ID: ");
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
            strcmp(user.role, "Administrator") == 0)
        {
            fclose(file);

            printf("\nLogin successful. Welcome, %s!\n", user.name);
            return 1;
        }
    }

    fclose(file);

    printf("\nInvalid Administrator ID or Password!\n");
    return 0;
}


/* Register New Customer */
void registerCustomer(void)
{
    FILE *file;
    FILE *checkFile;
    User newCustomer;
    User existingUser;
    int duplicate = 0;

    printf("\n====================================\n");
    printf("         REGISTER NEW CUSTOMER\n");
    printf("====================================\n");

    printf("Enter Customer ID: ");
    scanf("%19s", newCustomer.userID);

    /* Check duplicate ID */
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
            if (strcmp(existingUser.userID, newCustomer.userID) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        fclose(checkFile);
    }

    if (duplicate)
    {
        printf("\nError: Customer ID already exists!\n");
        return;
    }

    printf("Enter Customer Name: ");
    scanf(" %49[^\n]", newCustomer.name);

    printf("Enter Password: ");
    scanf("%29s", newCustomer.password);

    strcpy(newCustomer.role, "Customer");

    printf("Enter Contact Number: ");
    scanf("%19s", newCustomer.contact);

    printf("Enter Email: ");
    scanf("%99s", newCustomer.email);

    strcpy(newCustomer.department, "Customer");

    file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%s|%s|%s|%s\n",
            newCustomer.userID,
            newCustomer.name,
            newCustomer.password,
            newCustomer.role,
            newCustomer.contact,
            newCustomer.email,
            newCustomer.department);

    fclose(file);

    printf("\nCustomer registered successfully!\n");
}


/* Register New Technician */
void registerTechnician(void)
{
    FILE *file;
    FILE *checkFile;
    User newTechnician;
    User existingUser;
    int duplicate = 0;

    printf("\n====================================\n");
    printf("        REGISTER NEW TECHNICIAN\n");
    printf("====================================\n");

    printf("Enter Technician ID: ");
    scanf("%19s", newTechnician.userID);

    /* Check duplicate ID */
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
            if (strcmp(existingUser.userID, newTechnician.userID) == 0)
            {
                duplicate = 1;
                break;
            }
        }

        fclose(checkFile);
    }

    if (duplicate)
    {
        printf("\nError: Technician ID already exists!\n");
        return;
    }

    printf("Enter Technician Name: ");
    scanf(" %49[^\n]", newTechnician.name);

    printf("Enter Password: ");
    scanf("%29s", newTechnician.password);

    strcpy(newTechnician.role, "Technician");

    printf("Enter Contact Number: ");
    scanf("%19s", newTechnician.contact);

    printf("Enter Email: ");
    scanf("%99s", newTechnician.email);

    strcpy(newTechnician.department, "Service");

    file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%s|%s|%s|%s\n",
            newTechnician.userID,
            newTechnician.name,
            newTechnician.password,
            newTechnician.role,
            newTechnician.contact,
            newTechnician.email,
            newTechnician.department);

    fclose(file);

    printf("\nTechnician registered successfully!\n");
}

/* Register New Inventory Officer */
void registerInventoryOfficer(void)
{
    FILE *file;
    FILE *checkFile;
    User newInventoryOfficer;
    User existingUser;
    int duplicate = 0;

    printf("\n====================================\n");
    printf("    REGISTER NEW INVENTORY OFFICER\n");
    printf("====================================\n");

    printf("Enter Inventory Officer ID: ");
    scanf("%19s", newInventoryOfficer.userID);

    /* Check duplicate ID */
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
            if (strcmp(existingUser.userID,
                       newInventoryOfficer.userID) == 0)
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
    scanf(" %49[^\n]", newInventoryOfficer.name);

    printf("Enter Password: ");
    scanf("%29s", newInventoryOfficer.password);

    strcpy(newInventoryOfficer.role, "InventoryOfficer");

    printf("Enter Contact Number: ");
    scanf("%19s", newInventoryOfficer.contact);

    printf("Enter Email: ");
    scanf("%99s", newInventoryOfficer.email);

    strcpy(newInventoryOfficer.department, "Inventory");

    file = fopen("users.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open users.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%s|%s|%s|%s\n",
            newInventoryOfficer.userID,
            newInventoryOfficer.name,
            newInventoryOfficer.password,
            newInventoryOfficer.role,
            newInventoryOfficer.contact,
            newInventoryOfficer.email,
            newInventoryOfficer.department);

    fclose(file);

    printf("\nInventory Officer registered successfully!\n");
}

/* Search User */
void searchUser(void)
{
    FILE *file;
    User user;
    char searchID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("             SEARCH USER\n");
    printf("====================================\n");

    printf("Enter User ID: ");
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
        if (strcmp(user.userID, searchID) == 0)
        {
            printf("\nUser Found!\n");
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

    if (found == 0)
    {
        printf("\nUser not found!\n");
    }
}



/* View All Users */
void viewUsers(void)
{
    FILE *file;
    User user;
    int count = 0;

    printf("\n====================================\n");
    printf("            ALL USERS\n");
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
        count++;

        printf("\nUser %d\n", count);
        printf("------------------------------------\n");
        printf("ID         : %s\n", user.userID);
        printf("Name       : %s\n", user.name);
        printf("Role       : %s\n", user.role);
        printf("Contact    : %s\n", user.contact);
        printf("Email      : %s\n", user.email);
        printf("Department : %s\n", user.department);
        printf("------------------------------------\n");
    }

    fclose(file);

    if (count == 0)
    {
        printf("\nNo user records found!\n");
    }
    else
    {
        printf("\nTotal Users: %d\n", count);
    }
}

/* Customer Profile Report */
void customerProfileReport(void)
{
    FILE *file;
    User user;
    char customerID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("       CUSTOMER PROFILE REPORT\n");
    printf("====================================\n");

    printf("Enter Customer ID: ");
    scanf("%19s", customerID);

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
        if (strcmp(user.userID, customerID) == 0 &&
            strcmp(user.role, "Customer") == 0)
        {
            printf("\nCustomer Found!\n");
            printf("------------------------------------\n");
            printf("Customer ID : %s\n", user.userID);
            printf("Name        : %s\n", user.name);
            printf("Contact     : %s\n", user.contact);
            printf("Email       : %s\n", user.email);
            printf("------------------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nCustomer not found!\n");
    }
}

/* Administrator Menu */
void administratorMenu(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("====================================\n");
        printf("        ADMINISTRATOR MENU\n");
        printf("====================================\n");
        printf("1. Register Customer\n");
        printf("2. Register Technician\n");
        printf("3. Register Inventory Officer\n");
        printf("4. Search User\n");
        printf("5. View All Users\n");
        printf("6. Customer Profile Report\n");
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
                registerCustomer();
                break;

            case 2:
                registerTechnician();
                break;

            case 3:
                registerInventoryOfficer();
                break;

            case 4:
                searchUser();
                break;

            case 5:
                viewUsers();
                break;

            case 6:
                customerProfileReport();
                break;

            case 0:
                printf("\nLogging out from Administrator account...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);
}