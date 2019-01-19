
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */

#include "player.h"

void initialisePlayer(Player * player, Position * position, Direction direction)
{
	player->moves = 0;
	player->position = *position;
	player->direction = direction;
}

void turnDirection(Player * player, TurnDirection turnDirection)
{
	switch(turnDirection)
	{
		case TURN_LEFT:
		switch(player->direction)
		{
			case NORTH:
			player->direction = WEST;
			break;
			case SOUTH:
			player->direction = EAST;
			break;
			case WEST:
			player->direction = SOUTH;
			break;
			case EAST:
			player->direction = NORTH;
			break;
		}
		break;
		case TURN_RIGHT:
		switch(player->direction)
		{
			case NORTH:
			player->direction = EAST;
			break;
			case SOUTH:
			player->direction = WEST;
			break;
			case WEST:
			player->direction = NORTH;
			break;
			case EAST:
			player->direction = SOUTH;
			break;
		}
		break;
	}
}

Position getNextForwardPosition(const Player * player)
{
    Position position;
	position.x = player->position.x;
	position.y = player->position.y;
	
	switch(player->direction)
	{
		case NORTH:
		--position.y;
		break;
		case SOUTH:
		++position.y;
		break;
		case WEST:
		--position.x;
		break;
		case EAST:
		++position.x;
		break;
	}
	
    return position;
}

void updatePosition(Player * player, Position position)
{
	player->position.x = position.x;
	player->position.y = position.y;
	++player->moves;
}

void displayDirection(Direction direction)
{
	switch(direction)
	{
		case NORTH:
		printf(CARBOARD_BORDER);
		printf(DIRECTION_ARROW_OUTPUT_NORTH);
		break;
		case SOUTH:
		printf(CARBOARD_BORDER);
		printf(DIRECTION_ARROW_OUTPUT_SOUTH);
		break;
		case WEST:
		printf(CARBOARD_BORDER);
		printf(DIRECTION_ARROW_OUTPUT_WEST);
		break;
		case EAST:
		printf(CARBOARD_BORDER);
		printf(DIRECTION_ARROW_OUTPUT_EAST);
		break;
	}
}
