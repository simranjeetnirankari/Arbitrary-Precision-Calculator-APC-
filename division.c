/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headQ);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
            : tail1: Pointer to the last node of the first double linked list.
            : head2: Pointer to the first node of the second double linked list.
            : tail2: Pointer to the last node of the second double linked list.
            : headQ: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
   // CHECK IF DIVISOR IS ZERO
    Dlist *temp2 = *head2;
    while (temp2 != NULL && temp2->data == 0)
        temp2 = temp2->next;
    if (temp2 == NULL)
    {
        printf("Error: Division by zero\n");
        return FAILURE;
    }

    // INITIALIZE QUOTIENT LIST TO 0
    *headR = *tailR = NULL;
    insert_list(headR, tailR, 0); // QUOTIENT STARTS AT 0

    // COPY DIVIDEND TO A TEMPORARY LIST (REMAINDER)
    Dlist *headQ = NULL, *tailQ = NULL;
    Dlist *temp1 = *head1;
    while (temp1 != NULL)
    {
        // COPY EACH DIGIT TO THE REMAINDER LIST
        insert_list(&headQ, &tailQ, temp1->data);
        temp1 = temp1->next;
    }

    // PERFORM DIVISION USING REPEATED SUBTRACTION WHILE REMAINDER IS GREATER THAN OR EQUAL TO DIVISOR
    while (compare_lists(headQ, *head2) >= 0)
    {
        // SUBTRACT DIVISOR FROM REMAINDER
        Dlist *headSub = NULL, *tailSub = NULL;
        subtraction(&headQ, &tailQ, head2, tail2, &headSub, &tailSub);

        // UPDATE REMAINDER WITH THE RESULT OF SUBTRACTION
        while (headQ != NULL)
        {
            Dlist *temp = headQ;
            headQ = headQ->next;
            free(temp);
        }
        headQ = headSub;
        tailQ = tailSub;

        // INCREMENT QUOTIENT BY 1
        Dlist *tempQ = *tailR;
        int carry = 1;
        while (tempQ != NULL && carry != 0)
        {
            // ADD CARRY TO THE CURRENT DIGIT
            int sum = tempQ->data + carry;
            // UPDATE THE DIGIT
            tempQ->data = sum % 10;
            // CALCULATE THE NEW CARRY
            carry = sum / 10;
            // MOVE TO THE NEXT DIGIT
            tempQ = tempQ->prev;
        }
        if (carry != 0)
        {
            // INSERT CARRY IF IT EXISTS
            insert_rlist(headR, tailR, carry);
        }
    }

    // FREE THE TEMPORARY REMAINDER LIST
    while (headQ != NULL)
    {
        Dlist *temp = headQ;
        headQ = headQ->next;
        free(temp);
    }
    // RETURN SUCCESS AFTER COMPLETION
    return SUCCESS;
}

