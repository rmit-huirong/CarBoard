
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */

#include "carboard.h"

int main(void)
{	
	int menuInput = 0;
	char menuList[MENU_LENGTH + NULL_SPACE];
	
	sprintf(menuList, "\n"
					"Welcome to Car Board\n"
					"--------------------\n"
					"1. Play game\n"
					"2. Show student's information\n"
					"3. Quit\n"
					"\n"
					"Please enter your choice: ");
					
	inputValid(menuList, &menuInput, INPUT_LENGTH);
	
	/* To exit the program. */
    return EXIT_SUCCESS;
}

void inputValid(char* list, int* input, unsigned length)
{
	Boolean inputValid = FALSE;
	char temp[TEMP_LENGTH + EXTRA_SPACES];
	int tempInteger = 0;
	char* endPtr;
	
	/* Quit the loop when input is 3 */
	do
	{
		printf("%s", list);
		fgets(temp, length + EXTRA_SPACES, stdin);
		
		/* Check if the input is too long */
		if (temp[strlen(temp) - NULL_SPACE] != '\n')
		{
			printf(INVALID_INPUT_MESSAGE);
			readRestOfLine();
		}
		else
		{
			temp[strlen(temp) - NULL_SPACE] = NULL_TERMINATED;
			
			/* Cast the input into an integer */
			tempInteger = (int) strtol(temp, &endPtr, 10);
			if (strcmp(endPtr, EMPTY_STRING) != 0)
			{
				printf(INVALID_INPUT_MESSAGE);
			}
			
			/* Check if the integer is from 1 to 3 */
			else if (tempInteger < MIN || tempInteger > MAX)
			{
				printf(INVALID_INPUT_MESSAGE);
			}
			else
			{
				*input = tempInteger;
				inputValid = TRUE;
				menuOption(*input);
			}
		}
	}while(!inputValid || *input == OPTION_1 || *input == OPTION_2);
}

void menuOption(int option)
{
	
	switch(option)
	{
		case OPTION_1:
		playGame();
		break;
		case OPTION_2:
		showStudentInformation();
		break;
		case OPTION_3:
		printf("\nHave a good day. Good bye! \n\n");
		break;
	}
}

void showStudentInformation()
{    
	printf("\n");
	printf("-----------------------------------\n");
	printf("Name: %s\n", STUDENT_NAME);
	printf("Student ID: %s\n", STUDENT_ID);
	printf("Email: %s\n", STUDENT_EMAIL);
	printf("-----------------------------------\n");
}
