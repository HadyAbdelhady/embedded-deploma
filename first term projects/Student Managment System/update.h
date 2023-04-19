#include "student.h"

void Update_Student_Info( S_FIFO* fifo_buf )
{
	int modified_ID , counter , choice , flag = 0;
	S_info *ptail = fifo_buf->tail;
	if(fifo_is_empty(fifo_buf) == FIFO_EMPTY)
	{
		H_printf("[ERORR] The Queue is empty \n");
	}
	else
	{
		H_printf("Enter the ID to update the entry :");
		H_scanf("%d",&modified_ID);
		for(counter = 0 ; counter < fifo_buf->count ; counter++)
		{
			if(modified_ID == ptail->ID)
			{
				H_printf("\t1.First Name\n");
				H_printf("\t2.Last Name\n");
				H_printf("\t3.Roll Number\n");
				H_printf("\t4.GPA\n");
				H_printf("\t5.courses\n");
				H_printf("Choose the information you want to update :");
				H_scanf("%d",&choice);
				switch(choice)
				{
				case 1:
					H_printf("Enter the new first name :");
					gets(ptail->fname);
					break;
				case 2:
					H_printf("Enter the new last name :");
					gets(ptail->lname);
					break;
				case 3:
					H_printf("Enter the new ID :");
					H_scanf("%d",&ptail->ID);
					break;
				case 4:
					H_printf("Enter the new GPA :");
					H_scanf("%f",&ptail->GPA);
					break;
				case 5:
					H_printf("Enter the new course 1 ID :");
					H_scanf("%d",&ptail->courseID[0]);
					H_printf("Enter the new course 2 ID :");
					H_scanf("%d",&ptail->courseID[1]);
					H_printf("Enter the new course 3 ID :");
					H_scanf("%d",&ptail->courseID[2]);
					H_printf("Enter the new course 4 ID :");
					H_scanf("%d",&ptail->courseID[3]);
					H_printf("Enter the new course 5 ID :");
					H_scanf("%d",&ptail->courseID[4]);
                   break;
				}
				flag = 1;
			}

			ptail++;
		}
		if(flag==0)
		{
			H_printf("[ERROR] ID %d is not found \n",modified_ID);
		}
	}

}