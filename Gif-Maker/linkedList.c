#include "linkedList.h"

/*
Function checks if a frame with certain name exists in the frames list
Input: The first frame node and the name we compare with
Output: The matching frame with the name or NULL if there is no matching frame
*/
FrameNode* searchFrame(FrameNode* firstFrame ,char* frameName)
{
	FrameNode* currNode = firstFrame;
	int foundFrame = FALSE;

	// Checking if there is a first frame (List is not empty)
	if (firstFrame)
	{
		// Making sure the name of the frame is not NULL before comparing it
		if (currNode->frame->name)
		{
			// Iterating through all frames of list
			while (currNode)
			{
				// If we have found an existing frame with the name we want to add we return it
				if (!(strcmp(currNode->frame->name, frameName)))
				{
					return currNode;
				}

				currNode = currNode->next;

			}
		}

	}

	// Otherwise we can add the frame with this name to the list
	return NULL;
}

/*
The function creates a new frame which we add to frames list
Input: None (Void)
Output: Initialized new frame node
*/
FrameNode* createFrame()
{
	// Allocating memory for the frame node structure fields (The next field and Frame field)
	FrameNode* currFrame = (FrameNode*)(malloc(sizeof(FrameNode)));
	// Allocating memory for the Frame structure
	currFrame->frame = (Frame*)(malloc(sizeof(Frame)));
	// Setting all frame fields to default (All are NULL and 0)
	currFrame->frame->name = NULL;
	currFrame->frame->duration = NO_DUR;
	currFrame->frame->path = NULL;
	currFrame->next = NULL;

	return currFrame;

}

/*
The function takes a name for dealing with frames
Input: Pointer to the name we enter
Output: None (Void)
*/
void takeName(char** name)
{
	// Allocating maximal length for name input
	*name = (char*)(malloc(sizeof(char) * MAX_LEN));
	myFGets(*name, MAX_LEN);
}

/*
The function takes frame name for the new added frame and validates it
Input: The first frame in the list and the new added frame
Output: None (Void)
*/
void validateFrameName(FrameNode* firstFrame, char** frameName)
{
	FrameNode* matchingFrame = NULL;

	// Keep asking for frame name until user enters valid frame name which is not already in list
	do
	{
		// Taking name and searching if a frame with this name exists in the list already
		printf("Please choose name for that frame:\n");
		takeName(frameName);
		matchingFrame = searchFrame(firstFrame, *frameName); 

		// Otherwise the name is taken and we want the user to enter another name
		if (matchingFrame)
		{
			printf("The name is already taken, please enter another name\n");
		}

	} 
	while (matchingFrame);

}

/*
The function takes from the user the current frame's duration and validates it
Input: None (Void)
Output: Valid duration for the frame
*/
unsigned int takeDuration()
{
	unsigned int frameDuration = NO_DUR;

	// Validating the frame duration is greater than 0
	do
	{
		scanf("%u", &frameDuration);
		getchar(); // Cleans buffer

		// If the frame duration is invalid we print to user error message
		if (frameDuration <= NO_DUR)
		{
			printf("Please choose valid duration...\n");
		}

	} 
	while (frameDuration <= NO_DUR);

	// Returning the validated frame duration
	return frameDuration;
}

/*
The function takes all inputs for the new frame (Name, Path and Duration) and fills the new frame with them
Input: The first frame of the list and the current added frame, also boolean pointer if the first add was made
Output: If the frame was filled or not and can be added
*/
int takeFrameInputs(FrameNode* firstFrame, FrameNode* newFrame, int* firstAdd)
{
	char* frameName = NULL;
	char* framePath = NULL;
	unsigned int frameDuration = NO_DUR;
	FrameNode* matchingFrame = NULL;
	int addFrame = TRUE;

	printf("Please insert frame path:\n");
	takeName(&framePath);

	// Checking if the file exists
	if (fileExists(framePath, READ_MODE))
	{
		// Checking for the file type (If it is either PNG, JPEG or JPG)
		if (isFileAnImage(framePath))
		{
			
			printf("Please insert frame duration (in miliseconds):\n");
			frameDuration = takeDuration();

			// If there is at least 1 frame already in the list we need to validate the name of the added next frames
			if (!*firstAdd)
			{
				validateFrameName(firstFrame, &frameName);
				fillFrame(newFrame, framePath, frameDuration, frameName);
				free(framePath);
				free(frameName);
			}

			// Otherwise if the list is empty (There is no first frame) we don't need to validate the name
			// and we can just fill the frame with the information
			else
			{
				printf("Please choose name for that frame:\n");
				takeName(&frameName);
				fillFrame(firstFrame, framePath, frameDuration, frameName);

				// Freeing the containers of the frame information strings (name and path)
				free(framePath);
				free(frameName);
			}

		}

		else
		{
			printf("File is not an image! Frame will not be added\n\n");
			free(framePath);
			addFrame = FALSE;
		}

	}

	else
	{
		printf("Can't find file! Frame will not be added\n\n");
		free(framePath);
		addFrame = FALSE;
	}

	return addFrame;
}

/*
The function fills the new added frame with valid data from user
Input: The first frame of the list and the new added frame
Output: None (Void)
*/
void fillFrame(FrameNode* newFrame, char* framePath, unsigned int frameDuration, char* frameName)
{
	// Allocating memory for both frame and name of the strings
	newFrame->frame->path = (char*)(malloc(sizeof(char) * (strlen(framePath) + 1)));
	newFrame->frame->name = (char*)(malloc(sizeof(char) * (strlen(framePath) + 1)));

	// Filling the current new frame with the validated taken inputs from the user
	strcpy(newFrame->frame->path, framePath);
	strcpy(newFrame->frame->name, frameName);
	newFrame->frame->duration = frameDuration;

}

/*
The function adds a new frame to the end of the list of frames
Input: Pointer to the first frame node of list and the new frame we insert at the end of the list
Output: None (Void)
*/
void insertFrame(FrameNode** firstFrame, FrameNode* newFrame)
{
	// if the new frame is the first frame of list
	if (!*firstFrame)
	{
		*firstFrame = newFrame;
	}

	else if (newFrame) // If new frame is accepted
	{
		FrameNode* currFrame = *firstFrame;

		// Finding the last frame of the list
		while (currFrame->next)
		{
			currFrame = currFrame->next;
		}

		// Linking to it the new frame
		currFrame->next = newFrame;
	}
}

/*
The function creates and inserts the new frame to the list
Input: The pointer to the first frame in the list, the new added frame (After head) and pointer if the 
first frame of the list (head) was added or not
Output: None (Void)
*/
void addFrame(FrameNode** firstFrame, FrameNode* currFrame, int* firstAdd)
{
	int frameAdded = TRUE;
	char* frameName = NULL;
	char* framePath = NULL;
	unsigned int frameDuration = NO_DUR;

	// If this is the first call to the function the frame we add is declared as head of list
	if (*firstAdd)
	{
		printf("*** Creating new frame ***\n");
		*firstFrame = createFrame();
		frameAdded = takeFrameInputs(*firstFrame, *firstFrame, firstAdd);
		*firstAdd = FALSE; // First add was made, next frames' names must be checked!
	}

	else
	{
		// Otherwise we create a frame and insert it after the last frame in the list
		printf("*** Creating new frame ***\n");
		currFrame = createFrame();
		frameAdded = takeFrameInputs(*firstFrame, currFrame, firstAdd);

		if (frameAdded)
		{
			insertFrame(firstFrame, currFrame);
		}
	}
}

/*
The function changes duration for a frame
Input: The first frame in the list
Output: None (Void)
*/
void changeDuration(FrameNode* firstFrame)
{
	char* searchName = NULL;
	unsigned int newDuration = 0;
	FrameNode* changedFrame = NULL;

	printf("Enter the name of the frame:\n");
	takeName(&searchName);

	// Searching for the frame with the matching name which we change it's duration
	changedFrame = searchFrame(firstFrame, searchName);

	if (changedFrame)
	{
		// Taking the new duration (Validated) and changing the frame's duration
		printf("Enter the new duration:\n");
		newDuration = takeDuration();

		changedFrame->frame->duration = newDuration;
	}
	
	// If we've iterated through all frames and reached to NULL the frame name doesn't exist
	// In our frames list
	else
	{
		printf("The frame does not exist...\n");
	}

	// Freeing unecessary allocated memory which is used for input only!
	free(searchName);
}

/*
The function changes the duration of all frames in list to one the user chose
Input: The first frame in the list
Output: None (Void)
*/
void changeAllDuration(FrameNode* firstFrame)
{
	unsigned int newDuration = 0;
	FrameNode* currFrame = firstFrame;

	// Taking the new duration (Validated)
	printf("Enter new duration:\n");
	newDuration = takeDuration();

	// If the list is not empty
	if (currFrame)
	{
		// Iterating through each frame and changing it's duration until we reach to end of list
		while (currFrame)
		{
			currFrame->frame->duration = newDuration;
			currFrame = currFrame->next;
		}

	}	

}

/*
The function removes the required frame which is in middle of list or the last frame in list
Input: Pointer to the first frame of list and pointer to the name of the frame we want to remove
Output: If the frame was removed successfully or not (True/False)
*/
int removeFromMid(FrameNode** firstFrame, char** frameName)
{
	FrameNode* pFrame = *firstFrame;
	FrameNode* dFrame = NULL;

	int removedFrame = FALSE;

	// Finding the frame before the one we want to remove
	while ((pFrame->next) && (strcmp(pFrame->next->frame->name, *frameName)))
	{
		pFrame = pFrame->next;
	}

	// Making sure we've not reached to last node
	if (pFrame->next)
	{
		// Removing the node and frees it's allocated memory
		dFrame = pFrame->next;
		pFrame->next = dFrame->next;
		freeFrame(dFrame);

		removedFrame = TRUE;

	}

	return removedFrame;
}

/*
The function removes a frame from the list by name chosen by the user
Input: Pointer to the first frame in the list
Output: None (Void)
*/
void removeFrame(FrameNode** firstFrame, char* frameName)
{
	FrameNode* pFrame = *firstFrame;
	FrameNode* dFrame = NULL;
	int removedFrame = FALSE;

	// Making sure the list is not empty
	if (*firstFrame)
	{
		// Checking if the desired frame to remove is the first frame
		if (!(strcmp(pFrame->frame->name, frameName)))
		{
			// If so, removing the first frame
			*firstFrame = pFrame->next;
			freeFrame(pFrame);

			removedFrame = TRUE;

		}

		// Otherwise the frame is in the middle or end of list and we remove it from there
		else
		{
			removedFrame = removeFromMid(firstFrame, &frameName);
		}
	}

	// If we couldn't remove frame meaning the frame was not found!
	if (!removedFrame)
	{
		printf("The frame was not found\n");
	}

}

/*
The function counts how many frames are in the list
Input: The first frame of list
Output: Amount of frames in list
*/
int countFrames(FrameNode* firstFrame)
{
	int framesAmount = 0;
	FrameNode* currFrame = firstFrame;

	// Making sure the list is not empty
	if (firstFrame)
	{
		// Counting the amount of frames in list
		while (currFrame)
		{
			framesAmount++;
			currFrame = currFrame->next;
		}
	}

	return framesAmount;
}

/*
The function takes the new location of the desired frame and validates it
Input: The amount of frames in list (Maximal location number)
Output: The desired location validated
*/
int takeLocation(int maxLocation)
{
	int newLocation = 0;

	// Taking the location and making sure it is valid
	do
	{
		printf("Enter the new index in the movie you wish to place the frame\n");
		scanf("%d", &newLocation);
		getchar(); // Cleans buffer

		// If the location is not greater than 1 or the location is greater than the amount of frames
		// It is invalid location!
		if (newLocation < MIN_LOCATION || newLocation > maxLocation)
		{
			printf("The movie contains only %d frames!\n", maxLocation);
		}
	} 
	while (newLocation < MIN_LOCATION || newLocation > maxLocation);

	return newLocation;

}

/*
The function saves to a new unlinked frame the details of the frame we move
Input: Pointer to the unlinked copied frame and the moved frame itself
Output: None (Void)
*/
void saveMovedFrame(FrameNode** copiedFrame, FrameNode* movedFrame)
{
	// Allocating memory for all fields and information of the moved frame itself and
	// it's strings fields (Name and Path)
	*copiedFrame = (FrameNode*)(malloc(sizeof(FrameNode)));
	(*copiedFrame)->frame = (Frame*)(malloc(sizeof(Frame)));
	(*copiedFrame)->frame->name = (char*)(malloc(sizeof(char) * (strlen(movedFrame->frame->name) + 1)));
	(*copiedFrame)->frame->path = (char*)(malloc(sizeof(char) * (strlen(movedFrame->frame->path) + 1)));

	// Copying the fields into the copied frame (The name and path) and then saving also the duration
	// Setting next to be NULL (Default)
	strcpy((*copiedFrame)->frame->name, movedFrame->frame->name);
	strcpy((*copiedFrame)->frame->path, movedFrame->frame->path);
	(*copiedFrame)->frame->duration = movedFrame->frame->duration;
	(*copiedFrame)->next = NULL;
}

/*
The function changes the location of a frame
Input: First frame of the list
Output: None (Void)
*/
void changeFrameLocation(FrameNode** firstFrame)
{
	int maxFrameNum = countFrames(*firstFrame);
	int newLocation = 0, currentIndex = 1;
	char* movedFrameName = NULL;

	FrameNode* currFrame = NULL;
	FrameNode* movedFrame = NULL;
	FrameNode* movedFrameCopy = NULL;

	// Finding the frame we want to move
	printf("Enter frame name to move:\n");
	takeName(&movedFrameName);
	movedFrame = searchFrame(*firstFrame, movedFrameName);

	// If the frame with this name exists and was found
	if (movedFrame)
	{
		// Saving the frame to a copy (Without the next field)
		saveMovedFrame(&movedFrameCopy, movedFrame);

		// Removing the frame from the list
		removeFrame(firstFrame, movedFrameName);

		currFrame = *firstFrame;

		// Taking the new index of the frame
		newLocation = takeLocation(maxFrameNum);

		// If the new index is the first index we just add the frame
		if (newLocation == FIRST_INDEX)
		{
			movedFrameCopy->next = *firstFrame;
			*firstFrame = movedFrameCopy;
		}

		else
		{
			// Finding the frame with the matching index (Which we move the frame to)
			for (currentIndex = 1; (currentIndex < newLocation - 1) && (currFrame); currentIndex++)
			{
				currFrame = currFrame->next;
			}

			// Inserting the frame at the matching index (Which is not 1)
			movedFrameCopy->next = currFrame->next;
			currFrame->next = movedFrameCopy;
		}

	}
	
	else
	{
		printf("Frame does not exist...\n");
	}

	// Freeing unecessary allocated memory for input!
	free(movedFrameName);
}

/*
The function prints the frames nodes of the edited list
Input: The first frame in the list
Output: None (Void)
*/
void printFrames(FrameNode* firstFrame)
{
	FrameNode* currNode = firstFrame;

	printf("Name\t\tDuration\t\tPath\n");
	// If the list is not empty
	if (firstFrame)
	{
		// Printing all the frames in list and their details
		while (currNode)
		{
			printf("%s\t\t%u ms\t\t%s\n", currNode->frame->name, currNode->frame->duration, currNode->frame->path);
			currNode = currNode->next;
		}
	}

	printf("\n");
}

/*
The function reverses the movie frames (Bonus)
Input: Pointer to the first frame of the list
Output: None (Void)
*/
void reverseMovie(FrameNode** firstFrame)
{
	FrameNode* currFrame = *firstFrame;
	FrameNode* previousFrame = NULL;
	FrameNode* nextFrame = NULL;

	printf("Movie reversed!\n");

	// Making sure the frames list is not empty
	if (*firstFrame)
	{
		// Iterating through each frame
		while (currFrame)
		{
			// Reversing every frame (Saving the next frame)
			// And then declaring the next of the current frame as it's previous frame until we reach to end
			nextFrame = currFrame->next;
			currFrame->next = previousFrame;
			previousFrame = currFrame;
			currFrame = nextFrame;
		}

		// Setting the last frame of the list as the first frame
		*firstFrame = previousFrame;
	}
}

/*
The function will free desired frame's memory from list which user chose to remove
Input: The frame with the name the user chose
Output: None (Void)
*/
void freeFrame(FrameNode* frame)
{
	// Freeing all allocated memory for the single frame (Name, path, frame and frameNode)
	free(frame->frame->name);
	free(frame->frame->path);
	free(frame->frame);
	free(frame);
}

/*
Function frees all allocated memory for the frames in the list
Input: Pointer to the first frame of the list
Output: None (Void)
*/
void freeFrames(FrameNode** firstFrame)
{
	FrameNode* currFrame = *firstFrame;
	FrameNode* tempFrame = NULL;

	// Freeing all frames in the list
	while (currFrame)
	{
		// Saving next frame
		tempFrame = currFrame->next;

		// Freeing the current frame
		freeFrame(currFrame);
		currFrame = tempFrame;

	}

	// Setting the first frame pointer to NULL
	*firstFrame = NULL;
}
