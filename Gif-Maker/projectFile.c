#include "projectFile.h"

/*
The function appends to the file the current frame's information
Input: The path of the file where we save our project and the first frame of the list
Output: None (Void)
*/
void saveProjectToFile(FrameNode* firstFrame, char* filePath)
{
	FrameNode* currFrame = firstFrame;
	FILE* savedFile = fopen(filePath, WRITE_MODE); // No need to validate opening, already done before

	// Writing each frame to the file until we finish all frames
	while (currFrame)
	{
		fprintf(savedFile, "%s,%u,%s\n", currFrame->frame->path, currFrame->frame->duration, currFrame->frame->name);
		currFrame = currFrame->next;
	}

	fclose(savedFile);
}

/*
The function saves our current project to a text file
Input: The path to the text file where we save our frames information
Output: None (Void)
*/
void saveMovieProject(FrameNode* firstFrame)
{
	char* filePath = NULL;
	FrameNode* currFrame = firstFrame;
	FILE* savedFile = NULL;

	// Taking from user a path to a txt file where we would save our frames
	printf("Where to save the project? enter a full path and file name\n");
	takeName(&filePath);

	// Making sure this is a text file (With .txt suffix)
	if (validateFile(filePath, WRITE_MODE, SAVE_PROJ))
	{
		saveProjectToFile(firstFrame, filePath);
		printf("Saved successfully project to file at path: %s\n", filePath);
	}

	free(filePath);
}

/*
The function parses the current line to the different frame fields
Input: The current line, the seperator (comma), pointers to all frame fields (Path, name and duration)
Output: None (Void)
*/
void parseFrameLine(char* currLine, const char* frameDelimeter, char** framePath, char** frameName, unsigned int* frameDuration)
{
	int counter = 0;
	char* token = strtok(currLine, frameDelimeter);
	// Iterating through each field of the current frame (Current file line)
	while (token)
	{

		switch (counter)
		{
			case FRAME_PATH:
				// Allocating memory for the path of the current frame and then saving the path
				*framePath = (char*)(malloc(sizeof(char) * (strlen(token) + 1)));
				strcpy(*framePath, token);
				break;

			case FRAME_DUR:
				// Saving the duration of the current frame duration (String -> Int -> Unsigned int)
				*frameDuration = (unsigned int)(atoi(token));
				break;

			case FRAME_NAME:
				// Allocating memory for the name of the current frame and then saving the name
				*frameName = (char*)(malloc(sizeof(char) * (strlen(token) + 1)));
				strcpy(*frameName, token);
				break;
		}

		// Moving on to next field
		token = strtok(NULL, frameDelimeter);
		counter++;
	}
}

/*
The function saves the current scanned line from the file (After head) as a frame and inserts it to end of frames list
Input: Pointer to the first frame of list, the current line and the seperator of each frame field (,)
Output: None (Void)
*/
void loadFrame(FrameNode** firstFrame, char* currLine, const char* frameInfoDelimeter)
{
	FrameNode* currFrame = createFrame();

	char* frameName = NULL;
	char* framePath = NULL;
	unsigned int frameDuration = NO_DUR;
	char* token = NULL;
	int counter = 0;

	// Removing the \n of each frame line
	currLine[strcspn(currLine, NEW_LINE)] = NULL;
	
	// Extracting from the file the current frame fields information (Path, Name and Duration)
	parseFrameLine(currLine, frameInfoDelimeter, &framePath, &frameName, &frameDuration);
	fillFrame(currFrame, framePath, frameDuration, frameName);

	// Freeing the containers of the name and path after filled frame with them (We don't need them anymore)
	free(framePath);
	free(frameName);

	insertFrame(firstFrame, currFrame);
}

/*
The function saves the the first frame of the file as a list head
Input: The opened file which we read from and the seperator of frame fields (,)
Output: The first frame of the list
*/
FrameNode* loadHeadFrame(FILE* projectFile, const char* frameInfoDelimeter)
{
	FrameNode* firstFrame = NULL;
	int counter = 0;
	char* token = NULL;
	char* currLine = NULL;

	char* framePath = NULL;
	char* frameName = NULL;
	unsigned int frameDuration = NO_DUR;

	// Allocating memory for the first frame (First line)
	currLine = (char*)(malloc(sizeof(char) * LINE_SIZE));
	fgets(currLine, LINE_SIZE, projectFile);
	currLine[strcspn(currLine, NEW_LINE)] = NULL;

	// Creating the first frame, Extracting the frame fields and filling the first frame with them
	firstFrame = createFrame();
	parseFrameLine(currLine, frameInfoDelimeter, &framePath, &frameName, &frameDuration);
	fillFrame(firstFrame, framePath, frameDuration, frameName);

	// Freeing the memory allocated for first frame line and also the containers of the name and the path
	free(currLine);
	free(framePath);
	free(frameName);

	return firstFrame;
}

/*
The function loads from the text saved file frames into the linked list
Input: The path to the file where the frames informations are
Output: The first frame of the frames list
*/
FrameNode* loadFramesFromFile()
{
	FrameNode* firstFrame = NULL;
	FILE* projectFile = NULL;

	char* filePath = NULL;
	int counter = 0;

	char* currLine = NULL;
	const char frameInfoDelimeter[DELIMETER_SIZE] = COMMA_DELIMETER;

	printf("Enter the path of the project (including project name):\n");
	takeName(&filePath);

	// Making sure the file is valid
	if (validateFile(filePath, READ_MODE, LOAD_PROJ))
	{
		// Opening the file and extracting the first frame of list
		projectFile = fopen(filePath, READ_MODE);
		free(filePath); // Freeing file path after opening the file (We don't need it anymore)
		firstFrame = loadHeadFrame(projectFile, frameInfoDelimeter);
		
		// Allocating memory for each left frame of list (Each left line of file)
		currLine = (char*)(malloc(sizeof(char) * LINE_SIZE));
		counter = 0;
		
		// Iterating through all next frames (After the first frame) and saving them to list
		while (fgets(currLine, LINE_SIZE, projectFile) != NULL)
		{
			loadFrame(&firstFrame, currLine, frameInfoDelimeter);
		}
			
		fclose(projectFile);
	}
		
	else
	{
		printf("Error! - cant open file, creating a new project\n");
		return NULL; // First frame is NULL because we could not load the project file
	}

	return firstFrame;
}
