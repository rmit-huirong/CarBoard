
/**
 * Author: Huirong Huang
 * Student ID: s3615907
 * Email: s3615907@student.rmit.edu.au
 */

#ifndef CARBOARD_H
#define CARBOARD_H

#include "helpers.h"
#include "game.h"

/* Length of a valid menu option is 1, and set the length of the menu list to 120 */
#define INPUT_LENGTH 1
#define TEMP_LENGTH 1
#define MENU_LENGTH 120

/* Valid menu option is from 1 to 3 */
#define MIN 1
#define MAX 3

#define OPTION_1 1
#define OPTION_2 2
#define OPTION_3 3

/* Student's information */
#define STUDENT_NAME "Huirong Huang"
#define STUDENT_ID "s3615907"
#define STUDENT_EMAIL "s3615907@student.rmit.edu.au"

/* Check the validation of the input in the main menu */
void inputValid(char*, int*, unsigned);

/* Different Options lead to different results */
void menuOption(int);

/* To show student's information */
void showStudentInformation();

#endif
