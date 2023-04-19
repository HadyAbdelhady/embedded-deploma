#ifndef STUDENT_H_
#define STUDENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Platform_Types.h"

#define H_printf(...) {fflush(stdin);fflush(stdout);\
		printf(__VA_ARGS__);\
		fflush(stdin);fflush(stdout);}

#define H_scanf(...) {fflush(stdin);fflush(stdout);\
		scanf(__VA_ARGS__);\
		fflush(stdin);fflush(stdout);}

typedef struct
{
	char fname[50];
	char lname[50];
	int ID;
	float GPA ;
	int courseID[10];
}S_info;

#define TotalNumber 50
S_info Students[TotalNumber];

typedef struct
{
	unsigned int length ;
	unsigned int count  ;
	S_info *base  ;
	S_info *head  ;
	S_info *tail  ;
}S_FIFO;

typedef enum
{
	FIFO_NO_ERROR ,
	FIFO_NULL     ,
	FIFO_EMPTY    ,
	FIFO_FULL
}FIFO_STATUS;

void FIFO_Init( S_FIFO* fifo_buf , S_info* buf , uint32 length );
void Add_From_File( S_FIFO* fifo_buf );
void Add_Manually( S_FIFO* fifo_buf );
void Find_By_ID( S_FIFO* fifo_buf );
void Find_By_First_Name( S_FIFO* fifo_buf );
void Find_Student_IN_Course(S_FIFO* fifo_buf );
void Total_Number( S_FIFO* fifo_buf );
void Delete_Student( S_FIFO* fifo_buf );
void Update_Student_Info( S_FIFO* fifo_buf );
void Show_Student( S_FIFO* fifo_buf );
FIFO_STATUS fifo_is_full( S_FIFO *fifo_buf );
FIFO_STATUS fifo_is_empty( S_FIFO* fifo_buf );
FIFO_STATUS fifo_is_null( S_FIFO* fifo_buf );
int Check_ID(S_FIFO* fifo_buf , S_info* buf , uint32 number);
void Swap(S_info* student1 , S_info * student2);

#endif 