#include "student.h"
void Delete_Student( S_FIFO* fifo_buf )
{
	int deleted_ID , counter , flag = 0;
	S_info *ptail = fifo_buf->tail , *pswap = fifo_buf->tail;
	if(fifo_is_empty(fifo_buf) == FIFO_EMPTY)
	{
		H_printf("[ERORR] The Queue is empty \n");
	}
	else
	{
		H_printf("Enter the ID Number to delete :");
		H_scanf("%d",&deleted_ID);
		for(counter = 0 ; counter < fifo_buf->count ; counter++)
		{
			if(deleted_ID == ptail->ID)
			{
				pswap = ptail;
				for(counter = 1 ; counter < fifo_buf->count ; counter++)
				{   // swap until the student removed in the first position
					Swap(pswap , pswap-1);
					pswap--;
				}
				// change the pointer to points to previous element
				fifo_buf->count--;
				// head pointer reaches the end or not
				if(fifo_buf->tail == (S_info*)(fifo_buf->base + sizeof(S_info)*fifo_buf->length))
				{
					fifo_buf->tail = fifo_buf->base;
				}
				else
				{
					fifo_buf->tail++;
				}
				flag = 1;
				H_printf("[INFO] ID %d removed successfully \n",ptail->ID);
				break;

			}
			ptail++;
		}
		if(flag==0)
		{
			H_printf("[ERROR] The ID Number %d not found \n",deleted_ID);
		}

	}
}
void Swap(S_info* student1 , S_info * student2)
{
	S_info temp;
	temp = *student1;
	*student1 = *student2;
	*student2 = temp ;

}
