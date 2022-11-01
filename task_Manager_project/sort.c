
#include "struct.h"

void replace(struct process* replaceitem)
{
	// The function receives two numbers according to their position in the listand will replace their position from the smallest to the largest
	if (replaceitem == NULL) //אפס איברים
	{
		LogEvent("no item in list, no need to swap");
	}
	else if (replaceitem->next == NULL) // האחרון
	{
		LogEvent("the last number, no need to swap");
	}
	else if (replaceitem == headProcess && replaceitem->next == tailProcess) // שני איברים ברשימה
	{
		replaceitem->next = NULL;
		replaceitem->prev = tailProcess;
		tailProcess->prev = NULL;
		tailProcess->next = replaceitem;
		tailProcess = replaceitem;
		headProcess = replaceitem->prev;
	}
	else if (replaceitem == headProcess && replaceitem->next != NULL)  // שלוש צמוד לשמאל
	{
		replaceitem->next = replaceitem->next->next;
		replaceitem->next->prev->next = replaceitem;
		replaceitem->next->prev->prev = NULL;
		replaceitem->prev = replaceitem->next->prev;
		replaceitem->next->prev = replaceitem;
		headProcess = replaceitem->prev;
	}
	else if (replaceitem->next == tailProcess)  // שלוש צמוד לימין
	{
		replaceitem->prev->next = replaceitem->next;
		replaceitem->next->prev = replaceitem->prev;
		replaceitem->next->next = replaceitem;
		replaceitem->prev = replaceitem->next;
		replaceitem->next = NULL;
		tailProcess = replaceitem;
	}
	else // שניים באמצע
	{
		replaceitem->prev->next = replaceitem->next; // 1->3
		replaceitem->next->prev = replaceitem->prev; // 3->1 
		replaceitem->next->next->prev = replaceitem; // 4->2
		replaceitem->prev = replaceitem->next; //2->3
		replaceitem->next = replaceitem->next->next; // 2->4
		replaceitem->prev->next = replaceitem; // 3->2
	}
}

void sort()
{
	// The function will sort the list according to the amount of DLLs using the "replace" function.

	struct process* sorted = headProcess;

	if (sorted == NULL)
	{
		LogEvent("the list is empty");
		return;
	}

	int change = 1;
	int CNT= tailProcess->countOFprocess;
	LogEvent("starts sorting");
	while (change != 0)
	{
		change = 0;
		while (sorted != NULL)
		{
			if (sorted->next != NULL && sorted->countDLL > sorted->next->countDLL)
			{
				replace(sorted);
				change++;
			}
			//CNT = sorted.
			sorted = sorted->next;
		}

		sorted = headProcess;
	}
	LogEvent("Sorting is over");

	// Arranges the numerical number of the items
	int count = 0;
	while (sorted != NULL)
	{
		count++;
		sorted->countOFprocess = CNT;
		sorted->processNumber = count;
		sorted = sorted->next;
	}
}