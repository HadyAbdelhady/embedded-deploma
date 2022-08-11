#include "student.h"
void Add_Manually(S_FIFO *fifo_buf)
{
	int indicator = 0;
	if (fifo_is_full(fifo_buf) == FIFO_FULL)
	{
		H_printf("[ERORR] Queue is FULL \n");
	}
	else
	{
		H_printf("Add the Student Details \n");
		H_printf("\n*******************************************\n");
		H_printf("Enter the ID Number :");
		H_scanf("%d",&fifo_buf->head->ID);
		if (Check_ID(fifo_buf, fifo_buf->base, fifo_buf->head->ID) == 1)
		{
			H_printf("[ERORR] ID Number %d is already taken \n", fifo_buf->head->ID);
			indicator = 1;
		}
		else
		{
			fifo_buf->head->ID = fifo_buf->head->ID;
			H_printf("Enter the first name of student :");
			H_scanf("%s", fifo_buf->head->fname);
			H_printf("Enter the last name of student :");
			H_scanf("%s", fifo_buf->head->lname);
			H_printf("Enter the GPA you obtained :");
			H_scanf("%f", &fifo_buf->head->GPA);
			for (int i = 0; i < 5; i++)
			{
				H_printf("Enter ID for Course Number %d  :  ", i + 1);
				H_scanf("%d", &fifo_buf->head->courseID[i]);
			}
		}
		if (indicator != 1)
		{
			// change the pointer to points to next element
			fifo_buf->count++;
			// check if the head pointer reaches the end or not
			if (fifo_buf->head == (S_info *)(fifo_buf->base + sizeof(S_info) * fifo_buf->length))
			{
				fifo_buf->head = fifo_buf->base;
			}
			else
			{
				fifo_buf->head++;
			}
		}
	}
}
