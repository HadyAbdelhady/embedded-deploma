#include "student.h"

void Find_By_First_Name( S_FIFO* fifo_buf )
{
	char required_fname[50];
	int  counter , flag=0 ;
	S_info *ptail = fifo_buf->tail ;
	if(fifo_is_empty(fifo_buf) == FIFO_EMPTY)
	{
		H_printf("[ERORR] The Queue is empty \n");
	}
	else
	{
		H_printf("Enter the First Name of the student :");
		gets(required_fname);
		for(counter = 0 ; counter < fifo_buf->count ; counter++)
		{
			if(strcmp(required_fname,ptail->fname) == 0)
			{
				H_printf("The Student Details are \n*******************\n");
				H_printf("Student first name : %s\n",ptail->fname);
				H_printf("Student last name : %s\n",ptail->lname);
				H_printf("Student ID number : %d\n",ptail->ID);
				H_printf("Student GPA : %0.2f\n",ptail->GPA);
				for (int i = 0; i < 5; i++)
			{
				H_printf("The course ID : %d\n",ptail->courseID[i]);
			}
				flag = 1;
			}
			ptail++;
		}
		if(flag==0)
		{
			H_printf("[ERROR] First Name %s is not found \n",required_fname);
		}
	}
}
