#include <stdio.h>
#include "common.h"
#include "manager.h"
#include "administrator.h"
#include "customer.h"
#include "technician.h"
#include "inventory.h"

int main(void)
{
    int choice;
    int loginSuccess;

    do
    {
        printf("\n");
        printf("====================================\n");
        printf(" AUTOCARE WORKSHOP MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Manager Login\n");
        printf("2. Administrator Login\n");
        printf("3. Customer Login\n");
        printf("4. Technician Login\n");
        printf("5. Inventory Officer Login\n");
        printf("0. Exit\n");
        printf("====================================\n");

        printf("Select your role: ");

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
                loginSuccess = managerLogin();

                if (loginSuccess == 1)
                {
                    managerMenu();
                }
                break;

            case 2:
                loginSuccess = administratorLogin();

                if (loginSuccess == 1)
                {
                    administratorMenu();
                }
                break;

            case 3:
                loginSuccess = customerLogin();

                if (loginSuccess == 1)
                {
                    customerMenu();
                }
                break;

            case 4:
                loginSuccess = technicianLogin();

                if (loginSuccess == 1)
                {
                    technicianMenu();
                }
                break;

            case 5:
                loginSuccess = inventoryLogin();

                if (loginSuccess == 1)
                {
                    inventoryMenu();
                }
                break;

            case 0:
                printf("\nThank you for using AWMS. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}