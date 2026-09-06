#include "inventory.h"

/* Inventory Officer Login */
int inventoryLogin(void)
{
    char userID[MAX_ID];
    char password[MAX_PASSWORD];
    FILE *file;
    User user;

    printf("\n====================================\n");
    printf("       INVENTORY OFFICER LOGIN\n");
    printf("====================================\n");

    printf("Enter Inventory Officer ID: ");
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
            strcmp(user.role, "InventoryOfficer") == 0)
        {
            fclose(file);

            printf("\nLogin successful. Welcome, %s!\n", user.name);
            return 1;
        }
    }

    fclose(file);

    printf("\nInvalid Inventory Officer ID or Password!\n");
    return 0;
}

/* Add Inventory Item */
void addInventoryItem(void)
{
    FILE *file;
    Part part;

    printf("\n====================================\n");
    printf("         ADD INVENTORY ITEM\n");
    printf("====================================\n");

    printf("Enter Part ID: ");
    scanf("%19s", part.partID);

    printf("Enter Part Name: ");
    scanf(" %49[^\n]", part.name);

    printf("Enter Category: ");
    scanf(" %49[^\n]", part.category);

    printf("Enter Quantity: ");
    scanf("%d", &part.quantity);

    printf("Enter Unit Price: ");
    scanf("%f", &part.unitPrice);

    printf("Enter Supplier: ");
    scanf(" %99[^\n]", part.supplier);

    printf("Enter Warranty Start Date: ");
    scanf("%14s", part.warrantyStart);

    printf("Enter Warranty Expiry Date: ");
    scanf("%14s", part.warrantyExpiry);

    file = fopen("inventory.txt", "a");

    if (file == NULL)
    {
        printf("\nError: Unable to open inventory.txt file.\n");
        return;
    }

    fprintf(file,
            "%s|%s|%s|%d|%.2f|%s|%s|%s\n",
            part.partID,
            part.name,
            part.category,
            part.quantity,
            part.unitPrice,
            part.supplier,
            part.warrantyStart,
            part.warrantyExpiry);

    fclose(file);

    printf("\nInventory item added successfully!\n");
}

/* View Inventory */
void viewInventory(void)
{
    FILE *file;
    Part part;
    int found = 0;

    printf("\n====================================\n");
    printf("          INVENTORY LIST\n");
    printf("====================================\n");

    file = fopen("inventory.txt", "r");

    if (file == NULL)
    {
        printf("\nNo inventory records found!\n");
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%49[^|]|%49[^|]|%d|%f|%99[^|]|%14[^|]|%14[^\n]\n",
                  part.partID,
                  part.name,
                  part.category,
                  &part.quantity,
                  &part.unitPrice,
                  part.supplier,
                  part.warrantyStart,
                  part.warrantyExpiry) == 8)
    {
        printf("\nPart ID          : %s\n", part.partID);
        printf("Part Name        : %s\n", part.name);
        printf("Category         : %s\n", part.category);
        printf("Quantity         : %d\n", part.quantity);
        printf("Unit Price       : %.2f\n", part.unitPrice);
        printf("Supplier         : %s\n", part.supplier);
        printf("Warranty Start   : %s\n", part.warrantyStart);
        printf("Warranty Expiry  : %s\n", part.warrantyExpiry);
        printf("------------------------------------\n");

        found = 1;
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nNo inventory items found!\n");
    }
}

/* Search Inventory Item */
void searchInventoryItem(void)
{
    FILE *file;
    Part part;
    char partID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("       SEARCH INVENTORY ITEM\n");
    printf("====================================\n");

    printf("Enter Part ID: ");
    scanf("%19s", partID);

    file = fopen("inventory.txt", "r");

    if (file == NULL)
    {
        printf("\nNo inventory records found!\n");
        return;
    }

    while (fscanf(file,
                  "%19[^|]|%49[^|]|%49[^|]|%d|%f|%99[^|]|%14[^|]|%14[^\n]\n",
                  part.partID,
                  part.name,
                  part.category,
                  &part.quantity,
                  &part.unitPrice,
                  part.supplier,
                  part.warrantyStart,
                  part.warrantyExpiry) == 8)
    {
        if (strcmp(part.partID, partID) == 0)
        {
            printf("\nPart ID          : %s\n", part.partID);
            printf("Part Name        : %s\n", part.name);
            printf("Category         : %s\n", part.category);
            printf("Quantity         : %d\n", part.quantity);
            printf("Unit Price       : %.2f\n", part.unitPrice);
            printf("Supplier         : %s\n", part.supplier);
            printf("Warranty Start   : %s\n", part.warrantyStart);
            printf("Warranty Expiry  : %s\n", part.warrantyExpiry);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (found == 0)
    {
        printf("\nPart ID not found!\n");
    }
}

/* Update Inventory Item */
void updateInventoryItem(void)
{
    FILE *file;
    FILE *tempFile;
    Part part;
    char partID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("       UPDATE INVENTORY ITEM\n");
    printf("====================================\n");

    printf("Enter Part ID: ");
    scanf("%19s", partID);

    file = fopen("inventory.txt", "r");

    if (file == NULL)
    {
        printf("\nNo inventory records found!\n");
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
                  "%19[^|]|%49[^|]|%49[^|]|%d|%f|%99[^|]|%14[^|]|%14[^\n]\n",
                  part.partID,
                  part.name,
                  part.category,
                  &part.quantity,
                  &part.unitPrice,
                  part.supplier,
                  part.warrantyStart,
                  part.warrantyExpiry) == 8)
    {
        if (strcmp(part.partID, partID) == 0)
        {
            printf("Enter New Part Name: ");
            scanf(" %49[^\n]", part.name);

            printf("Enter New Category: ");
            scanf(" %49[^\n]", part.category);

            printf("Enter New Quantity: ");
            scanf("%d", &part.quantity);

            printf("Enter New Unit Price: ");
            scanf("%f", &part.unitPrice);

            printf("Enter New Supplier: ");
            scanf(" %99[^\n]", part.supplier);

            printf("Enter New Warranty Start Date: ");
            scanf("%14s", part.warrantyStart);

            printf("Enter New Warranty Expiry Date: ");
            scanf("%14s", part.warrantyExpiry);

            found = 1;
        }

        fprintf(tempFile,
                "%s|%s|%s|%d|%.2f|%s|%s|%s\n",
                part.partID,
                part.name,
                part.category,
                part.quantity,
                part.unitPrice,
                part.supplier,
                part.warrantyStart,
                part.warrantyExpiry);
    }

    fclose(file);
    fclose(tempFile);

    if (found == 1)
    {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");

        printf("\nInventory item updated successfully!\n");
    }
    else
    {
        remove("temp.txt");
        printf("\nPart ID not found!\n");
    }
}

/* Delete Inventory Item */
void deleteInventoryItem(void)
{
    FILE *file;
    FILE *tempFile;
    Part part;
    char partID[MAX_ID];
    int found = 0;

    printf("\n====================================\n");
    printf("       DELETE INVENTORY ITEM\n");
    printf("====================================\n");

    printf("Enter Part ID to delete: ");
    scanf("%19s", partID);

    file = fopen("inventory.txt", "r");

    if (file == NULL)
    {
        printf("\nNo inventory records found!\n");
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
                  "%19[^|]|%49[^|]|%49[^|]|%d|%f|%99[^|]|%14[^|]|%14[^\n]\n",
                  part.partID,
                  part.name,
                  part.category,
                  &part.quantity,
                  &part.unitPrice,
                  part.supplier,
                  part.warrantyStart,
                  part.warrantyExpiry) == 8)
    {
        if (strcmp(part.partID, partID) == 0)
        {
            found = 1;
            continue;
        }

        fprintf(tempFile,
                "%s|%s|%s|%d|%.2f|%s|%s|%s\n",
                part.partID,
                part.name,
                part.category,
                part.quantity,
                part.unitPrice,
                part.supplier,
                part.warrantyStart,
                part.warrantyExpiry);
    }

    fclose(file);
    fclose(tempFile);

    if (found == 1)
    {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");

        printf("\nInventory item deleted successfully!\n");
    }
    else
    {
        remove("temp.txt");

        printf("\nPart ID not found!\n");
    }
}

/* Inventory Menu */
void inventoryMenu(void)
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf("        INVENTORY OFFICER MENU\n");
        printf("====================================\n");
        printf("1. Add Inventory Item\n");
        printf("2. View Inventory\n");
        printf("3. Search Inventory Item\n");
        printf("4. Update Inventory Item\n");
        printf("5. Delete Inventory Item\n");
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
                addInventoryItem();
                break;

            case 2:
                viewInventory();
                break;

            case 3:
                searchInventoryItem();
                break;

            case 4:
                updateInventoryItem();
                break;

            case 5:
                deleteInventoryItem();
                break;

            case 0:
                printf("\nInventory Officer logged out successfully!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);
}

