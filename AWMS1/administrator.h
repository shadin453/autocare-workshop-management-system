#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "common.h"

/* Administrator Login */
int administratorLogin(void);

/* Administrator Menu */
void administratorMenu(void);

/* User Registration */
void registerCustomer(void);
void registerTechnician(void);
void registerInventoryOfficer(void);

/* User Search and View */
void searchUser(void);
void viewUsers(void);

/* Customer Profile Report */
void customerProfileReport(void);

#endif