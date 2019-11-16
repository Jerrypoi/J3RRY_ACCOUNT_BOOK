#include "utilities.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

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
/**
 * 消除一个字符串前面与后面的空格，换行符
 */
void trim(char* s) {
	char* p = s;
	int l = strlen(p);

	while (isspace(p[l - 1])) p[--l] = 0;
	while (*p && isspace(*p)) ++p, --l;

	memmove(s, p, l + 1);
}
/**
 * Read password 提示用户输入密码，将用户输入以 * 的形式返回。
 */
char* read_password(char* buffer)
{
	if (buffer == NULL) // 如果传进来的为空，开辟新的空间来存放
	{
		buffer = (char*)malloc(sizeof(char) * 100);
	}
	char ch;
	int index = 0;
	while ((ch = (char)_getch()) != '\r')
	{
		if (ch != 8)
		{
			buffer[index++] = ch;
			putchar('*');
		}
		else if (index != 0)
		{

			index--;
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
	}
	buffer[index] = '\0';


	return buffer;
}
