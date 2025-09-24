/*********************************
* Magshimim Year 1 Final Project *
* Name:  Ido Redid               *
**********************************/

#include <stdio.h>
#include <stdlib.h>

#include "filesTests.h"
#include "projectFile.h"
#include "ui.h"
#include "linkedList.h"
#include "view.h"

int main()
{
	int projectOp = 0, choiceOp = 0, firstAdd = TRUE;
	char* frameName = NULL;

	FrameNode* currFrame = NULL;
	FrameNode* firstFrame = NULL;

	// User choose if to load a project or create a new one (Valid choice)
	projectOp = projectOpChoice();
	system("cls");

	if (projectOp)
	{
		firstFrame = loadFramesFromFile();

		// If project was loaded successfully then the first frame is our header of list throughout program
		if (firstFrame)
		{
			firstAdd = FALSE;
		}
	}
	
	do
	{
		// User choose which operation to perform (Validated choice)
		choiceOp = menu();
		system("cls");

		// Performing user's choice
		switch (choiceOp)
		{
			case EXIT:
				printf("Bye Bye!\n");
				break;

			case ADD_FRAME:
				addFrame(&firstFrame, currFrame, &firstAdd);
				break;

			case REMOVE_FRAME:
				printf("Enter the name of the frame you would like to erase\n");
				takeName(&frameName);
				removeFrame(&firstFrame, frameName);
				free(frameName);
				break;

			case CHANGE_INDEX:
				changeFrameLocation(&firstFrame);
				break;

			case CHANGE_FRAME_DURATION:
				changeDuration(firstFrame);
				break;

			case CHANGE_ALL_DURATION:
				changeAllDuration(firstFrame);
				break;

			case SHOW_FRAMES:
				printFrames(firstFrame);
				break;

			case PLAY_MOVIE:
				play(firstFrame);
				break;

			case SAVE_PROJECT:
				saveMovieProject(firstFrame);
				break;

			case REVERSE_MOVIE:
				reverseMovie(&firstFrame);
				break;

			default:
				printf("You should choose one of the options - (0 - 8)!\n");
		}

	} 
	while (choiceOp);

	// If we have an existing list of frames (At least 1 frame) we free all of them at the end of program
	if (firstFrame)
	{
		freeFrames(&firstFrame);
	}

	getchar();
	return EXIT_SUCCESS;
}
