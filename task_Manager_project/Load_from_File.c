
#include "struct.h"

void Load_from_File()
{
	// The function reads the data from the file

	LogEvent("Opens the file for writing/reading");
	FILE* f = fopen(file_name, "rb");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in Load_from_File - The file did not open");
		exit(1);
	}

	struct headerFile headOFfile;

	// Reads the headerFile data from the file
	int read = fread(&headOFfile, sizeof(struct headerFile), 1, f);

	LogEvent("Reading from the file begins");
	for (int i = 1; i <= headOFfile.CountS; i++)
	{
		struct sample* currentSampleOFread = (struct sample*)malloc(sizeof(struct sample));
		if (!currentSampleOFread)
		{
			LogError(strerror(GetLastError()));
			printf("error in Load_from_File - There is no memory available");
			exit(1);
		}

		read = fread(currentSampleOFread, sizeof(struct sample), 1, f);

		for (int j = 1; j <= currentSampleOFread->countOFprocess; j++)
		{
			struct process* currentProcessOFread = (struct process*)malloc(sizeof(struct process));
			if (!currentProcessOFread)
			{
				LogError(strerror(GetLastError()));
				printf("error in Load_from_File - There is no memory available");
				exit(1);
			}

			read = fread(currentProcessOFread, sizeof(struct process), 1, f);

			for (int e = 1; e <= currentProcessOFread->countDLL; e++)
			{
				struct DLLofProcess* currentDLLOFread = (struct DLLofProcess*)malloc(sizeof(struct DLLofProcess));
				if (!currentDLLOFread)
				{
					LogError(strerror(GetLastError()));
					printf("error in Load_from_File - There is no memory available");
					exit(1);
				}

				if (e == 1000)
				{
					int a = 0;
				}

				read = fread(currentDLLOFread, sizeof(struct DLLofProcess), 1, f);
				if (e == currentProcessOFread->countDLL)
				{
					currentDLLOFread->next = NULL;
				}
				build_DOP(currentDLLOFread);
			}

			currentProcessOFread->dataDLL_OFprocess = headDLL;
			if (j == currentSampleOFread->countOFprocess)
			{
				currentProcessOFread->next = NULL;
			}
			buildP(currentProcessOFread);

		}

		currentSampleOFread->data_process = headProcess;
		if (i == headOFfile.CountS)
		{
			currentSampleOFread->next = NULL;
		}

		if (headSample != NULL)
		{
			countIDsample++;
			currentSampleOFread->id_sample = countIDsample;
		}
		buildS(currentSampleOFread);

	}
	LogEvent("Reading from the file is complete");
	fclose(f);

}