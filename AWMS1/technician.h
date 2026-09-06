#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "common.h"

/* Technician Login */
int technicianLogin(void);

/* Technician Menu */
void technicianMenu(void);

/* Appointment Management */
void viewAssignedAppointments(void);
void updateAppointmentStatus(void);

/* Service Record Management */
void createServiceRecord(void);
void updateServiceRecord(void);

/* Service Completion */
void completeService(void);

#endif