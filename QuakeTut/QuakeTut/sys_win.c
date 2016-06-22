#include <stdint.h>
#include <Windows.h>

typedef int8_t   int8;
typedef uint8_t  uint8;
typedef int32_t  int32;
typedef uint32_t uint32;

#define MAX_NUM_ARGVS 50

int argc = 1;
char *largv[MAX_NUM_ARGVS+1];


int32 Q_strcmp(uint8 *s1, uint8 *s2) {

	while (*s1 == *s2) {

		if (!*s1) return 0;;
		++s1;
		++s2;
	}
	
	return ((*s1 < *s2) ? -1 : 1);
}

/*
	Handle hex, pos or negative ints.
	e.g. -52, 13465, 0x21463
*/
int32 Q_atoi(const char *str) {
	int32 sign = 1;
	int32 val = 0;
	uint8 c;

	if (*str == '-') {
		sign = -1;
		str++;
	}

	// Hex
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {

		str += 2;
		while (1) {
			c = *str;
			str++;
			if (c >= '0' && c <= '9') {
				val = val * 16 + c - '0';
			}
			else if (c >= 'a' && c <= 'f') {
				val = val * 16 + c - 'a' + 10;
			}
			else if (c >= 'A' && c <= 'F') {
				val = val * 16 + c - 'A' + 10;
			}
			else {
				return val*sign;
			}
		}
	}

	// Decimal
	while (1) {
		c = *str;
		str++;
		if (c < '0' || c > '9')
			return sign * val;
		val = val * 10 + c - '0';
	}
}

int32 COM_CheckParm(int8 *parm) {
	for (int32 i = 1; i < argc; i++) {
		if (!Q_strcmp(parm, largv[i])) {
			return i;
		}
	}
	return 0;
}

int32 CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int32 nCmdShow) {

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

	int32 test  = COM_CheckParm("-setalpha");
	int32 value = Q_atoi(largv[test+1]);

	return 0;
}