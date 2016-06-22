#pragma once

#define MAX_NUM_ARGVS 50

extern int com_argc;
extern char *com_argv[MAX_NUM_ARGVS + 1];

int32 COM_CheckParm(int8 *parm);
void COM_ParseCmdLine(uint8 *lpCmdLine);