#pragma warning(disable:4996) //ignore safety warnings

#ifndef UIH
#define UIH

#include <stdio.h>
#include <string.h>

// Defining user's options constants
#define CREATE_PROJ 0
#define LOAD_PROJ 1

#define EXIT 0
#define ADD_FRAME 1
#define REMOVE_FRAME 2
#define CHANGE_INDEX 3
#define CHANGE_FRAME_DURATION 4
#define CHANGE_ALL_DURATION 5
#define SHOW_FRAMES 6
#define PLAY_MOVIE 7
#define SAVE_PROJECT 8
#define REVERSE_MOVIE 9 // Bonus

#define MIN_OPT 0
#define MAX_OPT 8

#define NEW_LINE "\n"
#define NO_DUR 0

// -----------------------------------------------------------------------------------------------------------------------------

// Defining my User Interface functions
int projectOpChoice();
int menu();
void myFGets(char* string, int maxLength);

#endif 