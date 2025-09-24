#include "ui.h"

/*
The function gets the user project choice (Create a new project/Load existing project)
Input: None (Void)
Output: User's choice --> 1/0 (1 - Load existing project, 0 - Create new project)
*/
int projectOpChoice()
{
	int userChoice = -1;

	printf("Welcome to Magshimim Movie Maker! What would you like to do?\n");
	printf("[0] Create a new project\n");
	printf("[1] Load existing project\n");

	// Taking user choice of project-operation until it is valid (Either 0 or 1)
	do
	{
		scanf("%d", &userChoice);
		getchar(); // Cleans buffer

		// If user chose invalid option we print to him error and the only options he may choose
		if ((userChoice != CREATE_PROJ) && (userChoice != LOAD_PROJ))
		{
			printf("Invalid choice! Please choose one of the options:\n");
			printf("[0] Create a new project\n");
			printf("[1] Load existing project\n");
		}
	} 
	while ((userChoice != CREATE_PROJ) && (userChoice != LOAD_PROJ));

	return userChoice;
}

/*
The function shows options menu and gets the user's choice
Input: None (Void)
Output: The user's desired operation to perform
*/
int menu()
{
	int opChoice = -1;

	printf("What would you like to do?\n");
	printf("[0] Exit\n");
	printf("[1] Add a new frame\n");
	printf("[2] Remove a frame\n");
	printf("[3] Change frame's index\n");
	printf("[4] Change a frame duration\n");
	printf("[5] Change duration of all frames\n");
	printf("[6] List frames\n");
	printf("[7] Play movie!\n");
	printf("[8] Save project\n");
	printf("[9] Reverse movie\n");

	scanf("%d", &opChoice);
	getchar(); // Cleans buffer

	return opChoice;
}

/*
The function takes string input from user and replaces new-line with NULL terminator
Input: The string and it's max length
Output: None (Void)
*/
void myFGets(char* string, int maxLength)
{
	fgets(string, maxLength, stdin);
	string[strcspn(string, NEW_LINE)] = 0;
}
