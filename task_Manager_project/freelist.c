
#include "struct.h"

void freelistDOP(struct process* head)
{
	// The function deletes the memory from the structure, when there is a structure within a structure (a list with a sub-list inside it)

	struct process* freelist = head;
	// If for any reason the structure is empty, then the function exits
	if (freelist == NULL)
	{
		LogEvent("Event: The structure is empty");
		return;
	}

	LogEvent("Begins by freeing the memory of the structure DLL of Process");
	// Promotes the main list
	while (freelist != NULL)
	{
		struct DLLofProcess* current = freelist->dataDLL_OFprocess;
		struct DLLofProcess* freeitem = freelist->dataDLL_OFprocess;

		// Promotes the secondary list, which actually needs to be freed.
		while (freelist->dataDLL_OFprocess != NULL)
		{
			current = current->next;
			free(freeitem);
			freelist->dataDLL_OFprocess = current;
			freeitem = current;
		}
		freelist = freelist->next;
	}
	LogEvent("the memory freeing is complete");
}

void freelistProcess(struct process* head)
{
	// The function deletes the memory from the structure

	struct process* current = head;
	struct process* freeitem = head;

	// If for any reason the structure is empty, then the function exits
	if (current == NULL)
	{
		LogEvent("Event: The structure is empty");
		return;
	}

	LogEvent("Begins by freeing the memory of the structure Process");
	while (head != NULL)
	{
		current = current->next;
		free(freeitem);
		freeitem = current;
		head = current;
	}
	LogEvent("the memory freeing is complete");
	return;
}

void freelistSample()
{
	// The function deletes the memory from the structure

	struct sample* current = headSample;
	struct sample* freeitem = headSample;
	struct process* headP;

	// If for any reason the structure is empty, then the function exits
	if (current == NULL)
	{
		LogEvent("Event: The structure is empty");
		return;
	}

	LogEvent("Begins by freeing the memory of the structure sample");  //  לחזור לזההההה
	while (headSample != NULL)
	{
		headP = headSample->data_process;
		freelistDOP(headP);
		freelistProcess(headP);
		current = current->next;
		free(freeitem);
		headSample = current;
		freeitem = current;
	}
	LogEvent("the memory freeing is complete");
	return;
}

void freePro_OFdll(struct UniqueDLL* head)
{
	// The function deletes the memory from the structure, when there is a structure within a structure (a list with a sub-list inside it)

	struct UniqueDLL* freelist = head;

	// If for any reason the structure is empty, then the function exits
	if (freelist == NULL)
	{
		LogEvent("Event: The structure is empty");
		return;
	}

	LogEvent("Begins by freeing the memory of the structure Process of DLL");
	// Promotes the main list
	while (freelist != NULL)
	{
		struct processOFdll* current = freelist->dataProcess_OFdll;
		struct processOFdll* freeitem = freelist->dataProcess_OFdll;

		// Promotes the secondary list, which actually needs to be freed.
		while (freelist->dataProcess_OFdll != NULL)
		{
			current = current->next;
			free(freeitem);
			freelist->dataProcess_OFdll = current;
			freeitem = current;
		}
		freelist = freelist->next;
	}
	LogEvent("the memory freeing is complete");
}

void freelistDLL(struct UniqueDLL* head)
{
	// The function deletes the memory from the structure

	struct UniqueDLL* current = head;
	struct UniqueDLL* freeitem = head;

	// If for any reason the structure is empty, then the function exits
	if (current == NULL)
	{
		LogEvent("Event: The structure is empty");
		return;
	}

	LogEvent("Begins by freeing the memory of the structure DLL");
	while (head != NULL)
	{
		current = current->next;
		free(freeitem);
		freeitem = current;
		head = current;
	}
	LogEvent("the memory freeing is complete");
	return;
}

void ResetCollections()
{
	// The function deletes all the accumulated memory

	LogEvent("calls a freelistSample function");
	freelistSample();

	LogEvent("calls a freePro_OFdll function");
	freePro_OFdll(headUniqueDLL);

	LogEvent("calls a freelistDLL function");
	freelistDLL(headUniqueDLL);

	// Resets the variable because the function has reset the entire program.
	FirstSnapShots = 0;
	count_ID_DLL = 0;
	countIDsample = 0;
}