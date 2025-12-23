#include "apc.h"
//FUNCTION TO INSERT THE ELEMENTS IN LINKED LIST
int insert_list(Dlist **head, Dlist **tail, int data)
{
    // ALLOCATING THE MEMORY
    Dlist *new = malloc(sizeof(Dlist));
    // VALIDATING THE ALLOCATED MEMORY
    if (new == NULL)
    {
        return FAILURE;
    }
    // UPDATING THE NEW NODE WITH DATA
    new->data = data;
    // UPDATING THE NEW NODE WITH LINKS
    new->prev = NULL;
    new->next = NULL;
    // IF LIST IS EMPTY ADDING NEW NODE
    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }
    // ADD THE ADDRESS OF NEW NODE TO THE TAIL->NEXT
    (*tail)->next = new;
    new->prev = *tail; // ADD THE ADDRESS OF TAIL NODE TO THE NEW->PREV
    *tail = new;       // UPDATING THE TAIL WITH NEW ADDRESS
    return SUCCESS;
}
//FUNCTION TO INSERT DATA IN RESULTANT LIST
int insert_rlist(Dlist **head, Dlist **tail, int data)
{
    // ALLOCATING THE MEMORY
    Dlist *new = malloc(sizeof(Dlist));
    // VALIDATING THE ALLOCATED MEMORY
    if (new == NULL)
    {
        return FAILURE;
    }
    // UPDATING THE NEW NODE WITH DATA
    new->data = data;
    // UPDATING THE NEW NODE WITH LINKS
    new->prev = NULL;
    new->next = NULL;
    // IF LIST IS EMPTY ADDING NEW NODE
    if (*head == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }
    // ADD THE ADDRESS OF NEW NODE TO THE HEAD->PREV
    (*head)->prev = new;
    new->next = *head; // ADD THE ADDRESS OF HEAD NODE TO THE NEW->NEXT
    *head = new;       // UPDATING THE HEAD WITH NEW ADDRESS
    return SUCCESS;
}

// Function to print the doubly linked list
void print_list(Dlist *head)
{
    Dlist *current = head;
    while (current != NULL)
    {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}

// FUNCTION TO COMPARE TWO NUMBERS STORED IN LINKED LISTS
int compare_lists(Dlist *head1, Dlist *head2)
{
    // TEMPORARY POINTERS TO TRAVERSE THE LISTS
    Dlist *temp1 = head1, *temp2 = head2;

     // SKIP LEADING ZEROS IN BOTH LISTS
    while (temp1 != NULL && temp1->data == 0)
        temp1 = temp1->next;
    while (temp2 != NULL && temp2->data == 0)
        temp2 = temp2->next;

    // CALCULATE THE LENGTHS OF THE TWO LISTS AFTER SKIPPING LEADING ZEROS
    int len1 = 0, len2 = 0;
    while (temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }
    while (temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    // COMPARE THE LENGTHS OF THE TWO LISTS
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    // IF LENGTHS ARE EQUAL COMPARING DIGIT BY DIGIT
    temp1 = head1;
    temp2 = head2;
    while (temp1 != NULL && temp2 != NULL)
    {
        if (temp1->data > temp2->data)
            return 1;
        if (temp1->data < temp2->data)
            return -1;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0; // NUMBERS ARE EQUAL
}
