
#include "struct.h"

void Create_home_page()
{
	// The function creates a piece of codeand adds the generated code to the existing code.
	// The generated code builds the homepage tables

	char code[300];
	char SEPERATOR[10] = { '\0' };
	char Template[50] = { '\0' };
	char newTemplate[50] = { '\0' };

	struct sample* infoSample = headSample;
	struct UniqueDLL* infoDLL = headUniqueDLL;
	unsigned long memory_avg = 0;
	int processCnt = 0;

	// Calculates the average of all the averages in the other samples
	while (infoSample != NULL)
	{
		if (processCnt < infoSample->data_process->countOFprocess)
		{
			processCnt = infoSample->data_process->countOFprocess;
		}
		unsigned long memory = infoSample->sample_memory_avg / infoSample->countSample;
		memory_avg += memory;
		infoSample = infoSample->next;
	}

	infoSample = headSample;

	FILE* f = fopen("code.txt", "w");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in Create_home_page - The file did not open");
		exit(1);
	}

	sprintf(code, "<div>DLL count: %d</div><div> process count : %d </div><div>memory Avg : %d </div>", infoDLL->DLLcount, processCnt, memory_avg);
	fputs(code, f);
	fclose(f);

	LogEvent("Creates the code snippet");
	strcpy(Template, "home_Template.html");
	strcpy(newTemplate, "home page.html");
	strcpy(SEPERATOR, SEPERATOR_3);

	LogEvent("calls a Global_page_editing function");
	Global_page_editing(Template, newTemplate, SEPERATOR);

	f = fopen("code.txt", "w");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in Create_home_page - The file did not open");
		exit(1);
	}

	LogEvent("Creates the code snippet");
	while (infoSample != NULL)
	{
		sprintf(code, "<tr><td>%d</td><td><a href='sampel%d.html'>sampel %d.html</a></td><td>%d</td><td>%d</td></tr>", infoSample->id_sample, infoSample->id_sample, infoSample->id_sample, infoSample->DLL_Cnt, infoSample->sample_memory_avg);

		fputs(code, f);

		infoSample = infoSample->next;
	}

	fclose(f);
	strcpy(Template, "home page.html");
	strcpy(newTemplate, "home page.html");
	strcpy(SEPERATOR, SEPERATOR_1);

	LogEvent("calls a Global_page_editing function");
	Global_page_editing(Template, newTemplate, SEPERATOR);

	f = fopen("code.txt", "w");
	if (!f)
	{
		LogError(strerror(GetLastError()));
		printf("error in Create_home_page - The file did not open");
		exit(1);
	}

	LogEvent("Creates the code snippet");
	while (infoDLL != NULL)
	{
		sprintf(code, "<tr><td>%s</td><td><a href='DLL%d.html'>DLL %d.html</a></td></tr>", infoDLL->DLLname, infoDLL->DLLid, infoDLL->DLLid);

		fputs(code, f);

		infoDLL = infoDLL->next;
	}

	fclose(f);
	strcpy(Template, "home page.html");
	strcpy(newTemplate, "home page.html");
	strcpy(SEPERATOR, SEPERATOR_2);

	LogEvent("calls a Global_page_editing function");
	Global_page_editing(Template, newTemplate, SEPERATOR);

}