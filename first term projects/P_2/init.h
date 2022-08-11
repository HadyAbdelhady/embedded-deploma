#include "student.h"
void FIFO_Init( S_FIFO* fifo_buf , S_info* buf , uint32 length )
{
	// checking if the program reseved the array of student
	if(buf == NULL)
	{
		H_printf("[ERORR] NO Queue !!\n");
	}
	else
	{
		// initialize head , base and tail pointers points to the base of the array
		fifo_buf->base = buf ;
		fifo_buf->head = buf ;
		fifo_buf->tail = buf ;
		fifo_buf->length = length ;
		fifo_buf->count = 0;
	}
}