#include "linked_list.h"
#include <stdio.h>

void main()
{
    short choice, choice2;
    while (choice2 != 10)
    {
        options();
        scanf("%d", &choice);
        switch (choice)
        {

        case 1:
            NEW_STUDENT();
            break;
        case 2:
            DELETE_STUDENT();
            break;
        case 3:
            ViewStudent();
            break;
        case 4:
            Hprint("the list has (%d) students enrolled", ListLength());
            break;
        case 5:
            GetMiddle();
            break;
        case 6:
            ViewfromEnd();
            break;
        case 7:
            reverse();
            break;
        case 10:
            choice2 = 10;
            Hprint("GOODBYE...");
            break;
        default:
            Hprint("\n wrong option Try again");
            break;
        }
    }
}