#ifndef UTILITIES_H
#define UTILITIES_H
#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * ��ȡ��ǰϵͳʱ�䣬����ָ����ʽ����
	 */
	const char* getSystemDate();
	/**
	* ����һ���ַ���ǰ�������Ŀո񣬻��з�
	*/
	void trim(char* s);
	/**
	 * Read password ��ʾ�û��������룬���û������� * ����ʽ���ء�
	 */
	char* read_password(char* buffer);
#ifdef __cplusplus
}
#endif

#endif
