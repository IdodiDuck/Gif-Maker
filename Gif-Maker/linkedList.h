#ifndef LINKEDLISTH
#define LINKEDLISTH

#include "ui.h"
#include "filesTests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linked list constants
#define FALSE 0
#define TRUE !FALSE

#define NO_DUR 0
#define MIN_DUR 0
#define MAX_LEN 150
#define MIN_LOCATION 1
#define FIRST_INDEX 1

// -----------------------------------------------------------------------------------------------------------------------------

// Frame struct
typedef struct Frame
{
	char* name;
	unsigned int duration;
	char* path;  
} Frame;


// Link (node) struct
typedef struct FrameNode
{
	Frame* frame;
	struct FrameNode* next;
} FrameNode;

// --------------------------------------------------------------------------------------------------------------------------

// Defining my linked list functions
FrameNode* searchFrame(FrameNode* firstFrame, char* frameName);
FrameNode* createFrame();
int takeFrameInputs(FrameNode* firstFrame, FrameNode* newFrame, int* firstAdd);
void fillFrame(FrameNode* newFrame, char* framePath, unsigned int frameDuration, char* frameName);
void insertFrame(FrameNode** firstFrame, FrameNode* newFrame);
void addFrame(FrameNode** firstFrame, FrameNode* currFrame, int* firstAdd);
void takeName(char** name);
void validateFrameName(FrameNode* firstFrame, char** frameName);
unsigned int takeDuration();
int removeFromMid(FrameNode** firstFrame, char** frameName);
void removeFrame(FrameNode** firstFrame, char* frameName);
int countFrames(FrameNode* firstFrame);
int takeLocation(int maxLocation);
void saveMovedFrame(FrameNode** copiedFrame, FrameNode* movedFrame);
void changeFrameLocation(FrameNode** firstFrame);
void changeDuration(FrameNode* firstFrame);
void changeAllDuration(FrameNode* firstFrame);
void printFrames(FrameNode* firstFrame);
void reverseMovie(FrameNode** firstFrame);
void freeFrame(FrameNode* frame);
void freeFrames(FrameNode** firstFrame);

#endif