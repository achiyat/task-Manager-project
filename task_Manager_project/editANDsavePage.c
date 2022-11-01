
#include "struct.h"

int SaveIntoFile(char* fileName, char* buff)
{
	//  The function saves the string (code) it received into an HTML file, thus actually creating a website.
	LogEvent("Opens the file for writing/reading");
	FILE* f = fopen(fileName, "w");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in SaveIntoFile - The file did not open");
		exit(1);
	}

	// Copies the entire string to a file
	LogEvent("Copy the string into a file");
	fputs(buff, f);
	LogEvent("Writing to the file is complete");
	fclose(f);
}

char* ReadAllFile(char* fileName)
{
	// The function reads each char individually, and at the end creates one long string (the website's code)
	LogEvent("Opens the file for writing/reading");
	FILE* f = fopen(fileName, "r");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in ReadAllFile - The file did not open");
		exit(1);
	}

	// Get the file size
	char* buff = (char*)malloc(1000);
	char* read;

	// Reads the number of characters in each line
	int fileSize = 0;

	LogEvent("The reading of the quantity of each row begins");
	while ((read = fgets(buff, 1000, f)))
	{
		fileSize += strlen(buff);
	}
	LogEvent("The reading is over complete");

	free(buff);

	fclose(f);

	// alloc space as file size
	buff = (char*)malloc(fileSize);

	LogEvent("Opens the file for writing/reading");
	f = fopen(fileName, "r");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in ReadAllFile - The file did not open");
		exit(1);
	}

	// Counts the place in the cell of char buff, and thus reads character by character throughout the string
	int readPosition = 0;
	char charToRead;
	LogEvent("Reading the amount of each char begins");
	while ((charToRead = fgetc(f)) != EOF)
	{
		buff[readPosition] = charToRead;
		readPosition++;
	}
	LogEvent("The reading is over complete");

	// Closes the array with NULL
	buff[readPosition] = NULL;

	LogEvent("closes the file");
	fclose(f);

	return buff;
}

void Global_page_editing(char Template[100], char newTemplate[100], char SEPERATOR[10])
{
	//The function receives a piece of code which it adds to the site's code! The function edits all pages of the sites and is therefore global.
	//The function reads the code of the entire site, cuts the code in two, and adds the part of the code that you want to add between them.

	LogEvent("calls a ReadAllFile function");
	// Puts everything written in the code.txt file into the array
	char* HTML_REPLACE = ReadAllFile("code.txt");

	LogEvent("calls a ReadAllFile function");
	// Puts into the array everything that is written in the Template(File) variable
	char* htmlTemplate = ReadAllFile(Template);

	// Cuts all the characters up to the part of the code that writes the string that is in the SEPERATOR variable
	char* found = strstr(htmlTemplate, SEPERATOR);

	int len = found - htmlTemplate;

	// Takes up space in memory the size of these 2 variables
	char* newBuff = (char*)malloc(strlen(htmlTemplate) + strlen(HTML_REPLACE));

	//  Copies the first part that was cut, and close with 0.
	strncpy(newBuff, htmlTemplate, len);
	newBuff[len] = NULL;

	// Adds the variable to the string, and closes with 0.
	strcat(newBuff, HTML_REPLACE);
	newBuff[len + strlen(HTML_REPLACE)] = NULL;

	// Adds the second part that was cut to the string
	strcat(newBuff, found + strlen(SEPERATOR));

	// Saves the file after editing
	LogEvent("calls a SaveIntoFile function");
	SaveIntoFile(newTemplate, newBuff);
	free(newBuff);

}