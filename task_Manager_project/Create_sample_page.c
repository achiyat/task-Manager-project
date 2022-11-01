
#include "struct.h"

void Create_sample_page()
{
	// The function creates a piece of codeand adds the generated code to the existing code.
	// The generated code builds a table of the samples that shows all the data of the processes.
	char code[300];
	char SEPERATOR[10] = { '\0' };
	char Template[50] = { '\0' };
	char newTemplate[50] = { '\0' };
	time_t t3;
	struct tm* timeinfo;
	time(&t3);
	timeinfo = localtime(&t3);

	struct sample* infoSample = headSample;

	while (infoSample != NULL)
	{
		FILE* f = fopen("code.txt", "w");
		if (!f)
		{
			LogError(strerror(GetLastError()));
			printf("error in Create_sample_page - The file did not open");
			exit(1);
		}

		sprintf(code, "samples list number: %d at %d/%d/%d %d:%d:%d", infoSample->id_sample, timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
		fputs(code, f);
		fclose(f);

		// Editing the title
		strcpy(Template, "sampel_Template.html");
		sprintf(newTemplate, "sampel%d.html", infoSample->id_sample);
		strcpy(SEPERATOR, SEPERATOR_3);

		LogEvent("calls a Global_page_editing function");
		Global_page_editing(Template, newTemplate, SEPERATOR);

		struct process* infoProcess = infoSample->data_process;
		f = fopen("code.txt", "w");
		if (!f)
		{
			LogError(strerror(GetLastError()));
			printf("error in Create_sample_page - The file did not open");
			exit(1);
		}

		LogEvent("Creates the code snippet");
		while (infoProcess != NULL)
		{
			//  HTML_REPLACE
			sprintf(code, "<tr><td class='td1'>%s</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>", infoProcess->nameOFprocess, infoProcess->idOFprocess, infoProcess->PageFaultCount, infoProcess->WorkingSetSize, infoProcess->QuotaPagedPoolUsage, infoProcess->QuotaPeakPagedPoolUsage, infoProcess->PagefileUsage, infoProcess->countDLL);

			fputs(code, f);
			strcpy(code, "<td><select>");
			fputs(code, f);

			struct DLLofProcess* infoDLLofProcess = infoProcess->dataDLL_OFprocess;
			while (infoDLLofProcess != NULL)
			{
				sprintf(code, "<option>%s</option>", infoDLLofProcess->name_OF_DLL);
				fputs(code, f);
				infoDLLofProcess = infoDLLofProcess->next;
			}

			strcpy(code, "</select></td></tr>");
			fputs(code, f);

			infoProcess = infoProcess->next;

		}

		fclose(f);
		sprintf(Template, "sampel%d.html", infoSample->id_sample);
		sprintf(newTemplate, "sampel%d.html", infoSample->id_sample);
		strcpy(SEPERATOR, SEPERATOR_1);

		// The function will add the code section to the existing code.
		LogEvent("calls a Global_page_editing function");
		Global_page_editing(Template, newTemplate, SEPERATOR);

		infoSample = infoSample->next;
	}
}