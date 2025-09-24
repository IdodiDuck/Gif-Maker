#define _CRT_SECURE_NO_WARNINGS

#ifndef FILESTESTS
#define FILESTESTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

// Defining my files tests constants
#define FALSE 0
#define TRUE !FALSE
#define READ_MODE "r"
#define WRITE_MODE "w"

#define TYPE_DOT '.'
#define PNG_TYPE ".png"
#define JPEG_TYPE ".jpeg"
#define JPG_TYPE ".jpg"
#define TXT_TYPE ".txt"

#define MATCH 0
#define MIN_FILE_LEN 6

// --------------------------------------------------------------------------------------------------------------------------
// Defining my files tests functions

int validateFile(char* filePath, char* mode, int projectOp);
int fileExists(char* filePath, char* mode);
int isFileAnImage(char* filePath);
int isFileATextFile(char* filePath);

#endif