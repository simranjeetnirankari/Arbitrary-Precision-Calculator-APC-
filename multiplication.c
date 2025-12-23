/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
            : tail1: Pointer to the last node of the first double linked list.
            : head2: Pointer to the first node of the second double linked list.
            : tail2: Pointer to the last node of the second double linked list.
            : headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    // TEMPORARY POINTER VARIABLE TO TRAVERSE THE SECOND LINKED LIST/NUMBER
    Dlist *temp2 = *tail2;
    // SHIFT COUNTER TO HANDLE PLACE VALUES
    int shift = 0;

    // INITIALIZE THE RESULT LIST WITH 0
    insert_list(headR, tailR, 0);

    // MULTIPLY EACH DIGIT OF THE SECOND NUMBER WITH THE FIRST NUMBER
    while (temp2 != NULL)
    {
        // TEMPORARY POINTER TO TRAVERSE THE FIRST NUMBER
        Dlist *temp1 = *tail1;
        // TEMPORARY LIST TO STORE INTERMEDIATE RESULTS
        Dlist *headTemp = NULL, *tailTemp = NULL;
        // CARRY VARIABLE FOR MULTIPLICATION
        int carry = 0;

         // MULTIPLY THE CURRENT DIGIT OF THE SECOND NUMBER WITH THE FIRST NUMBER
        while (temp1 != NULL || carry != 0)
        {
            // INITIALIZING PRODUCT WITH THE CARRY FROM THE PREVIOUS STEP
            int product = carry;
            //ITERATING THE LOOP TILL TEMP1 REACHES NULL
            if (temp1 != NULL)
            {
                // MULTIPLY THE DIGITS AND ADD TO THE PRODUCT
                product += temp1->data * temp2->data;
                temp1 = temp1->prev;
            }
            // CALCULATE THE CARRY FOR THE NEXT ITERATION
            carry = product / 10;
            // EXTRACT THE DIGIT TO BE STORED IN THE TEMPORARY LIST
            int digit = product % 10;

            // INSERT THE DIGIT INTO THE TEMPORARY LIST
            if (insert_rlist(&headTemp, &tailTemp, digit) == FAILURE)
            {
                printf("INFO : Insertion Failure\n");
                return FAILURE;
            }
        }

        // SHIFT THE TEMPORARY RESULT BY 'SHIFT' POSITIONS TO HANDLE PLACE VALUES
        for (int i = 0; i < shift; i++)
        {
            insert_list(&headTemp, &tailTemp, 0);
        }

        // ADD THE TEMPORARY RESULT TO THE FINAL RESULT
        Dlist *headSum = NULL, *tailSum = NULL;// TEMPORARY LIST TO STORE THE SUM
        // PERFORM ADDITION
        addition(headR, tailR, &headTemp, &tailTemp, &headSum, &tailSum);

        // UPDATE THE FINAL RESULT
        while (*headR != NULL)
        {
            Dlist *temp = *headR;
            *headR = (*headR)->next;
            free(temp);
        }
        // UPDATE THE HEAD AND THE TAIL OF THE RESULT LIST
        *headR = headSum;
        *tailR = tailSum;

        // MOVE TO THE NEXT DIGIT OF THE SECOND NUMBER
        temp2 = temp2->prev;
        shift++;
    }

    // REMOVE LEADING ZEROS FROM THE RESULT
    while (*headR != NULL && (*headR)->data == 0)
    {
        // REMOVONG ZEROS FROM THE MOST SIGNIFICANT SIDE
        Dlist *temp = *headR;
        *headR = (*headR)->next;
        if (*headR != NULL)
        {
            (*headR)->prev = NULL;
        }
        // FREE THE MEMORY OF THE REMOVED NODE
        free(temp);
    }
    return SUCCESS;
}