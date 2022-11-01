
#include "struct.h"

void searchDLL(int id_process, char DLLname[500], struct DLLofProcess* current)
{
	//The function checks whether the DLL exists or not, if the DLL exists - continue with the program, if the DLL does not exist - builds a linked list and then in the searchProcess function adds the DLL to the list
	//** Given: The process of that DLL must exist

	struct process* find_process = headProcess;

	// Looking for the process
	while (find_process != NULL && find_process->idOFprocess != id_process)
	{
		find_process = find_process->next;
	}

	// If not find the process - continue with the program
	if (find_process == NULL)
	{
		return;
	}

	// If find the process
	if (find_process->idOFprocess == id_process)
	{
		struct DLLofProcess* find_DLL = find_process->dataDLL_OFprocess;
		// Looking for the DLL
		while (find_DLL != NULL && strcmp(find_DLL->name_OF_DLL, DLLname) != 0)
		{
			find_DLL = find_DLL->next;
		}

		// If not find the DLL
		if (find_DLL == NULL)
		{
			current_longSnapShots_DLL = current;
			current_longSnapShots_DLL->next = NULL;
			current_longSnapShots_DLL->prev = NULL;

			//  Makes a small list of all the DLL's it did not find
			LogEvent("Generates a new item for structure longSnapShots_DLL");
			if (head_longSnapShots_DLL == NULL)
			{
				head_longSnapShots_DLL = current_longSnapShots_DLL;
				tail_longSnapShots_DLL = current_longSnapShots_DLL;
				countNewDLL++;
			}
			else
			{
				tail_longSnapShots_DLL->next = current_longSnapShots_DLL;
				current_longSnapShots_DLL->prev = tail_longSnapShots_DLL;
				tail_longSnapShots_DLL = current_longSnapShots_DLL;
				countNewDLL++;
			}
			LogEvent("Item creation is complete");
		}

		// If a DLL is found - continue with the program
	}
}

void searchProcess(int id_process, struct process* current)
{
	// The function checks whether the process exists or not, if the process does not exist - creates a new item for it. If the process exists - adds to I the new DLLS created in the "searchDLL" function
	// In addition, the memory data was summarized

	struct process* find_process = headProcess;

	// Looking for the process
	while (find_process != NULL && find_process->idOFprocess != id_process)
	{
		find_process = find_process->next;
	}

	if (find_process == NULL)  // If not find the process
	{
		LogEvent("Generates a new item for structure Process");
		current->processNumber = tailProcess->processNumber + 1;
		current->countOFprocess = tailProcess->countOFprocess + 1;
		tailProcess->next = current;
		current->prev = tailProcess;
		tailProcess = current;
		current->SnapShotsNumber = countSnapShots;
		LogEvent("Item creation is complete");
	}
	else if (find_process->idOFprocess == id_process)  // If find the process
	{

		// Adds new DLLs if any
		if (head_longSnapShots_DLL != NULL) // In other words, if new DLLS were added
		{
			LogEvent("Adds the DLL to a process's sublist");
			struct DLLofProcess* find_DLL = find_process->dataDLL_OFprocess;
			while (find_DLL->next != NULL)
			{
				find_DLL = find_DLL->next;
			}

			find_DLL->next = head_longSnapShots_DLL;
			head_longSnapShots_DLL->prev = find_DLL;
			find_DLL = head_longSnapShots_DLL;
			find_process->countDLL += countNewDLL;

			//Makes sure the ID will be synchronized
			while (find_DLL != NULL)
			{
				find_DLL->id_DLL = find_DLL->prev->id_DLL + 1;
				find_DLL = find_DLL->next;
			}

			LogEvent("The adding DLL is complete");
		}

		head_longSnapShots_DLL = NULL;
		tail_longSnapShots_DLL = NULL;
		countNewDLL = 0;

		// The new data of the process is summarized and updated according to the requirement
		find_process->PageFaultCount += current->PageFaultCount;
		find_process->WorkingSetSize += current->WorkingSetSize;
		find_process->QuotaPagedPoolUsage += current->QuotaPagedPoolUsage;
		find_process->QuotaPeakPagedPoolUsage += current->QuotaPeakPagedPoolUsage;
		find_process->PagefileUsage += current->PagefileUsage;
		find_process->SnapShotsNumber = countSnapShots;

		free(current);
		
	}
}