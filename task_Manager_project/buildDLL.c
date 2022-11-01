
#include "struct.h"

void buildDLL(char DLLname[MAX_PATH], struct process* currProcess)
{
	// The function builds a linked list for each DLL, and each DLL will have a sublist showing the processes that loaded it.
	// If the DLL is new - create a new item for it, if the DLL exists - add the process name to the sub - list of processes

	currentUniqueDLL = (struct UniqueDLL*)malloc(sizeof(struct UniqueDLL));
	if (!currentUniqueDLL)
	{
		LogError(strerror(GetLastError()));
		printf("error in buildDLL - There is no memory available");
		exit(1);
	}

	struct processOFdll* infoProcess = (struct processOFdll*)malloc(sizeof(struct processOFdll));
	if (!infoProcess)
	{
		LogError(strerror(GetLastError()));
		printf("error in buildDLL - There is no memory available");
		exit(1);
	}


	// "infoProcess"
	strcpy(infoProcess->nameOFprocess, currProcess->nameOFprocess);
	infoProcess->idOFprocess = currProcess->idOFprocess;
	infoProcess->next = NULL;
	infoProcess->prev = NULL;

	//defining "DLL"
	strcpy(currentUniqueDLL->DLLname, DLLname);
	currentUniqueDLL->processCount = 1;
	currentUniqueDLL->dataProcess_OFdll = infoProcess;
	currentUniqueDLL->next = NULL;
	currentUniqueDLL->prev = NULL;

	// All the DLLS of the first process are new, so we will create an item in the list for all of them
	if (currProcess->processNumber == 1 && FirstSnapShots == 0)
	{
		count_ID_DLL++;
		currentUniqueDLL->DLLid = count_ID_DLL;
		currentUniqueDLL->dataProcess_OFdll->id_ITEM = 1;

		LogEvent("Generates a new item for structure DLL");
		if (count_ID_DLL == 1)
		{
			headUniqueDLL = NULL;
			tailUniqueDLL = NULL;
		}

		if (headUniqueDLL == NULL)
		{
			headUniqueDLL = currentUniqueDLL;
			tailUniqueDLL = currentUniqueDLL;
		}
		else
		{
			tailUniqueDLL->next = currentUniqueDLL;
			currentUniqueDLL->prev = tailUniqueDLL;
			tailUniqueDLL = currentUniqueDLL;
		}
		LogEvent("Item creation is complete");
		currentUniqueDLL = currentUniqueDLL->next;
		infoProcess = infoProcess->next;
	}
	else
	{
		FirstSnapShots = 1;
		struct UniqueDLL* find_DLL = headUniqueDLL;

		// Looking for the DLL
		while (find_DLL != NULL && strcmp(find_DLL->DLLname, DLLname) != 0)
		{
			find_DLL->DLLcount = tailUniqueDLL->DLLid;
			find_DLL = find_DLL->next;
		}

		//  If it did not find the DLL, then a new item is created in the list
		if (find_DLL == NULL)
		{
			count_ID_DLL++;
			currentUniqueDLL->DLLid = count_ID_DLL;
			currentUniqueDLL->dataProcess_OFdll->id_ITEM = 1;

			LogEvent("Generates a new item for structure DLL");
			tailUniqueDLL->next = currentUniqueDLL;
			currentUniqueDLL->prev = tailUniqueDLL;
			tailUniqueDLL = currentUniqueDLL;
			LogEvent("Item creation is complete");

			tailUniqueDLL->DLLcount = currentUniqueDLL->DLLid;
			currentUniqueDLL = currentUniqueDLL->next;
		}
		else if (strcmp(find_DLL->DLLname, DLLname) == 0)
		{
			//  If it found the DLL then adds the process to the sub-list of the processes

			// Checks if there is a process that has previously loaded the DLL
			struct processOFdll* ProcessOFdll = find_DLL;
			while (ProcessOFdll != NULL && ProcessOFdll->idOFprocess != infoProcess->idOFprocess)
			{
				//If it does not find the process, then adds to the sub-list of the processes.
				if (ProcessOFdll->next == NULL)
				{
					LogEvent("Adds the process to a DLL's sublist");
					ProcessOFdll->next = infoProcess;
					infoProcess->prev = ProcessOFdll;
					ProcessOFdll = infoProcess;
					LogEvent("The adding process is complete");

					infoProcess->id_ITEM = infoProcess->prev->id_ITEM + 1;
					find_DLL->processCount++;

					return;
				}

				ProcessOFdll = ProcessOFdll->next;
			}
		}
	}
}