#ifndef PROJECTFILEH
#define PROJECTFILEH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "filesTests.h"

#define SAVE_PROJ 0
#define LOAD_PROJ 1

#define LINE_SIZE 360
#define DELIMETER_SIZE 2
#define COMMA_DELIMETER ","

#define FRAME_PATH 0
#define FRAME_DUR 1
#define FRAME_NAME 2

// -------------------------------------------------------------------------------------------------
// Defining my project file functions

void parseFrameLine(char* currLine, const char* frameDelimeter, char** framePath, char** frameName, unsigned int* frameDuration);
FrameNode* loadHeadFrame(FILE* projectFile, const char* frameInfoDelimeter);
void loadFrame(FrameNode** firstFrame, char* currLine, const char* frameInfoDelimeter);
FrameNode* loadFramesFromFile();
void saveProjectToFile(FrameNode* firstFrame, char* filePath);
void saveMovieProject(FrameNode* firstFrame);

#endif