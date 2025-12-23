/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* Definition goes here */
    // TEMPORARY POINTERS TO TRAVERSE BOTH LISTS
    Dlist *temp1 = *tail1, *temp2 = *tail2;
    // CARRY VARIABLE TO HANDLE ADDITION CARRY
    int carry = 0;

    // TRAVERSE BOTH LISTS UNTIL ALL NODES ARE PROCESSED
    while (temp1 != NULL || temp2 != NULL || carry != 0)
    {
        int sum = carry; // INITIALIZE SUM WITH THE CARRY FROM THE PREVIOUS STEP

        // ADD DATA FROM THE FIRST LIST 
        if (temp1 != NULL)
        {
            sum += temp1->data; // ADD THE DIGIT FROM THE FIRST LIST TO THE SUM
            temp1 = temp1->prev;// MOVE TO THE NEXT DIGIT OF THE FIRST LIST
        }

        // ADD DATA FROM THE SECOND LIST 
        if (temp2 != NULL)
        {
            sum += temp2->data; // ADD THE DIGIT FROM THE SECOND LIST TO THE SUM
            temp2 = temp2->prev;// MOVE TO THE NEXT DIGIT OF THE SECOND LIST
        }

        // CALCULATE CARRY AND DIGIT TO INSERT
        carry = sum / 10;// CALCULATE THE CARRY FOR THE NEXT ITERATION
        // EXTRACT THE DIGIT TO BE STORED IN THE RESULT LIST
        int digit = sum % 10;

        // INSERT THE DIGIT INTO THE RESULT LIST
        if (insert_rlist(headR, tailR, digit) == FAILURE)
        {
            printf("INFO : Insertion Failure\n");
            return FAILURE;
        }
    }

    return SUCCESS;
}