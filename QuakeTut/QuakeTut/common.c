#include "winquake.h"
#include "quakedef.h"

int com_argc = 1;
char *com_argv[MAX_NUM_ARGVS + 1];

int32 COM_CheckParm(int8 *parm) {
	for (int32 i = 1; i < com_argc; i++) {
		if (!Q_strcmp(parm, com_argv[i])) {
			return i;
		}
	}
	return 0;
}

void COM_ParseCmdLine(uint8 *lpCmdLine) {
	// Set initial pointer to be an empty string
	com_argv[0] = "";

	// Iterate over arguments until we hit the max limit
	while (*lpCmdLine && com_argc < MAX_NUM_ARGVS) {

		// If arg pointer is a non printable string (like a space), skip
		while (*lpCmdLine && ((*lpCmdLine <= 32) && (*lpCmdLine > 126)))
			lpCmdLine++;

		// If we have a value
		if (*lpCmdLine) {

			// Set string pointer into array of string pointers and iterate
			com_argv[com_argc] = lpCmdLine;
			com_argc++;

			while (*lpCmdLine && ((*lpCmdLine > 32) && (*lpCmdLine <= 126)))
				lpCmdLine++;

			if (*lpCmdLine) {
				*lpCmdLine = 0;
				lpCmdLine++;
			}
		}
	}
}
