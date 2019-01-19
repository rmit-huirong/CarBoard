
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */

#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "player.h"

#define COMMAND_LOAD_BOARD_1 "load 1"
#define COMMAND_LOAD_BOARD_2 "load 2"
#define COMMAND_LOAD "load"
#define COMMAND_INIT "init"
#define COMMAND_FORWARD "forward"
#define COMMAND_FORWARD_SHORTCUT "f"
#define COMMAND_TURN_LEFT "turn_left"
#define COMMAND_TURN_LEFT_SHORTCUT "l"
#define COMMAND_TURN_RIGHT "turn_right"
#define COMMAND_TURN_RIGHT_SHORTCUT "r"
#define COMMAND_QUIT "quit"

#define COMMAND_SPACE ' '
#define COMMAND_COMMA ','

#define DIRECTION_NORTH "north"
#define DIRECTION_EAST "east"
#define DIRECTION_SOUTH "south"
#define DIRECTION_WEST "west"

/**
 * I don't want to waste the memory, so I set the length of anykey to 1.
 * Maximum length of command 0 is 6, i.e. "load 1".
 * Maximum length of command 1 is 14, i.e. "init 0,0,north".
 * Maximum length of command 2 is 10, i.e. "turn_right".
 * Set the lengths of components of command as follows.
 * Set the lengths of menu list as follows to avoid segmentation fault.
 */
#define ANYKEY_LENGTH 1
#define COMMAND_0_LENGTH 6
#define COMMAND_1_LENGTH 14
#define COMMAND_2_LENGTH 10
#define COMMAND_1_INIT_LENGTH 4
#define COMMAND_SPACE_LENGTH 1
#define COMMAND_COMMA_LENGTH 1
#define COMMAND_1_COORDINATE_LENGTH 1
#define COMMAND_DIRECTION_LENGTH 5
#define COMMAND_0_LIST_LENGTH 150
#define COMMAND_1_LIST_LENGTH 175
#define COMMAND_2_LIST_LENGTH 200

/* The index of <x> is 5, the index of <y> is 7, the index of <direction> is 9 */

#define COMMAND_1_X 5
#define COMMAND_1_Y 7
#define COMMAND_1_DIRECTION 9

/**
 * Main menu option 1 - play the game as per the specification.
 *
 * This function makes all the calls to board & player and handles interaction
 * with the user (reading input from the console, error checking, etc...).
 *
 * It should be possible to break this function down into smaller functions -
 * but this is up to you to decide and is entirely your own design. You can
 * place the additional functions in this header file if you want.
 *
 * Note that if you don't break this function up it could become pretty big...
 */
 
 /**
 * Before the game starts, a board and a player need to be declared.
 * After initialise the board which is empty, you can load either board 1 or 2.
 * A valid input for initialisation will initialise a player successfully.
 * Use a Boolean enumeration quitValid to decide when to exit the loop.
 */
void playGame();

/**
 * Check the validation of the input in the sub menu, including load <g>, quit.
 * Use a Boolean enumeration commandValid to decide when to exit the loop.
 */
void command_0_Valid(char*, char*, Player*, 
					Cell board[BOARD_HEIGHT][BOARD_WIDTH], Boolean*);
		
/**
 * Check the validation of the input in the first level menu, including load <g>, quit.
 * Use a Boolean enumeration commandValid to decide when to exit the loop.
 * The command of init <x>,<y>,<direction> will be checked later.
 */		
void command_1_Valid(char*, char*, Player*, Cell board[BOARD_HEIGHT][BOARD_WIDTH], 
					Boolean*);

/**
 * Check the validation of the input in the sub menu or the first level menu due
 * to the common commands they both contain: load <g>, quit.
 */
void command_Common_Valid(char*, char*, char*, char*, Player*,	
						Cell board[BOARD_HEIGHT][BOARD_WIDTH], Boolean*, Boolean*,
						unsigned);

/**
 * Check the validation of init <x>,<y>,<direction> on diffrent components.
 * Check <x>,<y> first, then check the format of init <x>,<y>,<direction>.
 */						
void command_1_Component_Valid(char*, Boolean*, 
								Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player*);

/**
 * Check the spelling of <direction> in the command of init <x>,<y>,<direction>.
 * Given two different lengths of <direction>, I check it seperated.
 * If validation is good, it is time to initialise the player we declared above.
 * A valid command will initialise a player successfully.
 */							
void command_1_Direction_Valid(char*, char*, int, int, Boolean*, char*, char*,
								Player*,Cell board[BOARD_HEIGHT][BOARD_WIDTH]);

/* To link the valid input <direction> to enumeration Direction */								
void playerDirecition(Player*, char*);

/**
 * Check the validation of the input in the second level menu, including 
 * forward (f), turn_left (l), turn_right (r), quit.
 * Make forward be interchangeable with f, turn_left be interchangeable with l,
 * turn_right be interchangeable with r. If the command is valid, then follow it.
 * Use a Boolean enumeration commandValid to decide when to exit the loop.
 */
void command_2_Valid(char*, Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player*);


#endif
