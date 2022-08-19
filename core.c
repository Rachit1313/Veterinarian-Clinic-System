/*
*****************************************************************************
                        Assignment 1 - Milestone 3
Full Name  :Rachit Chawla
Student ID#:162759211
Email      :rchawla11@myseneca.ca
Section    :ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"
#include <string.h>
//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//

int inputInt()
{

    int result = -1;
    char nextChar = '\0';
    int flag = 1;
    do
    {
        scanf("%d%c", &result, &nextChar);
        if (nextChar != '\n')
        {
            printf("Error! Input a whole number: ");
            clearInputBuffer();
        }
        else
        {
            flag = 0;
        }

    } while (flag);
    return result;
}

int inputIntPositive()
{
    int result = -1;
    do
    {
        result = inputInt();
    } while (result < 0 && printf("ERROR! Value must be > 0: "));
    return result;
}

int inputIntRange(int lowerbound, int upperbound)
{
    int result = lowerbound - 1;
    do
    {
        result = inputInt();

    } while ((result < lowerbound || result > upperbound) && printf("ERROR! Value must be between %d and %d inclusive: ", lowerbound, upperbound));
    return result;
}

char inputCharOption(const char *str)
{
    char result = '\0';
    char nextChar = '\0';
    int i = 0;
    int len =strlen(str);
    int flag = 1;
    do
    {
        scanf("%c%c", &result, &nextChar);

        if (nextChar == '\n')
        {
            for (i = 0; i < len && flag; i++)
                if (str[i] == result)
                    flag = 0;
        }
        else{
            clearInputBuffer();
        }

    } while (flag && printf("ERROR: Character must be one of [%s]: ", str));

    return result;
}

void inputCString(char *str, int min, int max,const char* string2)
{
    char largeInput[100] = {'\0'};
    int done = 0;
    int i = 0;
    //int j = 0;
    do
    {
        scanf("%99[^\n]%*c", largeInput);
        for (i = 1; largeInput[i]; i++)
            ; // this will calculate the length of the string that is required
        if (min == max)
        {
            if (i == min)
            {
               strcpy(str,largeInput);
                done = 1;
            }
        }
        else
        {
            if (i >= min && i <= max)
            {
                strcpy(str,largeInput);
                done = 1;
            }
        }
        if (!done)
        {
            if(!string2){
            if (min == max)
            {
                printf("ERROR: String length must be exactly %d chars: ", min);
            }
            else if (min == 0||i>max)
            {
                printf("ERROR: String length must be no more than %d chars: ", max);
            }
            else
            {
                printf("ERROR: String length must be between %d and %d chars: ", min, max);
            }
            }
            else{
                printf(string2);
                
            }
        }

    } while (!done);
}
void displayFormattedPhone(const char *phone)
{
    int isValid = 1;
    int i = 0;
    if (phone != NULL)
    {
        for (i = 0; phone[i] && isValid; i++)
        {

            if (phone[i] < 48 || phone[i] > 57)
            {
                isValid = 0;
            }
        }
    }
    if (isValid && i == 10)
    {
        printf("(");
        for (i = 0; i < 3; i++)
            printf("%c", phone[i]);
        printf(")");
        for (i = 3; i < 6; i++)
            printf("%c", phone[i]);
        printf("-");
        for (i = 6; i < 10; i++)
            printf("%c", phone[i]);
    }
    else
    {
        printf("(___)___-____");
    }
}



//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

