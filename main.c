/**************************************************************************************************************************************************************
 *TITLE			: ARBITRARY PRECISION CALCULATOR (APC)
				  MAIN FUNCTION(DRIVER FUNCTION)
 *NAME          : SIMRANJEET NIRANKARI
 *DESCRIPTION	: THE PROJECT IS DESIGNED TO IMPLEMENT VARIOUS MATHEMATICAL OPERATIONS OF GIVEN TWO BIG NUMBERS BY STORING IN AN ABSTRACT DATA TYPE (ADT)
				  LIKE LINKED LIST.
				  THIS FUNCTION IS USED AS THE DRIVER FUNCTION FOR THE ALL THE FUNCTIONS
 *DATE			: 28-01-2025
 ***************************************************************************************************************************************************************/
#include "apc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// DECLARING THE POINTERS FOR THE DOUBLE LINKED LISTS
	Dlist *headR = NULL, *tailR = NULL;
	Dlist *head1 = NULL, *tail1 = NULL;
	Dlist *head2 = NULL, *tail2 = NULL;
	Dlist *temp = NULL;
	// VARIABLES USED IN THE PROGRAM
	char operator; // STORE THE OPERATOR
	// VARIABLE TO KEEP THE TRACK OF INDEX
	int i = 0;
	// VALIDATE IF THE NUMBER OF ARGUMENTS IS LESS THAN 4
	if (argc < 4)
	{
		printf("Usage: %s <number1> <operator> <number2>\n", argv[0]);
		return 1;
	}

	// STORE THE OPERANDS AND OPERATOR FROM COMMAND LINE ARGUMENTS IN POINTER VARIABLE
	char *operand1 = argv[1];
	operator= argv[2][0];
	char *operand2 = argv[3];

	// TRACK THE SIGNS OF THE OPERANDS
	int sign1 = 0, sign2 = 0;
	// CHECK IF THE OPERAND IS NEGATIVE AND SKIP THE '-' SIGN
	if (operand1[0] == '-')
	{
		sign1 = 1;
		operand1++; // SKIP THE '-' SIGN
	}
	if (operand2[0] == '-')
	{
		sign2 = 1;
		operand2++;
	}

	// INSERT CHARACTERS OF THE FIRST OPERAND INTO THE FIRST LINKED LIST
	while (operand1[i] != '\0')
	{
		if (insert_list(&head1, &tail1, operand1[i] - '0') == FAILURE) // insert last
		{
			printf("INFO : Insertion Failure\n");
		}
		i++;
	}

	i = 0; // RESET INDEX FOR THE SECOND OPERAND

	// INSERT CHARACTERS OF THE SECOND OPERAND INTO THE SECOND LINKED LIST
	while (operand2[i] != '\0')
	{
		if (insert_list(&head2, &tail2, operand2[i] - '0') == FAILURE)
		{
			printf("INFO : Insertion Failure\n");
		}
		i++;
	}

	int resultant_sign = 0; // TRACK IF THE RESULT IS NEGATIVE

	// PERFORMIING THE OPERATION BASED ON THE OPERATOR
	switch (operator)
	{
	case '+':
		if (sign1 == sign2)
		{
			// IF BOTH NUMBERS HAVE THE SAME SIGN
			if(addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == -1)
			{
				return 1;
			}
			resultant_sign = sign1; // Result has the same sign
		}
		else
		{
			// PERFORMING SUBTRACTION IF NUMBERS HAVE DIFFERENT SIGNS
			if (compare_lists(head1, head2) >= 0)
			{
				// If |head1| >= |head2|
				if(subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == -1)
				{
					return 1;
				}
				resultant_sign = sign1; // RESULT HAS THE SIGN OF THE FIRST OPERAND
			}
			else
			{
				// If |head1| < |head2|
				if(subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == -1)
				{
					return 1;
				}
				resultant_sign = sign2; // RESULT HAS THE SIGN OF THE SECOND OPERAND
			}
		}
		printf("Result: ");
		// IF RESULT IS ZERO
		if (headR == NULL)
		{
			printf("0\n");
		}
		// PRINT NEGATIVE SIGN IF RESULT IS NEGATIVE
		else if (resultant_sign)
		{
			printf("-");
		}
		// PRINT THE RESULT LIST
		print_list(headR);

		break;

	case '-':
		if (sign1 == sign2)
		{
			// IF NUMBERS HAVING DIFFERENT SIGN PERFORMING SUBTRACTION
			if (compare_lists(head1, head2) >= 0)
			{
				// If |head1| >= |head2|
				if(subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR) == -1)
				{
					return 1;
				}
				resultant_sign = sign1; // RESULT HAS THE SIGN OF THE FIRST OPERAND
			}
			else
			{
				// If |head1| < |head2|
				if(subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR) == -1)
				{
					return 1;
				}
				resultant_sign = !sign1; // RESULT HAS THE SIGN OF THE SECOND OPERAND
			}
		}
		else
		{
			// PERFORMING ADDITION IF THE NUMBERS HAVE DIFFERENT SIGNS
			if(addition(&head1, &tail1, &head2, &tail2, &headR, &tailR) == -1)
			{
				return 1;
			}
			resultant_sign = sign1; // RESULT HAS THE SIGN OF THE FIRST OPERAND
		}
		printf("Result: ");
		// IF RESULT IS ZERO
		if (headR == NULL)
		{
			printf("0\n");
		}
		// PRINT NEGATIVE SIGN IF RESULT IS NEGATIVE
		else if (resultant_sign)
		{
			printf("-");
		}
		// PRINT THE RESULT LIST
		print_list(headR);

		break;

	case 'X':
		// PERFORMING MULTIPLICATION
		if(multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR) == -1)
		{
			return 1;
		}
		if (sign1 != sign2) // RESULT IS NEGATIVE IF SIGNS ARE DIFFERENT
		{
			resultant_sign = 1;
		}
		else
		{
			resultant_sign = 0;
		}
		printf("Result: ");
		// IF RESULT IS ZERO
		if (headR == NULL)
		{
			printf("0\n");
		}
		// PRINT NEGATIVE SIGN IF RESULT IS NEGATIVE
		else if (resultant_sign)
		{
			printf("-");
		}
		// PRINT THE RESULT LIST
		print_list(headR);

		break;

	case '/':
		Dlist *headR = NULL, *tailRheadR = NULL; // QUOTIENT
		// PERFORMING DIVISION
		if (division(&head1, &tail1, &head2, &tail2, &headR, &tailR) == -1)
		{
			return 1;
		}
		if (sign1 != sign2) // RESULT IS NEGATIVE IF SIGNS ARE DIFFERENT
		{
			resultant_sign = 1;
		}
		else
		{
			resultant_sign = 0;
		}
		printf("Result: ");
		// IF RESULT IS ZERO, PRINT 0 AND SKIP THE NEGATIVE SIGN
		if (headR == NULL || (headR->next == NULL && headR->data == 0))
		{
			printf("0\n");
		}
		else
		{
			// PRINT NEGATIVE SIGN IF RESULT IS NEGATIVE
			if (resultant_sign)
			{
				printf("-");
			}
			// PRINT THE RESULT LIST
			print_list(headR);
		}

		break;

	default:
		// DEFAULT CASE FOR INVALID OPERATOR
		printf("Invalid Input:-( Try again...\n");
		printf("Usage: %s <number1> + <number2>\n", argv[0]);
		printf("Usage: %s <number1> - <number2>\n", argv[0]);
		printf("Usage: %s <number1> X <number2>\n", argv[0]);
		printf("Usage: %s <number1> / <number2>\n", argv[0]);
	}

	// FREE MEMORY ALLOCATED FOR THE LINKED LISTS
	while (head1 != NULL)
	{
		Dlist *temp = head1;
		head1 = head1->next;
		free(temp);
	}
	while (head2 != NULL)
	{
		Dlist *temp = head2;
		head2 = head2->next;
		free(temp);
	}
	while (headR != NULL)
	{
		Dlist *temp = headR;
		headR = headR->next;
		free(temp);
	}

	return 0;
}