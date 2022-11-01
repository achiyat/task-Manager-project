
#include "struct.h"

void addDlls(HANDLE hProcess, int processID)
{
	HMODULE hMods[1024];
	DWORD cbNeeded;
	TCHAR nPROCESS[MAX_PATH];
	TCHAR nDLL[MAX_PATH];
	size_t numConverted;

	if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{

		for (int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			currentDLL = (struct DLLofProcess*)malloc(sizeof(struct DLLofProcess));
			if (!currentDLL)
			{
				LogError(strerror(GetLastError()));
				printf("error in addprocess - There is no memory available");
				exit(1);
			}

			if (GetModuleFileNameEx(hProcess, hMods[i], nDLL, MAX_PATH))
			{
				// Converts the name of the process to char
				char DLLname[MAX_PATH];
				wcstombs_s(&numConverted, DLLname, MAX_PATH, nDLL, MAX_PATH);
				if (numConverted != 0)
				{
					LogEvent("Found a DLL - starts loading the data");

					// defining "DLL of process"
					strcpy(currentDLL->name_OF_DLL, DLLname);
					currentProcess->countDLL = i + 1;
					currentDLL->id_DLL = i + 1;
					currentDLL->idOFprocess = currentProcess->idOFprocess;
					currentDLL->next = NULL;
					currentDLL->prev = NULL;
					currentProcess->dataDLL_OFprocess = NULL;

					LogEvent("Generates a new item for structure DLL of process");
					build_DOP(currentDLL);
					LogEvent("Item creation is complete");

					// Placement of all loaded DLLS
					currentProcess->dataDLL_OFprocess = headDLL;

					// When there is a long snapshot, then the program enters the condition to check if the DLL exists or not.
					if (currentProcess->SnapShotsNumber != 1)
					{
						int id_process = currentProcess->idOFprocess;
						LogEvent("calls a searchDLL function");
						searchDLL(id_process, DLLname, currentDLL);
						LogEvent("exited the searchDLL function");
					}

					// calls the buildDLL function that builds a data structure for each DLL (unique DLL)
					LogEvent("calls a buildDLL function");
					buildDLL(DLLname, currentProcess);
					LogEvent("exited the buildDLL function");
				}
			}
		}
	}

	LogEvent("The DLL data loading is complete");
}