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
	if (buffer == NULL) // ���� buffer ʧ�ܣ����ؿ�ָ��
		return NULL;
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
			putchar('\b'); // ����һ��
			putchar(' '); // ���һ���ո񶥵� *
			putchar('\b'); // �ٻ���һ���ص�֮ǰ����Ŀո�֮ǰ��
		}
	}
	buffer[index] = '\0';
	return buffer;
}

/**
 * ����û�����������ַ�Ƿ�Ϊһ���Ϸ��������ַ
 */
int check_valid_email(char* email)
{
	if (email == NULL)
		return 0;
	char* p_str = strchr(email, '@');
	if (p_str == NULL)
		return 0;
	p_str = strchr(p_str, '.');
	if (p_str == NULL)
		return 0;
	return 1;
	
}
/**
 * ����û�����������Ƿ�Ϸ�
 */
int check_valid_date(const char* date)
{
	if (date == NULL)
		return 0;
	char year[10] = { 0 };
	char month[10] = { 0 };
	char day[10] = { 0 };
	int index_to_date = 0;
	int index_to_others = 0;
	// ���û���������ڷֱ������ն�����
	while(date[index_to_date] != '-')
	{
		year[index_to_others++] = date[index_to_date++];
	}
	index_to_others = 0;
	index_to_date++;
	while (date[index_to_date] != '-')
	{
		month[index_to_others++] = date[index_to_date++];
	}
	index_to_date++;
	index_to_others = 0;
	while (date[index_to_date] != '\0')
	{
		day[index_to_others++] = date[index_to_date++];
	}
	// ����������������ת���� int �ν��бȽϡ�
	const int i_year = atoi(year);
	const int i_month = atoi(month);
	const int i_day = atoi(day);
	if (i_year < 1800 || i_year > 2200)
		return 0;
	if (i_month <= 0 || i_month > 12)
		return 0;
	if (i_day <= 0 || i_day > 31)
		return 0;
	return 1;
}
