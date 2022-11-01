#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <psapi.h>
#include <time.h>
#pragma warning(disable : 4996)

#include "struct.h"

struct headerFile headFILE;

struct process* headProcess = NULL;
struct process* tailProcess = NULL;
struct process* currentProcess;

struct DLLofProcess* headDLL = NULL;
struct DLLofProcess* tailDLL = NULL;
struct DLLofProcess* currentDLL;

struct DLLofProcess* head_longSnapShots_DLL = NULL;
struct DLLofProcess* tail_longSnapShots_DLL = NULL;
struct DLLofProcess* current_longSnapShots_DLL;

struct UniqueDLL* headUniqueDLL = NULL;
struct UniqueDLL* tailUniqueDLL = NULL;
struct UniqueDLL* currentUniqueDLL;

struct sample* headSample = NULL;
struct sample* tailSample = NULL;
struct sample* currentSample;

int startTimeInSec, ensTimeInSec, id_process;
int countSnapShots, countProcess, countIDsample, count_ID_DLL, OneTime, FirstSnapShots, countNewDLL = 0;
char file_name[25];
char nameLog[200];
char userResponse = '0';

int main()
{
	LogEvent("The program started running\n");
	time_t t2;

	while (userResponse != '9')
	{
		printf("Click '1' for Take One SnapShot \n");
		printf("Click '2' for Take 20 SnapShots \n");
		printf("Click '3' for Start Long SnapShot \n");
		printf("Click '4' for End Long SnapShot \n");
		printf("Click '5' for Generate HTML Report \n");
		printf("Click '6' for Reset Collections \n");
		printf("Click '7' for Save in File \n");
		printf("Click '8' for Load from File \n");
		printf("Click '9' for Quit \n\n");

		userResponse = getch();

		switch (userResponse)
		{
		case '1':
			printf("Activates One SnapShot \n");
			startTimeInSec = time(&t2);
			countSnapShots++;
			GetProcessesInfo();
			sort();
			addsample(headProcess);
			countSnapShots = 0;
			ensTimeInSec = time(&t2);
			printf("%d\n", ensTimeInSec- startTimeInSec);
			printf("One SnapShot is over \n\n");
			break;

		case '2':
			printf("Activates 20 SnapShot \n");
			startTimeInSec = time(&t2);
			for (int i = 1; i <= 10; i++)
			{
				countSnapShots++;
				GetProcessesInfo();
				printf("SnapShot %d \n", countSnapShots);
				Sleep(1000);
			}
			sort();
			addsample(headProcess);
			countSnapShots = 0;
			ensTimeInSec = time(&t2);
			printf("%d\n", ensTimeInSec - startTimeInSec);
			printf("20 SnapShot is over \n\n");
			break;

		case '3':
			printf("Activates Long SnapShot \n");
			printf("Click '4' for End Long SnapShot \n");
			startTimeInSec = time(&t2);
			int stop = 0;
			while (!stop)
			{
				countSnapShots++;
				GetProcessesInfo();
				printf("SnapShot %d \n", countSnapShots);
				if (kbhit())
				{
					char ch = getch();

					if (ch == '4')
					{
						printf("You asked to stop the Long SnapShot \n");
						stop = 1;
					}
				}
				Sleep(100);
			}
			sort();
			addsample(headProcess);
			countSnapShots = 0;
			ensTimeInSec = time(&t2);
			printf("%d\n", ensTimeInSec - startTimeInSec);
			printf("Long SnapShot is over \n\n");

			break;

		case '5':
			printf("Activates Generate HTML Report \n");
			Create_sample_page();
			Create_DLL_page();
			Create_home_page();
			printf("Generate HTML Report is over \n\n");
			break;

		case '6':
			printf("Activates Reset Collections \n");
			ResetCollections();
			printf("The memory is empty, Reset Collections is over \n\n");
			break;

		case '7':
			printf("Activates Save function \n");
			Save_in_File();
			printf("Save function is over \n\n");
			break;

		case '8':
			printf("Activates Load function \n");
			Load_from_File();
			printf("Load function is over \n\n");
			break;

		case '9':
			printf("end");
			break;
		}
	}

	LogEvent("The program has finished running\n");
	return 0;
}