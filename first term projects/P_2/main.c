#include <stdio.h>
#include "student.h"
#include "AddFromFile.h"
#include "AddManually.h"
#include "delete.h"
#include "findByCourse.h"
#include "findByName.h"
#include "findByID.h"
#include "init.h"
#include "Platform_Types.h"
#include "status.h"
#include "update.h"
#include "viewALL.h"

int main()
{
    S_FIFO StudentData;
    int choice;
    FIFO_Init(&StudentData, Students, TotalNumber);
    H_printf("Student management System \n");
    while (1)
    {
        H_printf("\n*************************************\n");

        H_printf("Choose the you option \n");
        H_printf("\t1. Add the Student Details From Text File \n");
        H_printf("\t2. Add the Student Details Manually \n");
        H_printf("\t3. Find  by ID Number \n");
        H_printf("\t4. Find  by First Name \n");
        H_printf("\t5. Find  by Course ID \n");
        H_printf("\t6. Total Number Of Students \n");
        H_printf("\t7. Update by ID Number \n");
        H_printf("\t8. Show All Information \n");
        H_printf("\t9. Delete by ID Number \n");
        H_printf("\t10. To Exit \n");
        H_printf("\nEnter your choice to perform the task :");
        H_scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            H_printf("\n*****************************************\n");
            Add_From_File(&StudentData);
            break;
        case 2:
            H_printf("\n******************************************\n");
            Add_Manually(&StudentData);
            break;
        case 3:
            H_printf("\n*******************************************\n");
            Find_By_ID(&StudentData);
            break;
        case 4:
            H_printf("\n*******************************************\n");
            Find_By_First_Name(&StudentData);
            break;
        case 5:
            H_printf("\n*******************************************\n");
            Find_Student_IN_Course(&StudentData);
            break;
        case 6:
            Total_Number(&StudentData);
            H_printf("\n*******************************************\n");
            break;
        case 7:
            H_printf("\n*******************************************\n");
            Update_Student_Info(&StudentData);
            H_printf("\n*******************************************\n");
            break;
        case 8:
            H_printf("\n*******************************************\n");
            Show_Student(&StudentData);
            break;
        case 9:
            H_printf("\n*******************************************\n");
            Delete_Student(&StudentData);
            break;
        case 10:
            H_printf("\n*******************************************\n");
            H_printf("Thank You\n");
            exit(1);
            break;
        default:
            H_printf("\n*******************************************\n");
            H_printf("\n  Wrong Option \n") break;
        }
    }

    return 0;
}