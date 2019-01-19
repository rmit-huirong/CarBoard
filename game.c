
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */

#include "game.h"

void playGame()
{
	char anykey[ANYKEY_LENGTH];
	char command_0_List[COMMAND_0_LIST_LENGTH + NULL_SPACE];
	char command_1_List[COMMAND_1_LIST_LENGTH + NULL_SPACE];
	char command_2_List[COMMAND_2_LIST_LENGTH + NULL_SPACE];
    Cell board[BOARD_HEIGHT][BOARD_WIDTH];
	Player player;
	Boolean quitValid = FALSE;

	printf(	"\nYou can use the following commands to play the game:\n\n"
			"load <g>\n"
			"   g: number of the game board to load\n"
			"init <x>,<y>,<direction>\n"
			"   x: horizontal position of the car on the board (between 0 & 9)\n"
			"   y: vertical position of the car on the board (between 0 & 9)\n"
			"   direction: direction of the car’s movement "
			"(north, east, south, west)\n"
			"forward (or f)\n"
			"turn_left (or l)\n"
			"turn_right (or r)\n"
			"quit\n\n"
			"Press any key to continue...");
			
	fgets(anykey, ANYKEY_LENGTH, stdin);
	readRestOfLine();
	
    initialiseBoard(board);
	
	sprintf(command_0_List, 
		"\nAt this stage of the program, only two commands are acceptable:\n"
		"load <g>\n"
		"quit\n\n"
		"I wanna ");
		
	sprintf(command_1_List, 
		"\nAt this stage of the program, only three commands are acceptable:\n"
		"load <g>\n"
		"init <x>,<y>,<direction>\n"
		"quit\n\n"
		"I wanna ");
		
	sprintf(command_2_List,
		"\nAt this stage of the program, only four commands are acceptable:\n"
		"forward (or f)\n"
		"turn_left (or l)\n"
		"turn_right (or r)\n"
		"quit\n\n"
		"I wanna ");
	
	command_0_Valid(command_0_List, command_1_List, &player, board, &quitValid);
					
	if(quitValid == TRUE)
	{
		return;
	}
	else
	{
		command_2_Valid(command_2_List, board, &player);
		
		/* Display the moves of the player */
		if (player.moves > 0)
		{
			printf("\nWoohoo! Your total moves are: %d\n", player.moves);
		}
		else
		{
			printf("\nOops! Your total move is: %d\n", player.moves);
		}
	}
}

void command_0_Valid(char* list_0, char* list_1, Player* player, 
					Cell board[BOARD_HEIGHT][BOARD_WIDTH], Boolean* quitValid)
{
	Boolean commandValid = FALSE;
	char command[COMMAND_0_LENGTH + EXTRA_SPACES];
	
	do
	{
		command_Common_Valid(list_0, list_0, list_1, command, player, board, 
							&commandValid, quitValid, COMMAND_0_LENGTH);
		if(*quitValid == TRUE)
		{
			return;
		}
	}while(!commandValid);
}

void command_1_Valid(char* list_0, char* list_1, Player* player, 
					Cell board[BOARD_HEIGHT][BOARD_WIDTH], Boolean* quitValid)
{
	Boolean commandValid = FALSE;
	char command[COMMAND_1_LENGTH + EXTRA_SPACES];
	
	do
	{
		command_Common_Valid(list_1, list_0, list_1, command, player, board, 
							&commandValid, quitValid, COMMAND_1_LENGTH);
		if(*quitValid == TRUE)
		{
			return;
		}
	}while(!commandValid);
}

void command_Common_Valid(char* list, char* list_0, char* list_1, char* command, 
						Player* player,	Cell board[BOARD_HEIGHT][BOARD_WIDTH], 
						Boolean* commandValid, Boolean* quitValid, unsigned length)
{
	displayBoard(board, NULL);
	printf("%s", list);
	fgets(command, length + EXTRA_SPACES, stdin);
	
	/* Check if the input is too long */
	if(command[strlen(command) - NULL_SPACE] != '\n')
	{
		printf(INVALID_INPUT_MESSAGE);
		readRestOfLine();
	}
	else
	{
		command[strlen(command) - NULL_SPACE] = NULL_TERMINATED;
		
		/* Check if the input is load 1*/
		if (strcmp(command, COMMAND_LOAD_BOARD_1) == 0)
		{
			loadBoard(board, BOARD_1);
			
			/* Check if the console is of the sub menu */
			if (strcmp(list, list_0) == 0)
			{
				*commandValid = TRUE;
				command_1_Valid(list_0, list_1, player, board, quitValid);
			}
		}
		
		/* Check if the input is load 2*/
		else if (strcmp(command, COMMAND_LOAD_BOARD_2) == 0)
		{
			loadBoard(board, BOARD_2);
			
			/* Check if the console is of the sub menu */
			if (strcmp(list, list_0) == 0)
			{
				*commandValid = TRUE;
				command_1_Valid(list_0, list_1, player, board, quitValid);
			}
		}
		
		/* Check if the input is quit*/
		else if (strcmp(command, COMMAND_QUIT) == 0)
		{
			*quitValid = TRUE;
			return;
		}
		
		/* Check if the console is of the first level menu */
		else if (strcmp(list, list_1) == 0)
			{
				command_1_Component_Valid(command, commandValid, board, player);
			}
		else
		{
			printf(INVALID_INPUT_MESSAGE);
		}
	}
}

void command_1_Component_Valid(char* command, Boolean* commandValid,
								Cell board[BOARD_HEIGHT][BOARD_WIDTH],
								Player* player)
{
	int tempX = 0;
	int tempY = 0;
	char strCommand[COMMAND_1_INIT_LENGTH + NULL_SPACE];
	char strX[COMMAND_1_COORDINATE_LENGTH + NULL_SPACE];
	char strY[COMMAND_1_COORDINATE_LENGTH + NULL_SPACE];
	char strDirection_1[COMMAND_DIRECTION_LENGTH + NULL_SPACE];
	char strDirection_2[COMMAND_DIRECTION_LENGTH + NULL_SPACE];
	char* endPtr1;
	char* endPtr2;
	
	/* Use strncpy to copy the componets of init <x>,<y>,<direction> */
	strncpy(strCommand, command, COMMAND_1_INIT_LENGTH);
	strCommand[COMMAND_1_INIT_LENGTH] = NULL_TERMINATED;
	
	/* Copy <x> */
	strncpy(strX, command + (COMMAND_1_X), COMMAND_1_COORDINATE_LENGTH);
	strX[COMMAND_1_COORDINATE_LENGTH] = NULL_TERMINATED;
	
	/* Copy <y> */
	strncpy(strY, command + (COMMAND_1_Y), COMMAND_1_COORDINATE_LENGTH);
	strY[COMMAND_1_COORDINATE_LENGTH] = NULL_TERMINATED;
	
	/* Copy <direction> of length of 5 */
	strncpy(strDirection_1, command + COMMAND_1_DIRECTION, 
			COMMAND_DIRECTION_LENGTH);
	strDirection_1[COMMAND_DIRECTION_LENGTH] = NULL_TERMINATED;
	
	/* Copy <direction> of length of 4 */
	strncpy(strDirection_2, command + COMMAND_1_DIRECTION, 
			COMMAND_DIRECTION_LENGTH - NULL_SPACE);
	strDirection_2[COMMAND_DIRECTION_LENGTH - NULL_SPACE] = NULL_TERMINATED;
	
	/* Cast the copy of input <x> and <y> into integers */
	tempX = (int) strtol(strX, &endPtr1, 10);
	tempY = (int) strtol(strY, &endPtr2, 10);
	if (strcmp(endPtr1, EMPTY_STRING) != 0 || strcmp(endPtr2, EMPTY_STRING) != 0)
	{
		printf(INVALID_INPUT_MESSAGE);
	}
	
	/* Check the format */
	else if ((strcmp(strCommand, COMMAND_INIT) == 0) && 
			(command[COMMAND_1_X - COMMAND_SPACE_LENGTH] == COMMAND_SPACE) && 
			(command[COMMAND_1_Y - COMMAND_COMMA_LENGTH] == COMMAND_COMMA) && 
			(command[COMMAND_1_DIRECTION - COMMAND_COMMA_LENGTH] == COMMAND_COMMA))
		{
		command_1_Direction_Valid(strDirection_1, strDirection_2, tempX, tempY, 
								commandValid, strCommand, command, player, 
								board);
	}
	else
	{
		printf(INVALID_INPUT_MESSAGE);
	}
}

void command_1_Direction_Valid(char* strDirection_1, char* strDirection_2, 
							int tempX, int tempY, Boolean* commandValid, 
							char* strCommand, char* command, Player* player, 
							Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	
	char confirmDirection[COMMAND_DIRECTION_LENGTH + NULL_SPACE];
	
	/* Use strcpy to copy the input of <direction> to the same: confirmDirection */
	if (strDirection_1[COMMAND_DIRECTION_LENGTH - NULL_SPACE] == NULL_TERMINATED)
		{
			strcpy(confirmDirection, strDirection_2);
		}
		else
		{
			strcpy(confirmDirection, strDirection_1);
		}
		
		/* Check if the spelling of <direction> is valid */
		if ((strcmp(strDirection_1, DIRECTION_NORTH) == 0) ||
			(strcmp(strDirection_1, DIRECTION_SOUTH) == 0) ||
			(strcmp(strDirection_2, DIRECTION_WEST) == 0) ||
			(strcmp(strDirection_2, DIRECTION_EAST) == 0))
		{
			
			/* The input is valid, now player can be initialised */
			*commandValid = TRUE;
			player->position.x = tempX;
			player->position.y = tempY;
			playerDirecition(player, confirmDirection);
			initialisePlayer(player, &(player->position), player->direction);
			
			/* Check if the placement of the player is valid */
			if (placePlayer(board, player->position))
			{
				*commandValid = TRUE;
			}
			else
			{
				printf("\nUnable to place player at that position! "
						"Please try again.\n");
				*commandValid = FALSE;
			}
		}
		else
		{
			printf(INVALID_INPUT_MESSAGE);
		}
}

void playerDirecition(Player* player, char* strDirection)
{
	if (strcmp(strDirection, DIRECTION_NORTH) == 0)
	{
		player->direction = NORTH;
	}
	if (strcmp(strDirection, DIRECTION_SOUTH) == 0)
	{
		player->direction = SOUTH;
	}
	if (strcmp(strDirection, DIRECTION_WEST) == 0)
	{
		player->direction = WEST;
	}
	if (strcmp(strDirection, DIRECTION_EAST) == 0)
	{
		player->direction = EAST;
	}
}

void command_2_Valid(char* list, Cell board[BOARD_HEIGHT][BOARD_WIDTH], 
					Player* player)
{
	Boolean commandValid = FALSE;
	char command[COMMAND_2_LENGTH + EXTRA_SPACES];
	TurnDirection turningDirection;
	do
	{
		displayBoard(board, player);
		printf("%s", list);
		fgets(command, COMMAND_2_LENGTH + EXTRA_SPACES, stdin);
		
		/* Check if the input is too long */
		if(command[strlen(command) - NULL_SPACE] != '\n')
		{
			printf(INVALID_INPUT_MESSAGE);
			readRestOfLine();
		}
		else
		{
			command[strlen(command) - NULL_SPACE] = NULL_TERMINATED;
			
			/* Check if the input is forward or f */
			if ((strcmp(command, COMMAND_FORWARD) == 0) ||
				(strcmp(command, COMMAND_FORWARD_SHORTCUT) == 0))
			{
				/* Check if the player can move forward and display message*/
				switch(movePlayerForward(board, player))
				{
					case PLAYER_MOVED:
					printf("\nThe car moved forward! Well done. :)\n");
					break;
					case CELL_BLOCKED:
					printf("\nThe car is facing a block and cannot move forward"
						" in that direction!\nPlease try again.\n");
					break;
					case OUTSIDE_BOUNDS:
					printf("\nThe car is at the edge of the board and cannot "
						"move further in that direction!\nPlease try again.\n");
					break;
				}				
			}
			
			/* Check if the input is turn_left or l */
			else if ((strcmp(command, COMMAND_TURN_LEFT) == 0) ||
					(strcmp(command, COMMAND_TURN_LEFT_SHORTCUT) == 0))
			{
				turningDirection = TURN_LEFT;
				turnDirection(player, turningDirection);
				printf("\nThe car turned left! Well done. :)\n");
			}
			
			/* Check if the input is turn_right or r */
			else if ((strcmp(command, COMMAND_TURN_RIGHT) == 0) ||
					(strcmp(command, COMMAND_TURN_RIGHT_SHORTCUT) == 0))
			{
				turningDirection = TURN_RIGHT;	
				turnDirection(player, turningDirection);
				printf("\nThe car turned right! Well done. :)\n");				
			}
			
			/* Check if the input is quit */
			else if (strcmp(command, COMMAND_QUIT) == 0)
			{
				return;
			}
			else
			{
				printf(INVALID_INPUT_MESSAGE);
			}
		}
	}while(!commandValid);
}