#ifndef VIEW_H
#define VIEW_H
#ifdef __cplusplus
extern "C" {
#endif

	void ACCOUNT_BOOK_MAIN_LOOP();
	void printRed(const char* str);
	void printHelpMessage();
	void loginInteractions();
	void signUpInteractions();
	void getDataInteractions();
	void recordDataInteractions();
	void importDataInteractions();
	void exportDataInteractions();
#ifdef __cplusplus
}
#endif

#endif
