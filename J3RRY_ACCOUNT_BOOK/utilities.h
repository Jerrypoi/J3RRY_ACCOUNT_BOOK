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
#ifdef __cplusplus
}
#endif

#endif
