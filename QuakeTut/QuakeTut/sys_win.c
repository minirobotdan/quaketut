#include <Windows.h>

#define MAX_NUM_ARGVS 50

int argc = 1;
char *largv[MAX_NUM_ARGVS];

/*
	Returns the index of a parameter in the largv array.
*/
int COM_CheckParm(char *parm) {
	for (int i = 1; i < argc; i++) {
		if (!strcmp(parm, largv[i])) {
			return i;
		}
	}
	return 0;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// Set initial pointer to be an empty string
	largv[0] = "";

	// Iterate over arguments until we hit the max limit
	while (*lpCmdLine && argc < MAX_NUM_ARGVS) {

		// If arg pointer is a non printable string (like a space), skip
		while (*lpCmdLine && ((*lpCmdLine <= 32) && (*lpCmdLine > 126)))
			lpCmdLine++;

		// If we have a value
		if (*lpCmdLine) {

			// Set string pointer into array of string pointers and iterate
			largv[argc] = lpCmdLine;
			argc++;

			while (*lpCmdLine && ((*lpCmdLine > 32) &&( *lpCmdLine <= 126))) 
				lpCmdLine++;

			if (*lpCmdLine) {
				*lpCmdLine = 0;
				lpCmdLine++;
			}
		}
	}

	largv[argc] = "";

	int test  = COM_CheckParm("-setalpha");
	int value = (int)(*largv[2]);

	return 0;
}