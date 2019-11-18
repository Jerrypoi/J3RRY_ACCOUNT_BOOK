#ifndef VIEW_H
#define VIEW_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>
	/**
	 * 软件主要逻辑
	 */
	void ACCOUNT_BOOK_MAIN_LOOP();
	/**
	 * 显示帮助信息
	 */
	void printHelpMessage();
	/**
	 * 登录交互模块
	 */
	void loginInteractions();
	/**
	 * 注销交互模块
	 */
	void logoutInteractions();
	/**
	 * 注册交互模块
	 */
	void signUpInteractions();
	/**
	 * 显示数据交互模块
	 */
	void getDataInteractions();
	/**
	 * 记录数据交互模块
	 */
	void recordDataInteractions();
	/**
	 * 导入数据交互模块
	 */
	void importDataInteractions();
	/**
	 * 导出数据交互模块
	 */
	void exportDataInteractions();
	/**
	 * 询问用户是否重新尝试
	 * @param message 错误信息（要重新尝试的原因）
	 */
	bool ask_for_retry(const char* message);
#ifdef __cplusplus
}
#endif

#endif
