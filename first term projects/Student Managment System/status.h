#include "student.h"
// API to check if FIFO is empty
FIFO_STATUS fifo_is_empty( S_FIFO *fifo_buf )
{
	if(fifo_is_null(fifo_buf) == FIFO_NULL)
	{
		H_printf("[ERORR] The Queue is not exist !!\n");
	}
	if(fifo_buf->count == 0)
	{
		return FIFO_EMPTY;
	}
	else
	{
		return FIFO_NO_ERROR ;
	}
}
FIFO_STATUS fifo_is_full( S_FIFO* fifo_buf )
{
	if(fifo_is_null(fifo_buf) == FIFO_NULL)
	{
		H_printf("[ERORR] The Queue is not exist !!\n");
	}
	if(fifo_buf->length == fifo_buf->count)
	{
		return FIFO_FULL;
	}
	else
	{
		return FIFO_NO_ERROR ;
	}
}

FIFO_STATUS fifo_is_null( S_FIFO* fifo_buf )
{
	if(!fifo_buf->base || !fifo_buf->head || !fifo_buf->tail)
	{
		return FIFO_NULL ;
	}
	else
	{
		return FIFO_NO_ERROR;
	}
}