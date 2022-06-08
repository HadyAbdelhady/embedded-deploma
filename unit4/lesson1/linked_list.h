#ifndef _LIST_H
#define _LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Hprint(...)          \
    {                        \
        fflush(stdin);       \
        fflush(stdout);      \
        printf(__VA_ARGS__); \
        fflush(stdin);       \
        fflush(stdout);      \
        printf("\n");        \
        \ 
        fflush(stdin);       \
        fflush(stdout);      \
    }

typedef struct Sdata
{
    char name[40];
    float degree;
    short level;
} data;
struct Sstudent
{
    data studentData;
    struct Sstudent *Pnextstudent;
} Sstudent;
struct Sstudent *Pfirst_S = NULL;
void options()
{
    printf("\n\t choose the following options \n");
    printf("\n\t 1:AddStudent ");
    printf("\n\t 2:DeleteStudent ");
    printf("\n\t 3:ViewStudent ");
    printf("\n\t 4:Get the length of the list ");
    printf("\n\t 5:Get the middle of the list ");
    printf("\n\t 6:View from end of the list ");
    printf("\n\t 7:Reverse list ");

    printf("\n\t 10:EXIT\n");
    printf("\t=====================\n");
}
void NEW_STUDENT()
{
    struct Sstudent *Pnew_S = (struct Sstudent *)malloc(sizeof(struct Sstudent));
    char temp[40];
    if (Pfirst_S == NULL)
    {
        Pfirst_S = Pnew_S;
    }
    else
    {
        // create temp student to make him the last one then add the new one
        struct Sstudent *Plast_S = Pfirst_S;
        while (Plast_S->Pnextstudent)
            Plast_S = Plast_S->Pnextstudent;
        Plast_S->Pnextstudent = Pnew_S;
    }
    // add data
    Hprint("Enter Student Name");
    gets(Pnew_S->studentData.name);
    Hprint("Enter Student LEVEL");
    scanf("%d", &Pnew_S->studentData.level);
    Hprint("Enter Student DEGREE");
    scanf("%f", &Pnew_S->studentData.degree);
    Pnew_S->Pnextstudent = NULL;
}
void DeleteByName()
{
    short found = 0;
    char wantedName[40];
    Hprint("\n enter the student name to be deleted: ");
    scanf("%s", wantedName);
    // check if there is a list or not
    if (Pfirst_S)
    {
        struct Sstudent *PCurrent_S = Pfirst_S;
        struct Sstudent *Prev_S = NULL;
        // if it's the first student
        if (strcmp(Pfirst_S->studentData.name, wantedName) == 0)
        {
            Pfirst_S = PCurrent_S->Pnextstudent;
            Hprint("student %s deleted", wantedName);
            found = 1;
            // Pfirst_S = Current_S->Pnextstudent;
        }
        else
        {
            while (PCurrent_S)
            {
                if (strcmp(PCurrent_S->studentData.name, wantedName) == 0)
                {
                    Prev_S->Pnextstudent = PCurrent_S->Pnextstudent;
                    Hprint("student %s deleted", wantedName);
                    found = 1;
                    break;
                }
                else
                {
                    Prev_S = PCurrent_S;
                    PCurrent_S = PCurrent_S->Pnextstudent;
                }
            }
            if (found == 0)
                printf("name not found\n");
        }
    }
    else
    {
        Hprint("No list");
    }
}
void DeleteByNumber()
{

    Hprint("\n enter the student number to be deleted (starting from 1) ");
    int wanted_number;
    scanf("%d", &wanted_number);
    int counter = 1;
    struct Sstudent *Current_S = Pfirst_S;
    struct Sstudent *prev_S = NULL;

    if (Pfirst_S)
    {
        short found = 0;
        if (wanted_number == 1)
        {
            Pfirst_S = Current_S->Pnextstudent;
            Hprint("student number %d deleted", wanted_number);
            free(Current_S);
        }
        else
        {
            while (Current_S)
            {
                if (counter == wanted_number)
                {
                    prev_S->Pnextstudent = Current_S->Pnextstudent;
                    free(Current_S);
                    Hprint("student number %d deleted", wanted_number);
                    found = 1;
                    break;
                }
                else
                {
                    Current_S = Current_S->Pnextstudent;
                    counter++;
                }
            }
            if (found == 0)
                printf("number not found\n");
        }
    }
    else
        Hprint("No list or student not found");
}
void DeleteAll()
{
    Hprint("you chose to delete all");
    if (Pfirst_S)
    {
        while (Pfirst_S)
        {
            struct Sstudent *Current_S = Pfirst_S;
            Pfirst_S = Current_S->Pnextstudent;
            free(Current_S);
        }
        Hprint("all deleted");
    }
    else
        Hprint("No list or student not found");
}
void DELETE_STUDENT()
{
    if (Pfirst_S)
    {
        Hprint("delete by name (press 1) \t by number (press 2) \t delete all (press 3)");
        short option;
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            DeleteByName();
            break;
        case 2:
            DeleteByNumber();
            break;
        case 3:
            DeleteAll();
            break;
        default:
            Hprint("error");
            break;
        }
    }
    else
        Hprint("No List to delete from");
}
void ViewALL()
{
    if (Pfirst_S)
    {
        struct Sstudent *Current_S = Pfirst_S;
        int count = 0;
        while (Current_S)
        {
            printf("\n  name: %s ", Current_S->studentData.name);
            printf("\n record number %d ", count + 1);
            printf("\n  level: %d ", Current_S->studentData.level);
            printf("\n  degree: %f \n", Current_S->studentData.degree);
            Current_S = Current_S->Pnextstudent;
            count++;
        }
    }
    else
        Hprint("NO LIST TO SHOW");
}
void ViewByName()
{
    short found = 0;
    char wantedName[40];
    Hprint("\n enter the student name to be Viewed: ");
    scanf("%s", wantedName);
    // check if there is a list or not
    if (Pfirst_S)
    {
        struct Sstudent *PCurrent_S = Pfirst_S;
        int count = 1;
        // if it's the first student
        while (PCurrent_S)
        {
            if (strcmp(PCurrent_S->studentData.name, wantedName) == 0)
            {
                printf("\n  name: %s ", PCurrent_S->studentData.name);
                printf("\n record number %d ", count);
                printf("\n  level: %d ", PCurrent_S->studentData.level);
                printf("\n  degree: %f \n", PCurrent_S->studentData.degree);
                found = 1;
                break;
            }
            else
            {
                PCurrent_S = PCurrent_S->Pnextstudent;
                count++;
            }
        }
        if (found == 0)
            printf("name not found\n");
    }
    else
    {
        Hprint("No list");
    }
}
void ViewByNumber()
{

    Hprint("\n enter the student number to be Viewed (starting from 1) ");
    int wanted_number;
    scanf("%d", &wanted_number);
    int counter = 1;
    struct Sstudent *Current_S = Pfirst_S;
    if (Pfirst_S)
    {
        short found = 0;
        while (Current_S)
        {
            if (counter == wanted_number)
            {
                printf("\n  name: %s ", Current_S->studentData.name);
                printf("\n record number %d ", counter);
                printf("\n  level: %d ", Current_S->studentData.level);
                printf("\n  degree: %f \n", Current_S->studentData.degree);
                Current_S = Current_S->Pnextstudent;
                found = 1;
                break;
            }
            else
            {
                Current_S = Current_S->Pnextstudent;
                counter++;
            }
        }
        if (found == 0)
            printf("number not found\n");
    }
    else
        Hprint("No list or student not found");
}
void ViewStudent()
{
    if (Pfirst_S)
    {
        Hprint("show by name (press 1) \t by number (press 2) \t show all (press 3)");
        short option;
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            ViewByName();
            break;
        case 2:
            ViewByNumber();
            break;
        case 3:
            ViewALL();
            break;
        default:
            Hprint("error");
            break;
        }
    }
    else
        Hprint("No list to show from");
}
int ListLength()
{
    if (Pfirst_S)
    {
        struct Sstudent *Current_S = Pfirst_S;
        int count = 0;
        while (Current_S)
        {
            Current_S = Current_S->Pnextstudent;
            count++;
        }
        return count;
    }
    return 0;
}
void GetMiddle()
{
    if (Pfirst_S)
    {
        int num = ListLength();
        int counter = 1;
        struct Sstudent *Current_S = Pfirst_S;
        if (num % 2 == 0)
        {
            while (Current_S)
            {
                if (counter > (num / 2) + 1)
                    break;
                else if (counter == (num / 2) || counter == (num / 2) + 1)
                {
                    printf("\n  name: %s ", Current_S->studentData.name);
                    printf("\n record number %d ", counter);
                    printf("\n  level: %d ", Current_S->studentData.level);
                    printf("\n  degree: %f \n", Current_S->studentData.degree);
                    Current_S = Current_S->Pnextstudent;
                    counter++;
                }
                else
                {
                    Current_S = Current_S->Pnextstudent;
                    counter++;
                }
            }
        }
        else
        {
            while (Current_S)
            {
                if (counter > (num / 2) + 1)
                    break;
                else if (counter == (num / 2) + 1)
                {
                    printf("\n  name: %s ", Current_S->studentData.name);
                    printf("\n record number %d ", counter);
                    printf("\n  level: %d ", Current_S->studentData.level);
                    printf("\n  degree: %f \n", Current_S->studentData.degree);
                    Current_S = Current_S->Pnextstudent;
                    counter++;
                }
                else
                {
                    Current_S = Current_S->Pnextstudent;
                    counter++;
                }
            }
        }
    }
    else
        Hprint("NOLIST");
}
void ViewfromEnd()
{
    if (Pfirst_S)
    {
        int num = ListLength();
        Hprint("\n enter the student number to be Viewed from the end (starting from 1) ");
        int wanted_number, counter = 1;
        scanf("%d", &wanted_number);
        struct Sstudent *Current_S = Pfirst_S;

        short found = 0;
        while (Current_S)
        {
            if (counter == num - wanted_number + 1)
            {
                printf("\n  name: %s ", Current_S->studentData.name);
                printf("\n record number %d ", counter);
                printf("\n  level: %d ", Current_S->studentData.level);
                printf("\n  degree: %f \n", Current_S->studentData.degree);
                Current_S = Current_S->Pnextstudent;
                found = 1;
                break;
            }
            else
            {
                Current_S = Current_S->Pnextstudent;
                counter++;
            }
        }
        if (found == 0)
            printf("number not found\n");
    }
    else
        Hprint("No list ");
}
void reverse()
{

    if (Pfirst_S)
    {
        struct Sstudent *Current_S = Pfirst_S;
        struct Sstudent *Prev_S = NULL;
        struct Sstudent *next = NULL;
        while (Current_S)
        {
            next = Current_S->Pnextstudent;
            Current_S->Pnextstudent = Prev_S;
            Prev_S = Current_S;
            Current_S = next;
        }
        struct Sstudent *reversed = Prev_S;
        int count = 0;
        while (reversed)
        {
            printf("\n  name: %s ", reversed->studentData.name);
            printf("\n record number %d ", count + 1);
            printf("\n  level: %d ", reversed->studentData.level);
            printf("\n  degree: %f \n", reversed->studentData.degree);
            reversed = reversed->Pnextstudent;
            count++;
        }
    }
    else
        printf("NO LIST");
}
#endif