
#include "struct.h"

void addsample(struct process* headitem)
{
	// The function builds a linked list for each and every sample, containing all the data collected in the sample 
	time_t t2;
	time(&t2);
	struct tm* Timeinfo;
	Timeinfo = localtime(&t2);

	currentSample = (struct sample*)malloc(sizeof(struct sample));
	if (!currentSample)
	{
		LogError(strerror(GetLastError()));
		printf("error in addsample - There is no memory available");
		exit(1);
	}

	// defining "sample"
	currentSample->sample_memory_avg = 0;
	currentSample->DLL_Cnt = 0;
	sprintf(currentSample->samplingTime, "%d:%d:%d", Timeinfo->tm_hour, Timeinfo->tm_min, Timeinfo->tm_sec);
	ensTimeInSec = time(&t2);
	currentSample->samplingTimeInSec = ensTimeInSec - startTimeInSec;

	// memory avg & DLL Cnt
	struct process* curr = headitem;
	while (curr != NULL)
	{
		SIZE_T memory = curr->WorkingSetSize / curr->countOFprocess;
		currentSample->sample_memory_avg += memory;
		int dll = curr->countDLL;
		currentSample->DLL_Cnt += dll;
		curr = curr->next;
	}

	countIDsample++;
	currentSample->id_sample = countIDsample;
	currentSample->countOFprocess = headitem->countOFprocess;
	currentSample->data_process = headitem;
	currentSample->next = NULL;
	currentSample->prev = NULL;

	LogEvent("Generates a new item for structure sample");
	buildS(currentSample);
	LogEvent("Item creation is complete");

	currentSample = currentSample->next;

}