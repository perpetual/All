#ifndef MYALGORITHM_ENCRYPTION_H
#define MYALGORITHM_ENCRYPTION_H

#include <string>
#include <map>

namespace MyAlgorithm
{
	using std::string;
	using std::map;

	//���ܣ��㷨�硶C��ָ�롷P190��12��
	class CEncryption
	{
	public:
		//��һ�������Ǵ������ַ���
		//�ڶ�������������
		CEncryption(const string&, const string&);

		//����
		string Encrypt(void);

		//����
		string Decrypt(void);

	private:
		string m_str;								//�������ַ���
		map<char, char> m_mapCodeBook;			//�����ַ����ձ�<�����ַ��������ַ�>
		map<char, char> m_mapRCodeBook;		//�����ַ����ձ�<�����ַ��������ַ�>
	};
}

#endif