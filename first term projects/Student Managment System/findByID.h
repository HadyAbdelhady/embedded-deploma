#include "student.h"
void Find_By_ID(S_FIFO *fifo_buf)
{
	int required_ID, counter, flag = 0;
	S_info *ptail = fifo_buf->tail;
	if (fifo_is_empty(fifo_buf) == FIFO_EMPTY)
	{
		H_printf("[ERORR] The Queue is empty \n");
	}
	else
	{
		H_printf("Enter the ID Number of the student :");
		H_scanf("%d", &required_ID);
		for (counter = 0; counter < fifo_buf->count; counter++)
		{
			if (required_ID == ptail->ID)
			{
				H_printf("Student ID number : %d\n", ptail->ID);
				H_printf("Student first name : %s\n", ptail->fname);
				H_printf("Student last name : %s\n", ptail->lname);
				H_printf("Student GPA : %0.2f\n", ptail->GPA);
				for (int i = 0; i < 5; i++)
			{
				H_printf("The course ID is : %d\n", ptail->courseID[i]);
			}
				flag = 1;
				break;
			}

			ptail++;
		}
		if (flag == 0)
		{
			H_printf("[ERROR] ID %d is not found \n", required_ID);
		}
	}
}
