
#include "struct.h"

void Log(char message[100])
{
	// the function will write the events or errors that are made in real time, so we can identify where the program got stuck.

	time_t t1;
	time(&t1);
	struct tm* timeinfo;
	timeinfo = localtime(&t1);

	if (OneTime == 0)
	{
		sprintf(nameLog, "Log_%d%d%d_%d%d%d_.log", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_wday + 1, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		OneTime++;
	}

	FILE* f1 = fopen(nameLog, "a");
	if (!f1)
	{
		printf("The file did not open");
		exit(1);
	}

	char str[200];
	sprintf(str, "%d/%d/%d  %d:%d  %s\n", timeinfo->tm_wday + 1, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, message);
	fputs(str, f1);


	fclose(f1);
}

void LogError(char message[100])
{
	Log(message);
}

void LogEvent(char message[100])
{
	Log(message);
}