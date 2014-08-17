#include "VersionControl.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <cstring>
#include <cstdlib>
#include <climits>
#include "MyTools/MyUtilityTools.h"

#ifdef __OS_VERSION_LINUX__
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iconv.h>
#include <termios.h>
#endif


namespace MyTools
{
	using std::ifstream;
	using std::ofstream;
	using std::istringstream;
	using std::wistringstream;
	using std::cout;
	using std::endl;
	using std::bitset;
	using std::fstream;
	using MyTools::WStrToStr;

#ifdef __OS_VERSION_WINDOWS__
	static unsigned int g_uiComInitCount = 0;			//COM库初始化计数器
	CInitCom::CInitCom(void)
	{
		if (0 == g_uiComInitCount++)
		{
			::CoInitialize(NULL);
		}
	}

	CInitCom::~CInitCom(void)
	{
		if (0 == --g_uiComInitCount)
		{
			::CoUninitialize();
		}
	}
#endif

	string Trim(const char* const pStr)
	{
		return Trim(string(pStr));
	}

	wstring Trim(const wchar_t* const pWStr)
	{
		return Trim(wstring(pWStr));
	}

	string Trim(string str)
	{
		int begin = 0, end = 0;

		for (begin = 0; begin < static_cast <int> (str.length()); ++begin)
		{
			if (str[begin] != '\t' && str[begin] != ' ' && str[begin] != '\r' && str[begin] != '\n' && str[begin] != '\0')			//如果不是空白字符
			{
				break;
			}
			else
			{
				continue;
			}
		}

		for (end = str.length() - 1; end > 0; --end)
		{
			if (str[end] != '\t' && str[end] != ' ' && str[end] != '\r' && str[end] != '\n' && str[end] != '\0')			//如果是空白字符
			{
				break;
			}
			else
			{
				continue;
			}
		}

		if (begin > end)
		{
			str.clear();;
			return str;
		}
		else
		{
			return string(str.begin() + begin, str.begin() + end + 1);			//去除两端的空白字符
		}
	}

	wstring Trim(wstring wstr)
	{
		int begin = 0, end = 0;

		for (begin = 0; begin < static_cast <int> (wstr.length()); ++begin)
		{
			if (wstr[begin] != '\t' && wstr[begin] != ' ' && wstr[begin] != '\r' && wstr[begin] != '\n' && wstr[begin] != '\0')			//如果不是空白字符
			{
				break;
			}
			else
			{
				continue;
			}
		}

		for (end = wstr.length() - 1; end > 0; --end)
		{
			if (wstr[end] != '\t' && wstr[end] != ' ' && wstr[end] != '\r' && wstr[end] != '\n' && wstr[end] != '\0')			//如果是空白字符
			{
				break;
			}
			else
			{
				continue;
			}
		}

		if (begin > end)
		{
			wstr.clear();;
			return wstr;
		}
		else
		{
			return wstring(wstr.begin() + begin, wstr.begin() + end + 1);			//去除两端的空白字符
		}
	}

	string TrimAll(const char* const pStr)
	{
		return TrimAll(string(pStr));
	}

	wstring TrimAll(const wchar_t* const pWStr)
	{
		return TrimAll(wstring(pWStr));
	}

	string TrimAll(string str)
	{
		string temp;
		istringstream istrstr(str);

		str.clear();
		while (istrstr >> temp)
		{
			str += temp + ' ';
		}

		if (!str.empty())
		{
			str = str.substr(0, str.length() - 1);
		}
		return str;
	}

	wstring TrimAll(wstring wstr)
	{
		wstring temp;
		wistringstream wistrstr(wstr);
		wstr.clear();
		while (wistrstr >> temp)
		{
			wstr += temp + L' ';
		}

		if (!wstr.empty())
		{
			wstr = wstr.substr(0, wstr.length() - 1);
		}
		return wstr;
	}

	wstring StrToWStr(const string& str)
	{
		wstring wstrRet;
#ifdef __OS_VERSION_WINDOWS__
		unsigned int uiWStrLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);		//包括末尾的'\0'
		unsigned int uiWStrSize = uiWStrLen * sizeof (wchar_t);
		wchar_t* pWStrBuf = new wchar_t[uiWStrSize];

		if (0 != MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pWStrBuf, uiWStrSize))
		{
			wstrRet = wstring(pWStrBuf, 0 == uiWStrLen ? 0 : uiWStrLen - 1);
		}
		delete[] pWStrBuf;
#elif defined(__OS_VERSION_LINUX__)
#endif
		return TrimAll(wstrRet);
	}

	string WStrToStr(const wstring& wstr)
	{
		string strRet;
#ifdef __OS_VERSION_WINDOWS__
		unsigned int uiStrLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);		//包括末尾的'\0'
		unsigned int uiStrSize = uiStrLen;
		char* pStrBuf = new char[uiStrSize];

		if (0 != WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.length(), pStrBuf, uiStrSize, NULL, NULL))
		{
			strRet = string(pStrBuf, 0 == uiStrLen ? 0 : uiStrLen - 1);
		}
		delete[] pStrBuf;
#elif defined(__OS_VERSION_LINUX__)
#endif
		return TrimAll(strRet);
	}

	template<typename T>
	T StringToNumber(const string& str, T)
	{
		istringstream iss(str);
		T t;
		iss >> t;
		return t;
	}

	char StringToChar(const string& str)
	{
		return StringToNumber(str, char(0));
	}

	unsigned char StringToUChar(const string& str)
	{
		return StringToNumber(str, (unsigned char)(0));
	}

	byte StringToByte(const string& str)
	{
		short s;
		istringstream iss(str);

		iss >> s;
		return static_cast<byte>(s);
	}

	ubyte StringToUByte(const string& str)
	{
		unsigned short us;
		istringstream iss(str);

		iss >> us;
		return static_cast<ubyte>(us);
	}

	short StringToShort(const string& str)
	{
		return StringToNumber(str, short(0));
	}

	unsigned short StringToUShort(const string& str)
	{
		return StringToNumber(str, (unsigned short)(0));
	}

	int StringToInt(const string& str)
	{
		return StringToNumber(str, int(0));
	}

	unsigned int StringToUInt(const string& str)
	{
		return StringToNumber(str, (unsigned int)(0));
	}

	long StringToLong(const string& str)
	{
		return StringToNumber(str, long(0));
	}

	unsigned long StringToULong(const string& str)
	{
		return StringToNumber(str, (unsigned long)(0));
	}

	long long StringToLongLong(const string& str)
	{
		return StringToNumber(str, (long long)(0));
	}

	unsigned long long StringToULongLong(const string& str)
	{
		return StringToNumber(str, (unsigned long long)(0));
	}

	float StringToFloat(const string& str)
	{
		return StringToNumber(str, float(0));
	}

	double StringToDouble(const string& str)
	{
		return StringToNumber(str, double(0));
	}

	long double StringToLDouble(const string& str)
	{
		return StringToNumber(str, (long double)(0));
	}

	bool IsFile(const string& str)
	{
#ifdef __OS_VERSION_WINDOWS__
		return fstream(str.c_str()).is_open();
#elif defined (__OS_VERSION_LINUX__)
		struct stat buf;
		return 0 == stat(str.c_str(), &buf) ? !S_ISDIR(buf.st_mode) : false;
#endif
	}

	bool IsDirectory(const string& str)
	{
#ifdef __OS_VERSION_WINDOWS__
		return FILE_ATTRIBUTE_DIRECTORY == ::GetFileAttributes(StrToWStr(str).c_str());
#elif defined (__OS_VERSION_LINUX__)
		struct stat buf;
		return 0 == stat(str.c_str(), &buf) ? S_ISDIR(buf.st_mode) : false;
#endif
	}

	string ReadWholeFile(const string& strFileName)
	{
		ifstream InFile(TrimAll(strFileName).c_str());
		string strRet, strTemp;

		while (getline(InFile, strTemp))
		{
			strRet += strTemp + '\n';
		}
		InFile.close();
		return strRet;
	}

	bool WriteWholeFile(const string& strFileName, const string& strText)
	{
		ofstream outFile(Trim(strFileName).c_str());
		bool bRet = (outFile << strText).good();

		outFile.close();
		return bRet;
	}

	string GetRandomName(void)
	{
		char ch[FILENAME_MAX];
#ifdef __OS_VERSION_WINDOWS__
		if (0 == tmpnam_s(ch, FILENAME_MAX))
		{
			return string(ch + 1);
		}
#elif defined(__OS_VERSION_LINUX__)
		if (NULL != tmpnam(ch))
		{
			return string(ch + 5);
		}
#endif
		else
		{
			return string();
		}
	}

	bool RemoveFile(const string& strFileName)
	{
		return 0 == ::remove(strFileName.c_str());
	}

	bool RenameFile(const string& strOldName, const string& strNewName)
	{
		return 0 == ::rename(strOldName.c_str(), strNewName.c_str());
	}

	void WaitForever(void)
	{
#ifdef __OS_VERSION_WINDOWS__
		Sleep(static_cast<unsigned>(-1));
#elif defined(__OS_VERSION_WINDOWS__)
		sleep(static_cast<unsigned>(-1));
#endif
	}

	//用指定分隔符提取字符串
	vector<string> SplitString(const string& str, const string& strSeperator)
	{
		char* pBuf = new char[str.length() + 1];
		const char* pSeperator = strSeperator.c_str();
		char* pNextToken = NULL;
		vector<string> vecRet;

		memset(pBuf, '\0', str.length() + 1);
#ifdef __OS_VERSION_WINDOWS__
		memcpy_s(pBuf, str.length(), str.c_str(), str.length());
		for (char* p = strtok_s(pBuf, pSeperator, &pNextToken); NULL != p; p = strtok_s(NULL, pSeperator, &pNextToken))
#elif defined(__OS_VERSION_LINUX__)
		memcpy(pBuf, str.c_str(), str.length());
		for (char* p = strtok(pBuf, pSeperator); NULL != p; p = strtok(NULL, pSeperator))
#endif
		{
			vecRet.push_back(p);
		}

		delete[] pBuf;
		return vecRet;
	}

	bool SetSystemTime(time_t t)
	{
#ifdef __OS_VERSION_WINDOWS__
		FILETIME ft;
		SYSTEMTIME st;

		//首先设置基准时间
		st.wYear = 1900;
		st.wMonth = 1;
		st.wDay = 1;
		st.wHour = 0;
		st.wMinute = 0;
		st.wSecond = 0;
		st.wMilliseconds = 0;
		if (::SystemTimeToFileTime(&st, &ft))
		{
			*reinterpret_cast<unsigned long long*>(&ft) += static_cast<unsigned long long>(t) * 10000000;
			if (::FileTimeToLocalFileTime(&ft, &ft) && ::FileTimeToSystemTime(&ft, &st))
			{
				return TRUE == ::SetSystemTime(&st);
			}
		}
		return false;
#elif defined(_OS_VERSION_LINUX__)
        return false;
#endif
	}

	string& AppendString(string& str, const void* pBuf, unsigned int uiLen)
	{
		return str.append(reinterpret_cast<const char*>(pBuf), uiLen);
	}

	string& AppendString(string& str, char ch, unsigned int uiCount)
	{
		return str.append(uiCount, ch);
	}

	string PrintMemory(const void* pBuf, unsigned int uiBufLen)
	{
		string str;
		const char* p = reinterpret_cast<const char*>(pBuf);
		const unsigned int uiBufBitLen = 8 * uiBufLen;

		for (unsigned int u = 0; u < uiBufLen; ++u)
		{
			bitset<8> bs(*(reinterpret_cast<const unsigned char*>(p++)));
			str.insert(0, bs.to_string());
		}
		if (str.length() != uiBufBitLen)
		{
			str.insert(0, uiBufBitLen - str.length(), '0');
		}
		return str;
	}

	static void GetAllFileName(const string& strDir, bool bDirectory, bool bRecursion, bool bShowHidden, vector<string>& vecNames)
	{
		string strFullPath;
#ifdef __OS_VERSION_WINDOWS__
		struct _finddata_t tFileData;
		intptr_t handle = _findfirst((strDir + "\\*").c_str(), &tFileData);

		if (-1 == handle)
		{
			return;
		}
		while (-1 != _findnext(handle, &tFileData))
		{
			if (0 != strncmp(".", tFileData.name, 2) && 0 != strncmp("..", tFileData.name, 3))
			{
				if (bShowHidden || '.' != tFileData.name[0])
				{
						strFullPath = strDir + '\\' + tFileData.name;
#elif defined (__OS_VERSION_LINUX__)
		DIR *pCurDir = ::opendir(strDir.c_str());
		struct dirent *pItem = NULL;
		struct stat tBuf;

		if (NULL == pCurDir)
		{
			return;
		}

		while (NULL != (pItem = ::readdir(pCurDir)))
		{
			if (0 != strncmp(".", pItem->d_name, 2) && 0 != strncmp("..", pItem->d_name, 3))
			{
				if (bShowHidden || '.' != pItem->d_name[0])
				{
					strFullPath = strDir + '/' + pItem->d_name;
#endif
					if (IsDirectory(strFullPath))	//如果是目录
					{
						if (bDirectory)
						{
							vecNames.push_back(strFullPath);
						}
						if (bRecursion)
						{
							GetAllFileName(strFullPath.c_str(), bDirectory, bShowHidden, bRecursion, vecNames);
						}
					}
					else
					{
						vecNames.push_back(strFullPath);
					}
				}
			}
		}
#ifdef __OS_VERSION_WINDOWS__
		::_findclose(handle);
#elif defined (__OS_VERSION_LINUX__)
		::closedir(pCurDir);
#endif
	}

	vector<string> GetAllFileName(const string& strDir, bool bDirectory, bool bRecursion, bool bShowHidden)
	{
		vector<string> vecNames;

		GetAllFileName(strDir, bDirectory, bRecursion, bShowHidden, vecNames);
		return vecNames;
	}

	bool TransCode(const string& strSrcFileName, const string& strSrcCode, const string& strDstCode, const string& strDstFileName)
	{
		string strCmd("iconv");

		strCmd += " -f " + strSrcCode + " -t " + strDstCode + ' ' + strSrcFileName + " > " + strDstFileName;
		return 0 == system(strCmd.c_str());
	}

#ifdef __OS_VERSION_LINUX__
	int getch(void)
	{
		struct termios tm, tm_old;
		int fd = STDIN_FILENO, c;
		if ( tcgetattr  ( fd, &tm ) < 0 )
				return -1;
		tm_old = tm;
		cfmakeraw  ( &tm );
		if ( tcsetattr  ( fd, TCSANOW, &tm ) < 0 )
				return -1;
		c = fgetc ( stdin );
		if ( tcsetattr  ( fd, TCSANOW, &tm_old )<0 )
				return -1;

		return c;
	}

	int kbhit(void)
	{
		int i;

		system("stty raw -echo");
		ioctl(0, FIONREAD, &i);
		i = getchar();
		system("stty cooked echo");
		return i;
	}
#endif

	string GetCurrentPath(void)
	{
		string strCurPath;
		size_t uBufLen = 0;
#ifdef __OS_VERSION_WINDOWS__
		uBufLen = ::GetCurrentDirectory(NULL, NULL);
		wchar_t* wstrBuf = new wchar_t[uBufLen];
		if (0 != ::GetCurrentDirectory(uBufLen, wstrBuf))
		{
			strCurPath.assign(WStrToStr(wstrBuf));
		}
		delete[] wstrBuf;
#elif defined (__OS_VERSION_LINUX__)
		char strBuf[PATH_MAX];

		if (NULL != ::getcwd(strBuf, PATH_MAX))
		{
			strCurPath.assign(strBuf);
		}
#endif
		return strCurPath;
	}

	static clock_t clk = 0;

	float Clock(bool b)
	{
		if (b)
		{
			return clk = ::clock(), 0.0f;
		}
		else
		{
			return static_cast<float>(::clock() - clk) / CLOCKS_PER_SEC;
		}
	}
}
