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
	if (buffer == NULL) // 创建 buffer 失败，返回空指针
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
			putchar('\b'); // 回退一格
			putchar(' '); // 输出一个空格顶掉 *
			putchar('\b'); // 再回退一个回到之前输出的空格之前。
		}
	}
	buffer[index] = '\0';
	return buffer;
}

/**
 * 检查用户输入的邮箱地址是否为一个合法的邮箱地址
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
 * 检查用户输入的日期是否合法
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
	// 将用户输入的日期分别按年月日读出来
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
	// 将读出来的年月日转换成 int 形进行比较。
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
