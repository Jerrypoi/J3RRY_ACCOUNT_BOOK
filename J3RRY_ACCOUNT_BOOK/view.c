#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "print.h"
#include <stdbool.h>
#include <conio.h>
#include "user_login.h"
#include "process_record.h"
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
		else if (strcmp(line,"h") == 0 || strcmp(line,"help") == 0) // 输出帮助菜单
		{
			printHelpMessage();
		}
		else if(strcmp(line,"login") == 0 || strcmp(line, "log in") == 0) // 登录功能
		{
			loginInteractions();
		}
		else if(strcmp(line,"sign up") == 0 || strcmp(line,"signup") == 0) // 注册功能
		{
			signUpInteractions();
		}
		else if(strcmp(line,"search") == 0 || strcmp(line, "show") == 0) // 显示数据
		{
			getDataInteractions();
		}
		else if(strcmp(line,"record") == 0) // 记录交易
		{
			recordDataInteractions();
		}
		else if(strcmp(line,"import") == 0) // 导出数据
		{
			importDataInteractions();
		}
		else if(strcmp(line,"export") == 0) // 导入数据
		{
			exportDataInteractions();
		}
		else if (strcmp(line, "id") == 0) // 内部使用，获取当前登录id
		{
			printf("Your user id is: %d\n", user_id);

		}
		else if(strcmp(line,"q") == 0 || strcmp(line,"quit") == 0)  // 退出程序
		{
			printf("Bye\n");
			break;
		}
		else if(strcmp(line," ") == 0 || strcmp(line,"\n") == 0 || strcmp(line,"") == 0)
		{
			
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
/**
 * 登录交互逻辑
 */
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
/**
 * 注册交互逻辑
 */
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
		user_id = user_sign_up(user_name, password, password_confirm, email);
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
/**
 * SQLITE 回调函数，仅限本文件中使用
 */
static int callback_amount_and_classid(void* list, int argc, char** argv, char** azColName)
{
	amount_and_classid* aac = (amount_and_classid*)malloc(sizeof(amount_and_classid));
	if (!aac)
		return -1;
	aac->amount = atof(argv[0]);
	aac->class_id = strtol(argv[1], NULL, 10);
	llist_push((llist*)list, aac);
	return 0;
}
void getDataInteractions()
{
	if (user_id == -1)
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
	char group[100] = { 0 };
	char spaces[] = "\t\t\t";
	printf("please specify how to group your data:\n");
	printf("all%sShow all your transactions, don't group.\n", spaces);
	printf("type%sGroup your transactions by type(income or expenditure)\n",spaces);
	printf("class%sGroup your transactions by its classes\n",spaces);
	scanf("%s", group);
	while(strcmp(group,"all") != 0 && strcmp(group,"type") != 0 && strcmp(group,"class") != 0)
	{
		printRed("Please enter all, type or class: ");
		scanf("%s", group);
	}
	llist* transactions = getTransactionByUserId(user_id);
	if (strcmp(group,"all") == 0)
	{
		struct node* head = *transactions;
		while (head->data != NULL)
		{
			const transaction t = *(transaction*)head->data;
			printRed(t.type == false ? "Income\n" : "Expenditure\n");
			transaction_class* tc = getTransactionClassByID(db, t.class_id);
			printf("Class: %s", tc == NULL || tc->class_name ==NULL ? "NULL" : tc->class_name);
			printf("\nAmount: %.2lf\n", t.amount);
			printf("Date: %s\n", t.transaction_date);

			printf("\n");
			head = head->next;
			if (head == NULL)
				break;
		}
	}
	else if (strcmp(group, "type") == 0)
	{
		double in_total = 0;
		double out_total = 0;
		struct node* head = *transactions;
		while (head->data != NULL)
		{
			const transaction t = *(transaction*)head->data;
			if (t.type == false)
			{
				in_total += t.amount;
			}
			else
			{
				out_total += t.amount;
			}
			head = head->next;
			if (head == NULL)
				break;
		}
		printf("Your income is %.2lf yuan and your expenditure is %.2lf yuan.\n", in_total, out_total);
		printf("Your currently have %.2lf yuan in your account\n", in_total - out_total);
	}
	else
	{
		printf("\n");
		llist* aac_list = llist_create(NULL);
		char sql[1024] = { 0 };
		sprintf(sql, "select sum(case when type then amount else -amount end), class_id from transactions where user_id = %d group by class_id;", user_id);
		sqlite3_exec(db, sql, callback_amount_and_classid, aac_list, NULL);
		struct node* head = *aac_list;
		while (head->data != NULL)
		{
			const amount_and_classid aac = *(amount_and_classid*)head->data;
			transaction_class* tc = getTransactionClassByID(db, aac.class_id);
			printf(tc == NULL || tc->class_name == NULL ? "NULL" : tc->class_name);
			printf(": %.2lf\n", aac.amount);
			head = head->next;
			if (head == NULL)
				break;
		}
	}
}

void recordDataInteractions()
{
	char type[100] = { 0 };
	bool type_id = false;
	double amount = 0;
	char buffer[100] = { 0 };
	char class_name[1024] = { 0 };
	char date[1024] = { 0 };
	if (user_id == -1)
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
	printf("Please enter transaction type(income or expenditure): ");
	scanf("%s", type);
	while (strcmp(type,"income") != 0 && strcmp(type,"expenditure")!=0 && strcmp(type,"i") != 0 && strcmp(type,"e") != 0)
	{
		printf("Please enter income or expenditure (or i or e): ");
		scanf("%s", type);
	}
	if (strcmp(type,"i") == 0 || strcmp(type,"income") == 0)
	{
		type_id = false;
	}
	else
	{
		type_id = true;
	}
	printf("Please enter class name: ");
	scanf("%s", class_name);
	int class_id = find_transaction_class(class_name);
	if (class_id == -1)
	{
		printf("The class does not exist, would like to create it?(y or n): ");
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
		else
		{
			class_id = create_transaction_class(class_name);
		}
	}
	printf("Please enter amount: ");
	scanf("%lf", &amount);
	while (amount < 0)
	{
		printf("Amount should be greater than 0, please enter again: ");
		scanf("%lf", &amount);
	}
	printf("Please enter transaction date(enter 'today' for today): ");
	scanf("%s", date);
	if (strcmp(date,"today") == 0)
	{
		record_transaction(type_id, amount, class_id, user_id, NULL);
	}
	else
	{
		record_transaction(type_id, amount, class_id, user_id, date);
	}
	printf("%lf\n%d\n%s\n", amount, class_id, date);
	getchar();
}

void importDataInteractions()
{
	if (user_id == -1)
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
}

void exportDataInteractions()
{
	if (user_id == -1)
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
}
