#include "student.h"
void Total_Number(S_FIFO *fifo_buf)
{
	H_printf("\n******************************************\n");
	H_printf("[INFO] The total number of student is %d\n", fifo_buf->count);
	H_printf("[INFO] You can add %d more students\n", TotalNumber - (fifo_buf->count));
	H_printf("[INFO] You can add up to %d students\n", TotalNumber);
}

void Show_Student(S_FIFO *fifo_buf)
{
	int counter;
	S_info *ptail = fifo_buf->tail;
	if (fifo_is_empty(fifo_buf) == FIFO_EMPTY)
	{
		H_printf("[ERORR] The Queue is empty \n");
	}
	// looping untill show all students
	for (counter = 0; counter < fifo_buf->count; counter++)
	{
		H_printf("\n*******************************************\n");
		H_printf("Student first name : %s\n", ptail->fname);
		H_printf("Student last name : %s\n", ptail->lname);
		H_printf("Student ID number : %d\n", ptail->ID);
		H_printf("Student GPA : %0.2f\n", ptail->GPA);
		for (int i = 0; i < 5; i++)
		{
			H_printf("The course ID is : %d\n", ptail->courseID[i]);
		}
		ptail++;
	}
	H_printf("\n*******************************************\n");
}
