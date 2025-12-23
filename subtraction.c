/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"
/* Definition goes here */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	// TEMPORARY POINTERS TO TRAVERSE BOTH LISTS
	Dlist *temp1 = *tail1, *temp2 = *tail2;
	// BORROW VARIABLE TO HANDLE SUBTRACTION BORROW
	int borrow = 0;

	// TRAVERSE BOTH LISTS UNTIL ALL NODES ARE PROCESSED
	while (temp1 != NULL || temp2 != NULL)
	{
		// INITIALIZING THE DIFFERENCE WITH THE BORROW FROM THE PREVIOUS STEP
		int diff = borrow;

		// SUBTRACT DATA FROM THE FIRST LIST
		if (temp1 != NULL)
		{
			// ADD THE DIGIT FROM THE FIRST LIST TO THE DIFFERENCE
			diff += temp1->data;
			// MOVE TO THE NEXT DIGIT OF THE FIRST LIST
			temp1 = temp1->prev;
		}

		// SUBTRACT DATA FROM THE SECOND LIST 
		if (temp2 != NULL)
		{
			// SUBTRACT THE DIGIT FROM THE SECOND LIST FROM THE DIFFERENCE
			diff -= temp2->data;
			// MOVE TO THE NEXT DIGIT OF THE SECOND LIST
			temp2 = temp2->prev;
		}

		//BORROW IF THE DIFFERENCE IS NEGATIVE
		if (diff < 0)
		{
			// ADD 10 TO THE DIFFERENCE TO HANDLE BORROW
		    diff += 10;
			// SET BORROW FOR THE NEXT ITERATION
		    borrow = -1;
		}
		else
		{
		    borrow = 0;// RESET BORROW IF NO BORROW IS NEEDED
		}

		// INSERT THE DIGIT INTO THE RESULT LIST
		if (insert_rlist(headR, tailR, diff) == FAILURE)
		{
			printf("INFO : Insertion Failure\n");
			return FAILURE;
		}
	}

	// REMOVE LEADING ZEROS FROM THE RESULT
	while (*headR != NULL && (*headR)->data == 0)
	{
		Dlist *temp = *headR;
		*headR = (*headR)->next;
		if (*headR != NULL)
		{
			(*headR)->prev = NULL;
		}
		free(temp);
	}

	return SUCCESS;
}
