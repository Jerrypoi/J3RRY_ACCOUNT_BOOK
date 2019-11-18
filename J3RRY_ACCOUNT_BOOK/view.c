#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "print.h"
#include <stdbool.h>
#include <conio.h>
#include "UserInteraction.h"
#include "ProcessRecord.h"
#include "utilities.h"
#pragma warning( disable : 6031) // Ignore specific warning message from visual studio.
// 设置控制台的颜色
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
	char line[1024 * 10] = { 0 }; // 读入缓冲为 10KB
	char prompt[] = "account_book> ";
	bool print_prompt = true;
	while (1)
	{
		if (print_prompt)
			printf("%s", prompt);
		else
			print_prompt = true;
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
		else if (strcmp(line, "logout") == 0 || strcmp(line,"log out") == 0) // 导出数据
		{
			logoutInteractions();
		}
		else if(strcmp(line,"search") == 0 || strcmp(line, "show") == 0) // 显示数据
		{
			getDataInteractions();
		}
		else if(strcmp(line,"record") == 0) // 记录交易
		{
			recordDataInteractions();
		}
		else if(strcmp(line,"import") == 0) // 导入数据
		{
			importDataInteractions();
		}
		else if(strcmp(line,"export") == 0) // 导出数据
		{
			exportDataInteractions();
		}
		else if (strcmp(line, "id") == 0) // 内部调试使用，获取当前登录id
		{
			printf("Your user id is: %d\n", user_id);
		}
		else if(strcmp(line,"q") == 0 || strcmp(line,"quit") == 0)  // 退出程序
		{
			printf("Bye\n");
			break;
		}
		else if(strcmp(line," ") == 0 || strcmp(line,"\n") == 0)
		{
			
		}
		else if(strcmp(line, "") == 0)
		{
			print_prompt = false; // 防止出现重复输出两个提示符的情况
		}
		else
		{
			printRed(line);
			printRed(" is not recognizable, please enter 'help' to find out viable commands\n");
		}

	}
}
/**
 * 输出提示信息
 */
void printHelpMessage()
{
	char spaces[] = "\t\t\t";
	printf("help(h)%sshow this menu.\n",spaces);
	printf("login%slog into your account.\n", spaces);
	printf("sign up%ssign up for a new account.\n", spaces);
	printf("log out%slog out your current account.\n", spaces);
	printf("show%sshow your account.\n", spaces);
	printf("record%srecord a new transaction.\n", spaces);
	printf("import%simport data from outside file\n", spaces);
	printf("export%sexport data to outside file\n", spaces);
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
		printf("Please enter your name and password:\n");
		printf("User name> ");
		scanf("%s", user_name);
		getchar();
		printf("Password> ");
		read_password(password); // 通过特殊方式读取用户输入的密码，使用户输入的密码不明文显示
		printf("\n");

		user_id = login(user_name, password); // 尝试进行登录，user_id 为定义在 user_login 的全局变量
		if (user_id == -1) // id = -1 则说明登录失败
		{
			const bool do_retry = ask_for_retry("Your user name or password is wrong.");
			if (!do_retry)
			{
				return;
			}
		}
		
		else
		{
			login_sucess = true;
			printf("Successfully logged in as %s\n",user_name);
			printf("\n");
		}
	}
	
}

void logoutInteractions()
{
	if (user_id == -1)
		printRed("You're not logged in!\n");
	else
	{
		user_id = -1;
		printf("You've logged out your current account\n");
		printf("\n");
	}
	return;
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
		read_password(password); // 读取用户输入的密码
		printf("\n");
		printf("Confirm Password> ");
		read_password(password_confirm);  // 读取用户输入的确认密码
		printf("\n");
		printf("Email> ");
		scanf("%s", email);
		getchar();
		while (!check_valid_email(email))
		{
			const bool do_retry = ask_for_retry("Your email address is not valid.");
			if (!do_retry)
				return;	
			printf("Email> ");
			scanf("%s", email);
		}
		user_id = user_sign_up(user_name, password, password_confirm, email); // 尝试进行注册
		if (user_id == -1)  // user_id = -1 说明注册失败
		{
			const bool do_retry = ask_for_retry(NULL);
			if (!do_retry)
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
/**
 * 显示数据
 */
void getDataInteractions()
{
	if (user_id == -1) // 显示数据前必须登录
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
	char group[100] = { 0 };
	char spaces[] = "\t\t\t";
	// 询问用户已哪种方式展示数据，目前支持三种：
	// 1. 展示每一条交易记录
	// 2. 分别展示收入与支出的总额，eg，收入 100 元，支出 20元。
	// 3. 按照各个收支类别展示数据，eg， 微信收入100元，支付宝收入-10 元，现金收入 20 元
	printf("\n");
	printf("please specify how to group your data:\n");
	printf("all%sShow all your transactions, don't group.\n", spaces);
	printf("type%sGroup your transactions by type(income or expenditure)\n",spaces);
	printf("class%sGroup your transactions by its classes\n",spaces);
	printf("\nMethod to group data: ");
	scanf("%s", group);
	while(strcmp(group,"all") != 0 && strcmp(group,"type") != 0 && strcmp(group,"class") != 0) // 如果用户输入不满足要求
	{
		printRed("Please enter all, type or class: ");
		scanf("%s", group);
	}
	llist* transactions = getTransactionByUserId(user_id);
	if (strcmp(group,"all") == 0)
	{
		printf("\n");
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
		printf("\n");
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
	else // 按类别展示数据，由于如果使用链表做太麻烦，就写了一个sql和对应的 struct进行存储
	{
		printf("\n");
		llist* aac_list = llist_create(NULL);
		char sql[1024] = { 0 };
		sprintf(sql, "select sum(case when type then -amount else amount end), class_id from transactions where user_id = %d group by class_id;", user_id);
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
/**
 * 记录交易数据
 */
void recordDataInteractions()
{
	if (user_id == -1) // 要登录后才能记录交易数据
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
	char type[100] = { 0 };
	bool type_id = false;
	double amount = 0;
	char buffer[100] = { 0 };
	char class_name[1024] = { 0 };
	char date[1024] = { 0 };
	printf("Please enter transaction type(income or expenditure): "); // 首先输入交易类型，是收入还是支出
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
	// 提示用户输入交易类别
	printf("Please enter class name: ");
	while (strcmp(class_name,"") == 0) // 由于前面有换行符没有读到，使用这种方法防止读入空串
	{
		gets_s(class_name, sizeof(class_name));
	}
	int class_id = find_transaction_class(class_name);
	if (class_id == -1) // 如果没有在数据库中找到对应的交易类别，询问用户是否创建一个。
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
			class_id = create_transaction_class(class_name); // 创建新的交易类别
		}
	}
	// 输入金额
	printf("Please enter amount: ");
	scanf("%lf", &amount);
	// 由于数据库设计要求，输入的金额应当大于0
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
		while (!check_valid_date(date))
		{
			const bool do_retry = ask_for_retry("Your format for date is wrong.");
			if (!do_retry)
				return;
			printf("Please enter transaction date(format: YYYY-MM-DD): ");
			scanf("%s", date);
		}
		record_transaction(type_id, amount, class_id, user_id, date);
	}
	printf("Recorded successfully!\n");
	getchar();
}
/**
 * 将交易信息写入文件
 */
void exportDataInteractions()
{
	if (user_id == -1)
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
	char filename[100] = { 0 };
	char buffer[100] = { 0 };
	printf("Please enter the name of the where you want to store your data: ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "w");
	while (!file) // 判断文件是否合法，若不合法则让用户重新输入
	{
		const bool do_retry = ask_for_retry("The filename you entered is not valid.");
		if (!do_retry)
		{
			return;
		}
		printf("Please enter the name of the sql file: ");
		scanf("%s", filename);
		file = fopen(filename, 'w');
	}
	// 记录当前用户数据
	user* current_u = getUserById(db, user_id);
	fprintf(file, "%s\n%s\n%s\n", current_u->name, current_u->password, current_u->email_addr);
	llist* transactions = getTransactionByUserId(user_id);
	struct node* head = *transactions;
	while (head->data != NULL)
	{
		// 记录交易类型，交易金额，交易类别，交易日期
		const transaction t = *(transaction*)head->data;
		transaction_class* tc = getTransactionClassByID(db, t.class_id); // 因为我们的交易类别本来只有 id，所以要用id获取它的名字
		fprintf(file, "%d\n%.2lf\n%s\n%s\n", t.type, t.amount, tc->class_name, t.transaction_date);

		head = head->next;
		if (head == NULL)
			break;
	}

	fclose(file);
}


/**
 * 从文件中读取交易信息
 */
void importDataInteractions()
{
	if (user_id == -1)
	{
		printRed("You're not logged in. Please log in first!\n");
		return;
	}
	char filename[100] = { 0 };
	char buffer[100] = { 0 };
	printf("Please enter the name of the sql file: ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "r");
	while (!file) // 如果用户输入的文件不合法，则让用户重新输入
	{
		const bool do_retry = ask_for_retry("The filename you entered is not valid.");
		if (!do_retry)
		{
			return;
		}
		printf("Please enter the name of the sql file: ");
		scanf("%s", filename);
		file = fopen(filename, 'r');
	}
	char u_name[100];
	char u_password[100];
	char u_email[100];
	 // 从文件中读取各种数据，数据格式参见 export_data 函数中是如何写入的(
	fgets(u_name, sizeof(u_name),file);
	fgets(u_password, sizeof(u_password), file);
	fgets(u_email, sizeof(u_email), file);
	trim(u_name);
	trim(u_password);
	trim(u_email); // 防止读到换行符等空白字符
	user_id = user_sign_up(u_name, u_password, u_password, u_email); // 注册用户
	if (user_id == -1) 
	{
		user* u = getUserByName(db, u_name);
		user_id = u->id;
	}
	fprintf(stdout, "%s\n%s\n%s\n", u_name, u_password, u_email);
	char type[10];
	char amount[10];
	char class_name[100];
	char date[100];
	while(fgets(type,sizeof(type),file))
	{
		trim(type);
		fgets(amount, sizeof(amount), file);
		trim(amount);
		fgets(class_name, sizeof(class_name), file);
		trim(class_name);
		int class_id = create_transaction_class(class_name);
		if (class_id == -1)
		{
			class_id = find_transaction_class(class_name);
		}
		fgets(date, sizeof(date), file);
		trim(date);
		record_transaction(strcmp(type, "1") == 0 ? 1 : 0, atof(amount), class_id, user_id, date);
	}
	fclose(file);
}
/**
 * 询问用户是否重新尝试
 * @param message 错误信息（要重新尝试的原因）
 */
bool ask_for_retry(const char* message)
{
	char* buffer = (char*)malloc(sizeof(char) * 100);
	if (buffer == NULL)
	{
		return false; // 创建缓冲区失败，强制返回不继续
	}
	printf("\n");
	if (message != NULL)
	{
		printRed("Error: ");
		printRed(message);
		printf("\n");
	}
	printf("Would you like to retry? (y or n): ");
	gets_s(buffer, sizeof(buffer));
	while (strcmp(buffer, "y") != 0 && strcmp(buffer, "n") != 0 && strcmp(buffer, "yes") != 0 && strcmp(buffer, "no") != 0)
	{ // 如果输入不满足要求，则一直要求输入
		printf("Please input y or n: ");
		gets_s(buffer, sizeof(buffer));
	}
	if (strcmp(buffer, "n") == 0 || strcmp(buffer, "no") == 0)
	{
		free(buffer);
		return false;
	}
	printf("\n");
	free(buffer);
	return true;
}