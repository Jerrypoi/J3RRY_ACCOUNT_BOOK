#ifndef VIEW_H
#define VIEW_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>

void ACCOUNT_BOOK_MAIN_LOOP();
	void printRed(const char* str);
	void printHelpMessage();
	void loginInteractions();
	void logoutInteractions();
	void signUpInteractions();
	void getDataInteractions();
	void recordDataInteractions();
	void importDataInteractions();
	void exportDataInteractions();

	bool ask_for_retry(const char* message);
#ifdef __cplusplus
}
#endif

#endif
