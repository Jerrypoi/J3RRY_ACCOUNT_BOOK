#ifndef UTILITIES_H
#define UTILITIES_H
#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * 获取当前系统时间，并以指定格式返回
	 */
	const char* getSystemDate();
	/**
	* 消除一个字符串前面与后面的空格，换行符
	*/
	void trim(char* s);
	/**
	 * Read password 提示用户输入密码，将用户输入以 * 的形式返回。
	 */
	char* read_password(char* buffer);
	/**
	 * 检查用户输入的邮箱地址是否为一个合法的邮箱地址
	 */
	int check_valid_email(char* email);
	/**
	 * 检查用户输入的日期是否满足 YYYY-MM-DD 格式
	 */
	int check_valid_date(const char* date);
	
#ifdef __cplusplus
}
#endif

#endif
