#include "utilities.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

/**
 * ��ȡ��ǰϵͳʱ�䣬����ָ����ʽ����
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
 * ����һ���ַ���ǰ�������Ŀո񣬻��з�
 */
void trim(char* s) {
	char* p = s;
	int l = strlen(p);

	while (isspace(p[l - 1])) p[--l] = 0;
	while (*p && isspace(*p)) ++p, --l;

	memmove(s, p, l + 1);
}
/**
 * Read password ��ʾ�û��������룬���û������� * ����ʽ���ء�
 */
char* read_password(char* buffer)
{
	if (buffer == NULL) // �����������Ϊ�գ������µĿռ������
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
