
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */

 #include "board.h"
 
Cell BOARD_1[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

Cell BOARD_2[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

void initialiseBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int x, y;
	for (x = 0; x < BOARD_HEIGHT; ++x)
	{
		for (y = 0; y < BOARD_WIDTH; ++y)
		{
			
			/* Initial board must be empty */
			board[x][y] = EMPTY;
		}
	}
}

void loadBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
               Cell boardToLoad[BOARD_HEIGHT][BOARD_WIDTH])
{
    /* Use memcpy to copy the memory from boardToLoad to board */
	memcpy(board,boardToLoad,sizeof(Cell)*BOARD_HEIGHT*BOARD_WIDTH);
}

Boolean placePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Position position)
{
	
	/* Check if the coordinates of the player are out of boundary */
	if ((position.x >= MIN_COORDINATE) && position.x <= MAX_COORDINATE && 
		position.y >= MIN_COORDINATE && position.y <= MAX_COORDINATE)
	{
		/* Check if the cell to place the player is blocked */
		if (board[position.y][position.x] != BLOCKED)
		{
			board[position.y][position.x] = PLAYER;
			/* Check if the player has been successfully placed in the cell */
			if (board[position.y][position.x] == PLAYER)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

PlayerMove movePlayerForward(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
                             Player * player)
{
	Position position;
	position.x = getNextForwardPosition(player).x;
	position.y = getNextForwardPosition(player).y;
	
	/* Check if the player moved out of boundary */
	if (position.x > MAX_COORDINATE || position.x < MIN_COORDINATE ||
		position.y > MAX_COORDINATE || position.y < MIN_COORDINATE)
	{
		return OUTSIDE_BOUNDS;	
	}
	
	/* Check if the player moved into a block */
	else if (board[position.y][position.x] == BLOCKED)
	{
		return CELL_BLOCKED;
	}
	else
	{
		/* Empty the former cell and then move the player to the next one */
		board[player->position.y][player->position.x] = EMPTY;
		updatePosition(player, position);
		board[player->position.y][player->position.x] = PLAYER;
	}
	return PLAYER_MOVED;
}

void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
	
	/* Use y to imply x index of the board, x to imply y index of the board */
	int y, x;
	for (y = 0; y < BOARD_HEIGHT + 1; ++y)
	{
		for (x = 0; x < BOARD_WIDTH + 1; ++x)
		{
			if ((y == 0) && (x == 0))
			{
				printf("\n%s", CARBOARD_BORDER);
				printf(EMPTY_OUTPUT);
			}
			
			/* Display the y index of the board */
			else if (y == 0)
			{
				printf("%s%d", CARBOARD_BORDER, x - 1);
			}
			
			/* Display the x index of the board */
			else if (x == 0)
			{
				printf("%s%d", CARBOARD_BORDER, y - 1);
			}
			else
			{
				/* Check if the cell is empty, blocked or placed by a player */
				switch(board[y - 1][x - 1])
				{
					case EMPTY:
					printf(CARBOARD_BORDER);
					printf(EMPTY_OUTPUT);
					break;
					case BLOCKED:
					printf(CARBOARD_BORDER);
					printf(BLOCKED_OUTPUT);
					break;
					case PLAYER:
					displayDirection(player->direction);
					break;
				}	
			}
		}
		printf("%s\n", CARBOARD_BORDER);
	}
}