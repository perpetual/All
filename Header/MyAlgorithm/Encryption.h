#ifndef MYALGORITHM_ENCRYPTION_H
#define MYALGORITHM_ENCRYPTION_H

#include <string>
#include <map>

namespace MyAlgorithm
{
	using std::string;
	using std::map;

	//加密，算法如《C和指针》P190第12题
	class CEncryption
	{
	public:
		//第一个参数是待处理字符串
		//第二个参数是密码
		CEncryption(const string&, const string&);

		//加密
		string Encrypt(void);

		//解密
		string Decrypt(void);

	private:
		string m_str;								//待处理字符串
		map<char, char> m_mapCodeBook;			//明密字符对照表<明文字符，密文字符>
		map<char, char> m_mapRCodeBook;		//密明字符对照表<密文字符，明文字符>
	};
}

#endif