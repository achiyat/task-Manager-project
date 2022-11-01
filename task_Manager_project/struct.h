#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <psapi.h>
#include <time.h>
#pragma warning(disable : 4996)

#define SEPERATOR_1 "[LINE1]"
#define SEPERATOR_2 "[LIST]"
#define SEPERATOR_3 "[STATIC]"
#define Version 1;

struct headerFile
{
	int version;
	int CountS;
	char reserve[1000];
};

extern struct headerFile headFILE;

struct process
{
	char nameOFprocess[500];
	int idOFprocess;
	SIZE_T PageFaultCount;
	SIZE_T WorkingSetSize;
	SIZE_T QuotaPagedPoolUsage;
	SIZE_T QuotaPeakPagedPoolUsage;
	SIZE_T PagefileUsage;
	int countOFprocess;
	int processNumber;
	int SnapShotsNumber;
	int countDLL;
	struct DLLofProcess* dataDLL_OFprocess;
	struct process* next;
	struct process* prev;
};

extern struct process* headProcess;
extern struct process* tailProcess;
extern struct process* currentProcess;

struct DLLofProcess
{
	char name_OF_DLL[500];
	int id_DLL;
	int idOFprocess;
	struct DLLofProcess* next;
	struct DLLofProcess* prev;
};

extern struct DLLofProcess* headDLL;
extern struct DLLofProcess* tailDLL;
extern struct DLLofProcess* currentDLL;

extern struct DLLofProcess* head_longSnapShots_DLL;
extern struct DLLofProcess* tail_longSnapShots_DLL;
extern struct DLLofProcess* current_longSnapShots_DLL;

struct processOFdll
{
	int id_ITEM;
	char nameOFprocess[500];
	int idOFprocess;
	struct processOFdll* next;
	struct processOFdll* prev;
};

struct UniqueDLL
{
	int DLLid;
	char DLLname[500];
	int DLLcount;
	int processCount;
	struct processOFdll* dataProcess_OFdll;
	struct UniqueDLL* next;
	struct UniqueDLL* prev;
};

extern struct UniqueDLL* headUniqueDLL;
extern struct UniqueDLL* tailUniqueDLL;
extern struct UniqueDLL* currentUniqueDLL;

struct sample
{
	int id_sample;
	unsigned long sample_memory_avg;
	char samplingTime[10];
	int samplingTimeInSec;
	int DLL_Cnt;
	int countSample;
	int countOFprocess;
	struct process* data_process;
	struct sample* next;
	struct sample* prev;
};

extern struct sample* headSample;
extern struct sample* tailSample;
extern struct sample* currentSample;

extern int startTimeInSec, ensTimeInSec, id_process;
extern int countSnapShots, countProcess, countIDsample, count_ID_DLL, OneTime, FirstSnapShots, countNewDLL;
extern char file_name[25];
extern char nameLog[200];