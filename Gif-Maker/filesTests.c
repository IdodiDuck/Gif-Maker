#include "filesTests.h"

/*
The function checks if a is an image and
Input: The path to the file
Output: If the file is an image (True/False)
*/
int isFileAnImage(char* filePath)
{
	char* last = strrchr(filePath, TYPE_DOT);

	// Checking if the file's type is PNG, JPG or JPEG
	// File type is right after the last . in the path
	if (last)
	{
		if (strcmp(last, PNG_TYPE) == MATCH || strcmp(last, JPG_TYPE) == MATCH || strcmp(last, JPEG_TYPE) == MATCH)
		{
			return TRUE;
		}
	}

	return FALSE;
}

/*
The function checks if a file is openable/exists or not
Input: The path to the file
Output: If the file exists and openable or not (True/False)
*/
int fileExists(char* filePath, char* mode)
{
	FILE* checkedFile = fopen(filePath, mode);

	// Checking if file is openable for read (Path exists)
	if (checkedFile)
	{
		fclose(checkedFile);
		return TRUE;
	}

	return FALSE;
}

/*
The function checks if a the path to the file is a text file path
Input: The path to the file where we want to save our frames information
Output: Is the file type txt or not (True/False)
*/
int isFileATextFile(char* filePath)
{
	char* last = strrchr(filePath, TYPE_DOT);

	if (last)
	{
		if (strcmp(last, TXT_TYPE) == MATCH)
		{
			return TRUE;
		}

	}

	return FALSE;
}

/*
The function validates a file if it can be opened and used
Input: The path to the file and the mode we open the file with and which operation we perform (Save or Load)
Output: Is the file valid for usage or not (True/False)
*/
int validateFile(char* filePath, char* mode, int projectOp)
{
	FILE* file = NULL;
	int fileLength = 0;
	int isValid = FALSE;

	// Making sure the path to the file is for a text file
	if (isFileATextFile(filePath))
	{
		// If we wanted to load a project (projectOp = 1) we need to check the file content's length
		// Making sure there are at minimal characters for at least 1 frame
		if (projectOp)
		{
			file = fopen(filePath, READ_MODE);

			// Making sure file can be opened
			if (file)
			{
				// Getting the length of the file
				fseek(file, 0, SEEK_END);
				fileLength = ftell(file);
				fseek(file, 0, SEEK_SET);

				fclose(file);

				// Making sure file is not empty
				if (fileLength >= MIN_FILE_LEN)
				{
					isValid = TRUE;
				}
			}

		}

		// Otherwise, if I want to save the current project (Could be also new file) then we say the path is valid
		else
		{
			isValid = TRUE;
		}
	}

	return isValid;
}
