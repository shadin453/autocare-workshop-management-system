#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"

/* Manager Login */
int managerLogin(void);

/* Manager Menu */
void managerMenu(void);

/* Administrator Management */
void addAdministrator(void);
void searchAdministrator(void);
void viewAdministrators(void);

/* Staff Report */
void staffReport(void);

/* Service Sales Report */
void serviceSalesReport(void);

#endif