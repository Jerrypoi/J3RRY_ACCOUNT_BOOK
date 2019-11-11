#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "print.h"
#include <stdbool.h>
#include <conio.h>
#include "user_login.h"
VOID WINAPI SetConsoleColors(WORD attribs) {
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFOEX cbi;
	cbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
	GetConsoleScreenBufferInfoEx(hOutput, &cbi);
	cbi.wAttributes = attribs;
	SetConsoleScreenBufferInfoEx(hOutput, &cbi);
}
void ACCOUNT_BOOK_MAIN_LOOP()
{
	//SetConsoleColors(  FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("欢迎使用杰瑞记账本\n");
	printRed("Enter 'h' to display help menu\n");
	char line[1024 * 10] = { 0 };
	char prompt[] = "account_book> ";
	while (1)
	{
		printf("%s", prompt);
		char* res = gets_s(line, sizeof(line));
		if (line == NULL || res == NULL) // 使用 res 判断是否为 EOF
		{
			printf("LINE = NULL");
		}
		else if (strcmp(line,"h") == 0 || strcmp(line,"help") == 0)
		{
			printHelpMessage();
		}
		else if(strcmp(line,"login") == 0)
		{
			loginInteractions();
		}
		else if(strcmp(line,"sign up") == 0 || strcmp(line,"signup") == 0)
		{
			signUpInteractions();
		}
		else if(strcmp(line,"search") == 0 || strcmp(line, "show") == 0)
		{
			getDataInteractions();
		}
		else if(strcmp(line,"record") == 0)
		{
			recordDataInteractions();
		}
		else if (strcmp(line, "id") == 0)
		{
			printf("Your user id is: %d\n", user_id);

		}
		else if(strcmp(line,"q") == 0 || strcmp(line,"quit") == 0)
		{
			printf("Bye\n");
			break;
		}
		else
		{
			printRed(line);
			printRed(" is not recognizable, please enter 'help' to find out viable commands\n");
		}

	}
}

void printHelpMessage()
{
	char spaces[] = "\t\t\t";
	printf("help(h)%sshow this menu.\n",spaces);
	printf("login%slog into your account.\n", spaces);
	printf("sign up%ssign up for a new account.\n", spaces);
	printf("show%sshow your account.\n", spaces);
	printf("record%srecord a new transaction.\n", spaces);
	printf("quit(q)%squit this program.\n", spaces);
}

void loginInteractions()
{
	bool login_sucess = false;
	char prompt[] = "account_book> ";
	char user_name[64];
	char password[64];
	while(login_sucess == false)
	{
		int index_to_password = 0;
		
		printf("Please enter your name and password:\n");
		printf("User name> ");
		scanf("%s", user_name);
		getchar();
		printf("Password> ");
		char ch;
		while ((ch = _getch()) != '\r')
		{
			if (ch != 8)
			{
				password[index_to_password++] = ch;
				putchar('*');
			}
			else if(index_to_password != 0)
			{
				
				index_to_password--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
		password[index_to_password] = '\0';
		printf("\n");

		user_id = login(user_name, password);
		if (user_id == -1)
		{
			char buffer[1024] = { 0 };
			printRed("You entered username or password wrong!\n");
			printf("Would you like to retry(y or n):");
			gets_s(buffer, sizeof(buffer));
			while (strcmp(buffer,"y") != 0 && strcmp(buffer,"n") != 0 && strcmp(buffer, "yes") != 0 && strcmp(buffer, "no") != 0)
			{
				printf("Please input y or n: ");
				gets_s(buffer, sizeof(buffer));
			}
			if (strcmp(buffer,"n") == 0 || strcmp(buffer,"no") == 0)
			{
				return;
			}
			
		}
		else
		{
			login_sucess = true;
			printf("Successfully logged in as %s\n",user_name);
		}
	}
	
}

void signUpInteractions()
{
	char user_name[100] = { 0 };
	char password[100] = { 0 };
	char password_confirm[100] = { 0 };
	char email[100] = { 0 };
	bool success = false;
	while (success == false)
	{
		printf("Please enter your name:\nUser Name> ");
		scanf("%s", user_name);
		printf("Password> ");
		int index_to_password = 0;
		char ch;
		while ((ch = _getch()) != '\r')
		{
			if (ch != 8)
			{
				password[index_to_password++] = ch;
				putchar('*');
			}
			else if (index_to_password != 0)
			{

				index_to_password--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
		password[index_to_password] = '\0';
		printf("\n");
		printf("Confirm Password> ");
		index_to_password = 0;
		while ((ch = _getch()) != '\r')
		{
			if (ch != 8)
			{
				password_confirm[index_to_password++] = ch;
				putchar('*');
			}
			else if (index_to_password != 0)
			{

				index_to_password--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
		password_confirm[index_to_password] = '\0';
		printf("\n");
		printf("Email> ");
		scanf("%s", email);
		getchar();
		// printf("name:%s\npasswd:%s\npassconfirm:%s\nemail:%s\n", user_name, password, password_confirm, email);
		user_id = sign_up(user_name, password, password_confirm, email);
		if (user_id == -1)
		{
			char buffer[1024] = { 0 };
			printf("Would you like to retry(y or n):");
			gets_s(buffer, sizeof(buffer));
			while (strcmp(buffer, "y") != 0 && strcmp(buffer, "n") != 0 && strcmp(buffer, "yes") != 0 && strcmp(buffer, "no") != 0)
			{
				printf("Please input y or n: ");
				gets_s(buffer, sizeof(buffer));
			}
			if (strcmp(buffer, "n") == 0 || strcmp(buffer, "no") == 0)
			{
				return;
			}

		}
		else
		{
			success = true;
			printf("Now signed in as %s\n", user_name);
		}
	}
}

void getDataInteractions()
{
	
}

void recordDataInteractions()
{
	
}
