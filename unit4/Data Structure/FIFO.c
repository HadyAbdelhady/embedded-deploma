#include <stdio.h>
unsigned int buffer1[5];
typedef struct FIFO
{
    unsigned int lenght;
    unsigned int *base;
    unsigned int *head;
    unsigned int *tail;
    unsigned int count;

} FIFO_S;
typedef enum
{
    FIFO_NO_ERROR,
    FIFO_FULL,
    FIFO_NOTFULL,
    FIFO_NULL,
    FIFO_EMPTY,

} FIFO_STATE;
FIFO_STATE FIFO_ADD(FIFO_S *FIFO, unsigned char item)
{
    if (!FIFO->head || !FIFO->base)
        return FIFO_NULL;
    else if (FIFO->lenght == FIFO->count)
        return FIFO_FULL;

    *(FIFO->head) = item;
    FIFO->count++;
    FIFO->head++;

    if (FIFO->head == FIFO->base + FIFO->lenght)
        FIFO->head = FIFO->base;
    else
        FIFO->head++;
    return FIFO_NO_ERROR;
}
FIFO_STATE FIFO_POP(FIFO_S *FIFO, unsigned int *item)
{
    if (!FIFO->head || !FIFO->base || !FIFO->tail)
        return FIFO_NULL;
    else if (FIFO->count == 0)
        return FIFO_EMPTY;
    FIFO->head--;
    *item = *(FIFO->tail);
    FIFO->count--;
    if (FIFO->tail == FIFO->base + FIFO->lenght)
        FIFO->tail = FIFO->base;
    else
        FIFO->tail++;
    return FIFO_NO_ERROR;
}
FIFO_STATE FIFO_INIT(FIFO_S *FIFO, unsigned int *flag, unsigned int length)
{
    if (flag == NULL)
        return FIFO_NULL;
    FIFO->base = flag;
    FIFO->head = flag;
    FIFO->tail = flag;
    FIFO->lenght = length;
    FIFO->count = 0;
    return FIFO_NO_ERROR;
}
void main()
{
    FIFO_S fifo_1;
    FIFO_INIT(&fifo_1, buffer1, 5);
    int temp;
    for (int i = 0; i < 5; i++)
    {
        if (FIFO_ADD(&fifo_1, i) == FIFO_NO_ERROR)
        {
            printf("ADDED %d \n", i + 1);
        }
    }
    FIFO_POP(&fifo_1, &temp);
    FIFO_POP(&fifo_1, &temp);
    printf("%d \n", fifo_1.count);
}