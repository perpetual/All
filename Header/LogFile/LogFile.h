#ifndef LOGFILE_LOG_FILE_H
#define LOGFILE_LOG_FILE_H

#include <fstream>
#include <iosfwd>
#include <ostream>
#include <string>

namespace LogFile
{
	using std::ofstream;
	using std::basic_ostream;
	using std::char_traits;
	using std::string;
	using std::ios;
	using std::endl;
	using std::ios_base;

	class CLogFile
	{
	public:
		CLogFile(const string& = "Log.log", ios_base::openmode  = ios::trunc, bool bOn = true);
		~CLogFile(void) {this->m_ofLog.close();}

		//����ֵ��ʾ�ļ������Ƿ񴴽��ɹ�
		operator bool(void) const;

		template <class T>
		CLogFile& operator <<(const T& obj)
		{
			if (this->m_bOn)
			{
				this->m_ofLog << obj;
			}
			return *this;
		}

		//֧��endl�ȱ�׼�⺯��
		CLogFile& operator <<( basic_ostream<char, char_traits<char> >& (*)(basic_ostream<char, char_traits<char> >&));

		//������־�Ĵ���ر�
		void Switch(bool);
		bool On(void)
		{
			return this->m_bOn;
		}

	private:
		ofstream m_ofLog;
		bool m_bOn;				//����Ƿ����־
	};
}

#endif