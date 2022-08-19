#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.num);
        printf(" (%s)\n", patient->phone.desc);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.num);
        printf(" (%s)\n", patient->phone.desc);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.num);

    printf(" (%s)\n", patient->phone.desc);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.num);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN,NULL);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int index = 0;
    int found = 1;
    int printed = 0;
    while (index < max) {
        if (patient[index].patientNumber != 0) {
            if (!printed)
                displayPatientTableHeader();
            displayPatientData(&patient[index], fmt);
            found = 0;
            printed = 1;
        }
        index++;
    }
    if (found) {
        printf("*** No records found ***\n\n");
    }
    putchar('\n');
}


// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        selection = inputIntRange(0, 2);
        putchar('\n');
        
        if (selection == 1) {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2) {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (selection);
    
}

// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max)
{
    int found = 0;
    int index = -1;
    while (!found && ++index < max) {
        if (patient[index].patientNumber == 0) {
            found = 1;
        }
    }

    if (found) {
        int nextP_Number = nextPatientNumber(patient, max);
        patient[index].patientNumber = nextP_Number;
        inputPatient(&patient[index]);
        printf("*** New patient record added ***\n\n");
    }
    else {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patientNum = inputIntPositive();
    putchar('\n');
    int index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        menuPatientEdit(&patient[index]);
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patientNum = inputIntPositive();
    putchar('\n');
    int index = findPatientIndexByPatientNum(patientNum, patient, max);
    if (index == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        displayPatientData(&patient[index], 1);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        int selection = (inputCharOption("yn") == 'y');


        if (selection) {
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }
    }
}
/* !!!!!!!EXTRA FUNCTIONS!!!!!!! */
//Function to change date time to integer format for calculations and sorting
int datetoint(const struct Date *d, const struct Time *t)
{
    return d->year * 100000 + d->month * 10000 + d->day * 1000 + t->hour * 100 + t->min;
}

//Function to sort appointments by date after using datetoint function to convert it
void sortAppointments(struct ClinicData *data)
{
    int i, j;
    struct Appointment temp;

    for (i = data->maxAppointments - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (datetoint(&data->appointments[j].date, &data->appointments[j].time) > datetoint(&data->appointments[j + 1].date, &data->appointments[j + 1].time) && data->appointments[j].patientNumber > 0 && data->appointments[j + 1].patientNumber > 0)
            {
                temp = data->appointments[j];
                data->appointments[j] = data->appointments[j + 1];
                data->appointments[j + 1] = temp;
            }
        }
    }
}
//Function which can be used an equal to for dates or can copy date from 1 struct to another
int equalto(const struct Date *d1, const struct Date *d2)
{
    return d1->year == d2->year && d1->month == d2->month && d1->day == d2->day;
}

//
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData *data)
{

    struct Date a;
    displayScheduleTableHeader(&a, 1);
    sortAppointments(data);
    int i = 0;
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber > 0)
        {
            displayScheduleData(&data->patients[findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient)], &data->appointments[i], 1);
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData *data)
{
    struct Date a;
    int i = 0;
    sortAppointments(data);
    printf("Year        : ");
    a.year = inputIntPositive();
    int febdays = a.year % 4 == 0 ? 29 : 28;
    int months[12] = {31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    printf("Month (1-12): ");
    a.month = inputIntRange(1, 12);
    printf("Day (1-%d)  : ", months[a.month - 1]);
    a.day = inputIntRange(1, months[a.month - 1]);
    putchar('\n');
    displayScheduleTableHeader(&a, 0);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].patientNumber > 0)
        {
            if (equalto(&a, &data->appointments[i].date))
            {

                displayScheduleData(&data->patients[findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient)], &data->appointments[i], 0);
            }
        }
    }
    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment *appointments, int maximumAppointments, struct Patient *patients, int maximumpatient)
{
    int isavailable = 0,flag = 0,patientDone = 0,dateDone = 0,timeDone = 0,number = 0,same = 0,i = 0,final=0;
    struct Date a;
    struct Time t;
    for (i = 0; i < maximumAppointments && !isavailable; i++)
    {
        if (appointments[i].patientNumber < 1)
        {
            isavailable = i;
        }
    }
    while (!flag && isavailable)
    {
        while (patientDone < 1)
        {
            printf("Patient Number: ");
            number = inputIntPositive();
            int result = findPatientIndexByPatientNum(number, patients, maximumpatient);
            if (result > -1)
            {
                patientDone = 1;
            }
            else
            {
                printf("Invalid Entry, try again: \n");
            }
        }
        while (dateDone < 1)
        {
            printf("Year        : ");
            a.year = inputIntPositive();
            int febdays = a.year % 4 == 0 ? 29 : 28;
            int months[12] = {31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            printf("Month (1-12): ");
            a.month = inputIntRange(1, 12);
            printf("Day (1-%d)  : ", months[a.month - 1]);
            a.day = inputIntRange(1, months[a.month - 1]);
            dateDone = 1;
        }
        while (timeDone < 1)
        {
            final=0;
            printf("Hour (0-23)  : ");
            t.hour = inputIntRange(0, 23);
            printf("Minute (0-59): ");
            t.min = inputIntRange(0, 59);
            if(t.hour==TIME_END){
                if(t.min!=0){
                    final=1;
                }
            }
            
            if (t.hour >= TIME_START && t.hour <= TIME_END && (t.min % TIME_INTERVAL == 0)&&!final)
            {
                timeDone=1;
               
            }
            else
            {
                 printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", TIME_START, TIME_END, TIME_INTERVAL);
            }
        }
        same=0;
        for (i = 0; i < maximumAppointments && !same; i++)
        {
            if (equalto(&a, &appointments[i].date) && appointments[i].time.hour == t.hour && appointments[i].time.min == t.min)
            {

                same = 1;
            }
        }
            if (same > 0)
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
                dateDone = 0;
                timeDone = 0;
            }
            else
            {
                flag = 1;
                appointments[isavailable].date = a;
                appointments[isavailable].time = t;
                appointments[isavailable].patientNumber = number;
                printf("\n*** Appointment scheduled! ***\n\n");
            }
        }
    }

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment * appointments, int maximumAppointments, struct Patient *patients, int maximumpatient)
    {
        int i = 0;
        printf("Patient Number: ");
        int number = inputIntPositive();
        int result = findPatientIndexByPatientNum(number, patients, maximumpatient);
        if (result == -1)
        {
            printf("ERROR: Patient record not found!\n\n");
        }
        else
        {
            struct Date d;
            int found = 0;
            int index = 0;
            printf("Year        : ");
            d.year = inputIntPositive();
            int febdays = d.year % 4 == 0 ? 29 : 28;
            int months[12] = {31, febdays, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            printf("Month (1-12): ");
            d.month = inputIntRange(1, 12);
            printf("Day (1-%d)  : ", months[d.month - 1]);
            d.day = inputIntRange(1, months[d.month - 1]);
            for (i = 0; i < maximumAppointments && !found; i++)
            {
                if ((appointments[i].patientNumber == number) && equalto(&d, &appointments[i].date))
                {
                    found = 1;
                    index = i;
                
                }
    
            }
            printf("\n");
            displayPatientData(&patients[result], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");
            char option = inputCharOption("yn");
            if (option != 'y')
            {
                printf("\n Operation Aborted!\n");
            }
            else
            {
                appointments[index].patientNumber = 0;
                appointments[index].date.year = 0;
                appointments[index].date.month = 0;
                appointments[index].date.day = 0;
                printf("\nAppointment record has been removed!\n");
            }

            printf("\n");
        }
    }

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    printf("Search by patient number: ");
    int num = inputIntPositive();
    putchar('\n');
    int index = findPatientIndexByPatientNum(num, patient, max);
    
    if (index == -1) {
        printf("*** No records found ***\n\n");
    }
    else {
        displayPatientData(&patient[index], 1);
        putchar('\n');
    }
}


// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    printf("Search by phone number: ");
    char phone[PHONE_LEN+1];
    inputCString(phone, PHONE_LEN, PHONE_LEN,NULL);
    putchar('\n');
    int found = 0;
    displayPatientTableHeader();
    int index = -1;
    while(++index < max) {

        if ((strcmp(patient[index].phone.num,phone) == 0)) {
            displayPatientData(&patient[index], 2);
            found = 1;
        }
    }
    if (!found) {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max)
{
    int latest = 0;
    int index = -1;
    while(++index < max) {
        if (latest < patient[index].patientNumber) {
            latest = patient[index].patientNumber;
        }
    }
    return latest + 1;
    
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int index = -1;
    int i = 0;
    while(i < max) {
        if (patient[i].patientNumber == patientNumber) {
            index = i;
        }
        i++;
    }
    return index;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN,NULL);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone * phone)
    {

        printf("Phone Information\n-----------------\nHow will the patient like to be contacted?\n1. Cell\n2. Home\n3. Work\n4. TBD\nSelection: ");
        int selection = inputIntRange(1, 4);
        putchar('\n');
        if (selection == 4){
            strcpy(phone->desc, "TBD");
            phone->num[0] = 0;
        }
        else{
            if (selection == 1)
                strcpy(phone->desc, "CELL");
            if (selection == 2)
                strcpy(phone->desc, "HOME");
            if (selection == 3)
                strcpy(phone->desc, "WORK");
            printf("Contact: %s\n", phone->desc);
            printf("Number : ");
            inputCString(phone->num, 10, 10,"Invalid 10-digit number! Number: ");
            putchar('\n');
        }
    }

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char *datafile, struct Patient patients[], int maximum)
    {

        FILE *fp = NULL;
        fp = fopen(datafile, "r");
        int read = 0;
        if (fp != NULL){
            while (!feof(fp) && read < maximum)
            {
                fscanf(fp, "%d|%29[^|]|%4[^|]|", &patients[read].patientNumber, patients[read].name, patients[read].phone.desc);

                if (!(strcmp(patients[read].phone.desc, "TBD") == 0)){
                    fscanf(fp, "%[^\n]%*c", patients[read].phone.num);
                }
                read++;
            }
            fclose(fp);
        }
        return read;
    }

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char *datafile, struct Appointment appoints[], int maximum){

        FILE *fp = NULL;
        fp = fopen(datafile, "r");
        int read = 0;
        if (fp != NULL){
            while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[read].patientNumber, &appoints[read].date.year, &appoints[read].date.month, &appoints[read].date.day, &appoints[read].time.hour, &appoints[read].time.min) == 6 && read < maximum)
            {
                read++;}
            fclose(fp);}

        return read;
        }
