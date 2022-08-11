#include "student.h"
void Add_From_File( S_FIFO* fifo_buf )
{
	if(fifo_is_full(fifo_buf) == FIFO_FULL)
	{
		H_printf("[ERORR] Queue is FULL \n");
	}
	else
	{
		//  the file contains the student informaton
		FILE *pfile =fopen("student.txt","r");
		char lines[TotalNumber]; // storing the line
		const char *token ;
		int LineNumber = 0 , parts = 0 , indicator = 0;
		// the file is opened or not
		if(!pfile)
		{
			H_printf("[ERORR] The file can not be opened \n");
		}
		else
		{
			while(fgets(lines ,sizeof(lines),pfile ))
			{
				LineNumber++;
				token = strtok(lines ," ");
				parts = 0 , indicator = 0;
				// looping untill the line end
				while(token != NULL)
				{
					++parts;
					switch(parts)
					{
					case 1:
					{
						if(Check_ID(fifo_buf,fifo_buf->base,atoi(token)) == 0)
						{
							//true ---> ID number is unique
							H_printf("[INFO] ID Number %d added successfully \n",atoi(token));
							fifo_buf->head->ID = atoi(token);
						}
						else
						{
							// false ---> the ID number is not unique
							H_printf("[ERORR] ID Number %d is already taken \n",atoi(token));
							indicator++;
						}
					}
					break;
					case 2:
						strcpy(fifo_buf->head->fname,token);
						break;
					case 3:
						strcpy(fifo_buf->head->lname,token);
						break;
					case 4:
						fifo_buf->head->GPA= atof(token);
						break;
					case 5:
						fifo_buf->head->courseID[0] = atoi(token);
						break;
					case 6:
						fifo_buf->head->courseID[1]= atoi(token);
						break;
					case 7:
						fifo_buf->head->courseID[2] = atoi(token);
						break;
					case 8:
						fifo_buf->head->courseID[3] = atoi(token);
						break;
					case 9:
						fifo_buf->head->courseID[4] = atoi(token);
						break;
					}

					token = strtok(NULL ," \n");
				}
				if(indicator == 1)
				{
					continue;
				}
				// change the pointer to points to next element
				fifo_buf->count++;
				// the head pointer reaches the end 
				if(fifo_buf->head == (S_info*)(fifo_buf->base + sizeof(S_info)*fifo_buf->length))
				{
					fifo_buf->head = fifo_buf->base;
				}
				else
				{
					fifo_buf->head++;
				}
			}
		}
		fclose(pfile);
		H_printf("[INFO] Student Details is added successfully\n");
	}
}

int Check_ID(S_FIFO* fifo_buf , S_info* buf , uint32 number)
{
	int flag = 0 , counter;
	// looping by number of students
	for(counter = 0 ; counter < fifo_buf->count ; counter++)
	{
		if(number == buf[counter].ID)
		{
			flag++;
			break ;
		}
	}
	return flag;
}