
#include "struct.h"

void addprocess(DWORD processID)
{
	/* The function receives a process with its data, and adds the process to a linked list.
	After that, it gets all the DLLs of the process, and builds a linked list of DLLS.
	The DLLS list will be a sublist for each process. */

	HANDLE hProcess;
	PROCESS_MEMORY_COUNTERS pmc;


	hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID);
	if (NULL == hProcess)
		return;


	HMODULE hMods[1024];
	DWORD cbNeeded;
	TCHAR nPROCESS[MAX_PATH];
	TCHAR nDLL[MAX_PATH];

	if (!GetModuleFileNameEx(hProcess, 0, nPROCESS, MAX_PATH))
	{
		LogError("error: nPROCESS not contains the full path to the executable");
		return;
	}

	currentProcess = (struct process*)malloc(sizeof(struct process));
	if (!currentProcess)
	{
		LogError(strerror(GetLastError()));
		printf("error in addprocess - There is no memory available");
		exit(1);
	}

	// Converts the name of the process to char
	char processName[MAX_PATH];
	size_t numConverted;
	wcstombs_s(&numConverted, processName, MAX_PATH, nPROCESS, MAX_PATH);
	if (numConverted == 0)
	{
		return;
	}

	LogEvent("Found a process - starts loading the data");

	//defining "process"
	if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		strcpy(currentProcess->nameOFprocess, processName);
		currentProcess->idOFprocess = processID;
		countProcess++;
		currentProcess->PageFaultCount = pmc.PageFaultCount;
		currentProcess->WorkingSetSize = pmc.WorkingSetSize;
		currentProcess->QuotaPagedPoolUsage = pmc.QuotaPagedPoolUsage;
		currentProcess->QuotaPeakPagedPoolUsage = pmc.QuotaPeakPagedPoolUsage;
		currentProcess->PagefileUsage = pmc.PagefileUsage;
		currentProcess->countDLL = 0;
		currentProcess->SnapShotsNumber = countSnapShots;
		currentProcess->processNumber = countProcess;
		currentProcess->next = NULL;
		currentProcess->prev = NULL;
	}

	/*Builds a linked list of processes but enters the condition only in the first Snapshot!
	In the rest of the snapshots the list will be updated from the searchProcess function.*/
	if (countSnapShots == 1)
	{
		LogEvent("Generates a new item for structure sample");
		buildP(currentProcess);
		LogEvent("Item creation is complete");
	}

	// Get Dlls List
	LogEvent("calls a addDlls function");
	addDlls(hProcess, processID);
	LogEvent("exited the addDlls function");

	// When there is a long snapshot, then the program enters the condition to check if the process exists or not.
	if (currentProcess->SnapShotsNumber != 1)
	{
		int id_process = currentProcess->idOFprocess;
		LogEvent("calls a searchProcess function");
		searchProcess(id_process, currentProcess);
		LogEvent("exited the searchProcess function");
	}

	// Closes the array
	CloseHandle(hProcess);
	LogEvent("The process data loading is complete");

}

void GetProcessesInfo()
{
	// Get Processes
	// Receive all process ID

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		LogError("error: The processes were not accepted");
		return;
	}

	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);


	// Print the memory usage for each process
	for (i = 0; i < cProcesses; i++)
	{
		LogEvent("calls a addprocess function");
		addprocess(aProcesses[i]);
		LogEvent("exited the addprocess function");
	}

	// After the program has finished sampling the processes, it can add the last field of the process (each process) - the count of processes present in the sample
	if (countSnapShots == 1)
	{
		while (currentProcess != NULL)
		{
			currentProcess->countOFprocess = countProcess;
			currentProcess = currentProcess->prev;
		}
	}

	// Resets the variable so we can use it again later
	countProcess = 0;
}