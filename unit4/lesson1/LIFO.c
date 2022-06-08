#include <stdio.h>
// LAST INPUT FIRST OUTPUT
unsigned int buffer1[5];
typedef struct LIFO
{
    unsigned int lenght;
    unsigned int *base;
    unsigned int *head;
    unsigned int count;

} LIFO_S;
typedef enum
{
    LIFO_NO_ERROR,
    LIFO_FULL,
    LIFO_NOTFULL,
    LIFO_NULL,
    LIFO_EMPTY,

} LIFO_STATE;
LIFO_STATE LIFO_ADD(LIFO_S *lifo, unsigned char item)
{
    if (!lifo->head  || !lifo->base)
        return LIFO_NULL;
    else if (lifo->lenght == lifo->count)
        return LIFO_FULL;
    
    *(lifo->head) = item;
    lifo->count++;
    lifo->head++;
    return LIFO_NO_ERROR;
}
LIFO_STATE LIFO_POP(LIFO_S *lifo, unsigned int *item)
{
    if (!lifo->head || !lifo->base)
        return LIFO_NULL;
    else if ( lifo->count==0)
        return LIFO_EMPTY;
    lifo->head--;
    *item =*(lifo->head) ;
    lifo->count--;
    return LIFO_NO_ERROR;
}
LIFO_STATE LIFO_INIT(LIFO_S *lifo, unsigned int *flag,unsigned int length)
{
    if (flag == NULL)
        return LIFO_NULL;
    lifo->base = flag;
    lifo->head = flag;
    lifo->lenght = length;
    lifo->count = 0;
    return LIFO_NO_ERROR;
}
void main()
{
    LIFO_S lifo_1;
    LIFO_INIT(&lifo_1, buffer1,5);
    int temp=0;
    for (int i = 0; i < 5; i++)
    {
        if (LIFO_ADD(&lifo_1, i) == LIFO_NO_ERROR)
        {
            printf("ADDED %d \n", i + 1);
        }
    }
     for (int i = 0; i < 5; i++)
    {
        if (LIFO_POP(&lifo_1, &temp) == LIFO_NO_ERROR)
        {
            printf("Deleted %d \n", temp+1);
        }
    }
}