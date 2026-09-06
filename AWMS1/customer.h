#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "common.h"

/* Customer Login */
int customerLogin(void);

/* Customer Menu */
void customerMenu(void);

/* Appointment Management */
void bookAppointment(void);
void viewAppointments(void);
void rescheduleAppointment(void);
void cancelAppointment(void);

/* Service History */
void viewServiceHistory(void);

/* Billing */
void viewBilling(void);

#endif