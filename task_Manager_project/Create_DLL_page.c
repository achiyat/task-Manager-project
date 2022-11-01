
#include "struct.h"

void Create_DLL_page()
{
	// The function creates a piece of codeand adds the generated code to the existing code.
	// The generated code builds a DLLS table.
	char code[300];
	char SEPERATOR[10] = { '\0' };
	char Template[50] = { '\0' };
	char newTemplate[50] = { '\0' };

	struct UniqueDLL* infoDLL = headUniqueDLL;

	while (infoDLL != NULL)
	{
		FILE* f = fopen("code.txt", "w");
		if (!f)
		{
			LogError(strerror(GetLastError()));
			printf("error in Create_DLL_page - The file did not open");
			exit(1);
		}

		sprintf(code, "%d process user %s", infoDLL->processCount, infoDLL->DLLname);
		fputs(code, f);
		fclose(f);

		// Editing the title
		strcpy(Template, "DLL_Template.html");
		sprintf(newTemplate, "DLL%d.html", infoDLL->DLLid);
		strcpy(SEPERATOR, SEPERATOR_3);

		LogEvent("calls a Global_page_editing function");
		Global_page_editing(Template, newTemplate, SEPERATOR);

		struct processOFdll* infoProcess = infoDLL->dataProcess_OFdll;

		f = fopen("code.txt", "w");
		if (!f)
		{
			LogError(strerror(GetLastError()));
			printf("error in Create_DLL_page - The file did not open");
			exit(1);
		}

		LogEvent("Creates the code snippet");
		while (infoProcess != NULL)
		{
			//  HTML_REPLACE
			sprintf(code, "<tr><td>%s</td><td>%d</td></tr>", infoProcess->nameOFprocess, infoProcess->idOFprocess);
			fputs(code, f);

			infoProcess = infoProcess->next;

		}

		fclose(f);
		sprintf(Template, "DLL%d.html", infoDLL->DLLid);
		sprintf(newTemplate, "DLL%d.html", infoDLL->DLLid);
		strcpy(SEPERATOR, SEPERATOR_1);

		// The function will add the code section to the existing code.
		LogEvent("calls a Global_page_editing function");
		Global_page_editing(Template, newTemplate, SEPERATOR);

		infoDLL = infoDLL->next;

	}
}