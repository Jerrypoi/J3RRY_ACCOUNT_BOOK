#include "utilities.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * 获取当前系统时间，并以指定格式返回
 */
const char* getSystemDate()
{
	char* result = malloc(100 * sizeof(char));
	if (result == NULL)
		return "1900-1-1";
	time_t t = time(NULL);
	const struct tm tm = *localtime(&t);
	sprintf(result, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	return result;
}

void trim(char* s) {
	char* p = s;
	int l = strlen(p);

	while (isspace(p[l - 1])) p[--l] = 0;
	while (*p && isspace(*p)) ++p, --l;

	memmove(s, p, l + 1);
}
