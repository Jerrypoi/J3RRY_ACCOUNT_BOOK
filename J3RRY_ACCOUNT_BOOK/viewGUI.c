/**
 * Warning:
 * This file is not completed.
 * DO NOT use any method from this file.
 */
#include "viewGUI.h"
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "UserInteraction.h"
#define   NR(x)   (sizeof(x)/sizeof(x[0]+0))
#define TITLE "J3RRY ACCOUNT BOOK"
int getXPosForString(char * str)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	const int columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	return (columns - strlen(str)) / 2;
	
}
bool ask_for_if_retry(HANDLE hout,char* err_msg);
void show_menu(HANDLE hOut, char* title_msg, char** menu, int size, int high_light_index);
int listen_for_user_input(int* index, int size);
CONSOLE_CURSOR_INFO cci;
COORD pos = { 0,0 };
void login_GUI(HANDLE hout);
void ACCOUNT_BOOK_GUI_MAIN_LOOP()
{
	char* options[] = {
		"LOG IN",
		"SIGN UP",
		"SHOW RECORD",
		"RECORD",
		"IMPORT DATA",
		"EXPORT DATA",
		"QUIT",
	};
	int i;
	int ret;
	int index = 0;
	HANDLE hout;
	SetConsoleTitleA(TITLE);
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hout, &cci);
	cci.dwSize = 1;
	cci.bVisible = false;
	SetConsoleCursorInfo(hout, &cci);

	while(1)
	{
		show_menu(hout, TITLE, options, NR(options), index);
		ret = listen_for_user_input(&index, NR(options));
		if (ret == ESC)
			return;

		if (ret == ENTER)
		{
			switch(index)
			{
			case 0: login_GUI(hout); // ��¼����
			case 1: break; // ע�ᴦ��
			case 2: break; // ��ʾ����
			case 3: break; // ��¼����
			case 4: break; // ��������
			case 5: break; // ��������
			default:break;
			}
		}
	}
}

void login_GUI(HANDLE hout)
{
	char* const msg[] = { "NAME: ", "PASSWORD: ","SUBMIT"};

	char name[100] = { 0 };
	char password[100] = { 0 };
	char* menu[3];
	for (int i = 0; i < 3; i++)
	{
		menu[i] = (char*)malloc(sizeof(char) * 200);
		for (int j = 0; j < 200; j++)
			menu[i][j] = 0; // set menu to 0
	}
	int index = 0;
	int input;
	int index_to_password = 0;
	int index_to_name = 0;
	strcpy(menu[0], msg[0]);
	strcpy(menu[1], msg[1]);
	strcpy(menu[2], msg[2]);
	while (1)
	{
		show_menu(hout, TITLE, &menu, NR(menu), index);
		input = listen_for_user_input(&index, NR(menu));
		if (input == ENTER && index == 2)
		{
			user_id = login(name, password);
			if (user_id == -1)
			{
				bool do_retry = ask_for_if_retry(hout, "Your name and password do not match!");
				if (!do_retry)
				{
					for (int i = 0; i < 3; i++)
						free(menu[i]);
					return;
				}
				else
				{
					// re-init
					index = 0;
					strcpy(name, "");
					strcpy(password, "");
					index_to_password = 0;
					index_to_name = 0;
					memset(menu[0], 0, sizeof(menu[0]));
					memset(menu[1], 0, sizeof(menu[1]));
					memset(menu[2], 0, sizeof(menu[2]));
					memset(name, 0, sizeof(name));
					memset(password, 0, sizeof(password));
					strcpy(menu[0], msg[0]);
					strcpy(menu[1], msg[1]);
					strcpy(menu[2], msg[2]);
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
					free(menu[i]);
				return;
			}
		}
		else if (input == BACKSPACE)
		{
			if (index == 0 && index_to_name > 0)
			{
				name[index_to_name--] = '\0';
				menu[index][strlen(menu[index]) - 1] = '\0';
			}
			if (index == 1 && index_to_password > 0)
			{
				password[index_to_password--] = '\0';
				menu[index][strlen(menu[index]) - 1] = '\0';
			}
		}
		else if(!isspace(input) && input != 0 && isascii(input))
		{
			if (index == 0)
			{
				name[index_to_name + 1] = '\0';
				name[index_to_name++] = (char)input;
				menu[index][strlen(menu[index]) + 1] = '\0';
				menu[index][strlen(menu[index])] = (char)input;
			}
			if (index == 1)
			{
				password[index_to_password + 1] = '\0';
				password[index_to_password++] = (char)input;
				menu[index][strlen(menu[index]) + 1] = '\0'; 
				menu[index][strlen(menu[index])] = '*'; // ���벻����
			}
		}

		
	}
}
bool ask_for_if_retry(HANDLE hout, char* err_msg)
{
	char* const options[] = { "YES","NO" };
	SetConsoleTextAttribute(hout, FOREGROUND_GREEN | 0x8);
	if (err_msg == NULL)
		err_msg = TITLE;
	char* prompt = (char*)malloc(sizeof(char) * 100);
	strcpy(prompt, err_msg);
	strcat(prompt, " Would you like retry?");
	int index = 0;
	while (1)
	{
		show_menu(hout, prompt, options, NR(options), index);
		int input = listen_for_user_input(&index, NR(options));
		if (input == ENTER)
		{
			if (index == 0) // user chose yes
			{
				free(prompt);
				return true;
			}
			else
			{
				free(prompt);
				return false;
			}
		}

	}

}
int listen_for_user_input(int *index,int size)
{
	const int ch = _getch();
	switch (ch)
	{
		//�� 
		//���ѡ���ϣ���ô��������ƶ� 
	case UP: if (*index > 0)  *index -= 1;  break;
		//�� 
		//���ѡ���£���ô��������ƶ� 
	case DOWN:if (*index < size - 1)  *index += 1;  break;
		//�� 
	case LEFT:
	case 97:return 0;
		//�� 
	case RIGHT:return 0;
		//�س� 
	case ENTER: return ENTER;
		//ESC
	case ESC: return ESC;
	case BACKSPACE: return BACKSPACE;
	default: return ch;
	}
	return 0;
}
void show_menu(HANDLE hOut, char *title_msg , char* menu[], int size, int high_light_index)
{
	
	int y_index = 4;
	int i;
	system("cls");
	if(title_msg != NULL)
	{
		// ��ӡ����
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | 0x8);
		pos.X = getXPosForString(title_msg);
		pos.Y = 2;
		//������ʾ������̨�ն˵ľ���λ�� 
		SetConsoleCursorPosition(hOut, pos);
		//����printf�ڿ���̨��Ӧ��λ������� 
		printf("%s", title_msg);
	}
	for (i = 0; i < size; i++)
	{
		//���i==high light index��ʾ�ڵ�ǰѡ���λ�ã�Ĭ�ϳ�ʼ����ʾ�ǵ�һ���ʾΪ��ɫ��
		//���������°���ѡ���ʱ�򣬹����ƶ���Ҳ�Ϳ������б�ѡ������� 
		if (i == high_light_index)
		{
			// ������ʾ���ı�����ɫ 
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | 0x8);
			// ��ʼ������̨��ʾ��X,Y������� 
			pos.X = getXPosForString(menu[i]);
			pos.Y = y_index++;
			//���ù������
			SetConsoleCursorPosition(hOut, pos);
			printf("%s", menu[i]);
		}
		//������ʾΪ��ɫ 
		else
		{
			//��ɫ 
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			pos.X = getXPosForString(menu[i]);
			pos.Y = y_index++;
			//���ù������
			SetConsoleCursorPosition(hOut, pos);    //���ù������
			printf("%s", menu[i]);
		}
	}
	//ˢ�±�׼��������� 
	fflush(stdout);
}
