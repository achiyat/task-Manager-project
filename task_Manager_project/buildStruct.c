
#include "struct.h"

void buildS(struct sample* currentS)
{
	//The function builds the structure

	if (currentS->id_sample == 1)
	{
		headSample = NULL;
		tailSample = NULL;
	}

	if (headSample == NULL)
	{
		headSample = currentS;
		tailSample = currentS;
	}
	else
	{
		tailSample->next = currentS;
		currentS->prev = tailSample;
		tailSample = currentS;
	}

	// Updates the total amount of samples in the entire program
	if (currentS->id_sample > 1)
	{
		struct sample* count = tailSample;

		while (count != NULL)
		{
			count->countSample = tailSample->id_sample;
			count = count->prev;
		}
	}

}

void buildP(struct process* currentP)
{
	//The function builds the structure

	if (currentP->processNumber == 1)
	{
		headProcess = NULL;
		tailProcess = NULL;
	}

	if (headProcess == NULL)
	{
		headProcess = currentP;
		tailProcess = currentP;
	}
	else
	{
		tailProcess->next = currentP;
		currentP->prev = tailProcess;
		tailProcess = currentP;
	}
}

void build_DOP(struct DLLofProcess* currentD)
{
	//The function builds the structure

	if (currentD->id_DLL == 1)
	{
		headDLL = NULL;
		tailDLL = NULL;
	}

	if (headDLL == NULL)
	{
		headDLL = currentD;
		tailDLL = currentD;
	}
	else
	{
		tailDLL->next = currentD;
		currentD->prev = tailDLL;
		tailDLL = currentD;
	}
}