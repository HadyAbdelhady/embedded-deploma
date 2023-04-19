#include "student.h"

void Find_Student_IN_Course(S_FIFO* fifo_buf )
{
	int row , col , required_course_ID , flag = 0;
	S_info *ptail = fifo_buf->tail ;
	if(fifo_is_empty(fifo_buf) == FIFO_EMPTY)
	{
		H_printf("[ERORR] The Queue is empty \n");
	}
	else
	{
		H_printf("Enter the course ID :");
		H_scanf("%d",&required_course_ID);
		for(row = 0 ; row < fifo_buf->count ; row++)
		{
			for(col =0 ; col < 5 ; col++)
			{
				if(required_course_ID == ptail->courseID[col])
				{
					H_printf("Student first name : %s\n",ptail->fname);
					H_printf("Student last name : %s\n",ptail->lname);
					H_printf("Student ID number : %d\n",ptail->ID);
					H_printf("Student GPA : %0.2f\n",ptail->GPA);
					flag = 1;
					break;
				}
			}
			ptail++;
		}
		if(flag==0)
		{
			H_printf("[ERROR] The course ID %d is not found \n",required_course_ID);
		}
	}
}
