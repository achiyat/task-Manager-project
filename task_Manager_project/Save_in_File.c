
#include "struct.h"

void Save_in_File()
{
	// A function saves the data of the samples in a file

	headFILE.version = Version;
	headFILE.CountS = headSample->countSample;

	file_name[0] = 0;

	// The name of the file that receives the data of all samples
	strcpy(file_name, "file sample.bin");

	LogEvent("Opens the file for writing/reading");
	FILE* f = fopen(file_name, "wb");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in Save_in_File - The file did not open");
		exit(1);
	}

	// Writes the fields of the structure header File to the file
	fwrite(&headFILE, sizeof(struct headerFile), 1, f);

	struct sample* currentOFsaveSample = headSample;
	struct process* currentOFsaveProcess = currentOFsaveSample->data_process;
	struct DLLofProcess* currentOFsaveDLL = currentOFsaveProcess->dataDLL_OFprocess;

	//  Writes to the file each sample separately
	LogEvent("Writing to the file is in progress");
	while (currentOFsaveSample != NULL)
	{
		fwrite(currentOFsaveSample, sizeof(struct sample), 1, f);
		while (currentOFsaveProcess != NULL)
		{
			fwrite(currentOFsaveProcess, sizeof(struct process), 1, f);
			while (currentOFsaveDLL != NULL)
			{
				fwrite(currentOFsaveDLL, sizeof(struct DLLofProcess), 1, f);
				currentOFsaveDLL = currentOFsaveDLL->next;
			}
			currentOFsaveProcess = currentOFsaveProcess->next;
			if (currentOFsaveProcess != NULL)
			{
				currentOFsaveDLL = currentOFsaveProcess->dataDLL_OFprocess;
			}
		}
		currentOFsaveSample = currentOFsaveSample->next;
		if (currentOFsaveSample != NULL)
		{
			currentOFsaveProcess = currentOFsaveSample->data_process;
			currentOFsaveDLL = currentOFsaveProcess->dataDLL_OFprocess;
		}
	}
	LogEvent("Writing to the file is complete");
	fclose(f);

}