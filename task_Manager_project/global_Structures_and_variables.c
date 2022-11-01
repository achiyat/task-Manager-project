#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <psapi.h>
#include <time.h>

#pragma once

time_t t;

struct process
{
	char nameOFprocess[500];
	int idOFprocess;
	unsigned long PageFaultCount;
	unsigned long WorkingSetSize;
	unsigned long QuotaPagedPoolUsage;
	unsigned long QuotaPeakPagedPoolUsage;
	unsigned long PagefileUsage;
	int samplingTimeInSec;
	int countOFprocess;
	int processNumber;
	int sampleNumber;
	int countDLL;
	struct DLL* data_DLL;
	struct process* next;
	struct process* prev;
};

struct process* headProcess = NULL;
struct process* tailProcess = NULL;
struct process* currentProcess;


struct DLL
{
	char name_OF_DLL[500];
	int id_DLL;
	struct DLL* next;
	struct DLL* prev;
};

struct DLL* headDLL = NULL;
struct DLL* tailDLL = NULL;
struct DLL* currentDLL;

struct sample
{
	int id_sample;
	struct process* data_process;
	struct sample* next;
	struct sample* prev;
};

struct sample* headSample = NULL;
struct sample* tailSample = NULL;

int startTimeInSec, ensTimeInSec;
int countSample, countProcess = 0;
char file_name[25];

