#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <psapi.h>
#include <time.h>
#include <global_Structures_and_variables.c>
//#pragma warning(disable : 4996)
#pragma once



time_t t;


void addprocess(DWORD processID)
{

	startTimeInSec = time(&t);
	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;

	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return;

	HMODULE hMods[1024];
	DWORD cbNeeded;
	TCHAR Buffer[MAX_PATH];
	TCHAR Buffer2[MAX_PATH];

	if (GetModuleFileNameEx(hProcess, 0, Buffer, MAX_PATH))
	{
		// At this point, buffer contains the full path to the executable
	}
	else
	{
		// You better call GetLastError() here
	}


	currentProcess = (struct process*)malloc(sizeof(struct process));


	char str[500] = { '\0' };
	for (int j = 0; Buffer[j] != '\0'; j++)
	{
		str[j] = Buffer[j];
		//strcat(currentProcess->nameOFprocess, Buffer[j]);
	}
	strcpy(currentProcess->nameOFprocess, str);

	currentProcess->idOFprocess = processID;


	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		currentProcess->PageFaultCount = pmc.PageFaultCount;
		currentProcess->WorkingSetSize = pmc.WorkingSetSize;
		currentProcess->QuotaPagedPoolUsage = pmc.QuotaPagedPoolUsage;
		currentProcess->QuotaPeakPagedPoolUsage = pmc.QuotaPeakPagedPoolUsage;
		currentProcess->PagefileUsage = pmc.PagefileUsage;
		currentProcess->countDLL = 0;
		currentProcess->sampleNumber = countSample;
		currentProcess->next = NULL;
		currentProcess->prev = NULL;


		if (headProcess == NULL)
		{
			headProcess = currentProcess;
			tailProcess = currentProcess;
		}
		else
		{
			currentProcess->prev = tailProcess;
			tailProcess->next = currentProcess;
			tailProcess = currentProcess;
			//currentProcess->prev->data_DLL = headDLL;
		}
	}


	// Get Dlls List

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{

		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			if (GetModuleFileNameEx(hProcess, hMods[i], Buffer2, MAX_PATH))
			{
				currentDLL = (struct DLL*)malloc(sizeof(struct DLL));
				currentProcess->countDLL = i + 1;
				currentDLL->id_DLL = i + 1;

				char str[500] = { '\0' };
				for (int j = 0; Buffer2[j] != '\0'; j++)
				{
					str[j] = Buffer2[j];
				}
				strcpy(currentDLL->name_OF_DLL, str);
				//printf("%s", currentDLL->name_OF_DLL);
				currentDLL->next = NULL;
				currentDLL->prev = NULL;



				if (currentDLL->id_DLL == 1)
				{
					headDLL = NULL;
					tailDLL = NULL;
				}


				if (headDLL == NULL)
				{
					headDLL = currentDLL;
					tailDLL = currentDLL;
					currentProcess->data_DLL = headDLL;
				}
				else
				{
					currentDLL->prev = tailDLL;
					tailDLL->next = currentDLL;
					tailDLL = currentDLL;
					currentProcess->data_DLL = headDLL;
				}

				currentDLL = currentDLL->next;

				// Print the module name and handle value.
				//wprintf(L"%s\n", Buffer2);

			}
		}
	}
	free(currentDLL);
	countProcess++;
	currentProcess->processNumber = countProcess;


	ensTimeInSec = time(&t);
	currentProcess->samplingTimeInSec = ensTimeInSec - startTimeInSec;

	currentProcess = currentProcess->next;
	free(currentProcess);
	CloseHandle(hProcess);


}
