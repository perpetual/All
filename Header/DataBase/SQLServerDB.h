#ifndef SQLSERVERDB_SQL_SERVER_DB_H
#define SQLSERVERDB_SQL_SERVER_DB_H

#import "C:\program files\common files\system\ado\msado15.dll" rename("EOF","rsEOF")

#include <string>
#include <vector>
#include "MyTools/MyUtilityTools.h"

namespace DataBase
{
	using std::string;
	using std::vector;
	using ADODB::_ConnectionPtr;
	using ADODB::_RecordsetPtr;
	using ADODB::adCmdText;
	using ADODB::Connection;
	using ADODB::Recordset;
	using ADODB::adModeUnknown;
	using ADODB::adLockOptimistic;
	using ADODB::adOpenDynamic;
	using ADODB::adOpenStatic;
	using MyTools::CInitCom;

	class CSQLServerDBBase : public CInitCom
	{
	protected:
		CSQLServerDBBase(void) :
			 m_pConnection(__uuidof(Connection)/*"ADODB.Connection"*/),
			 m_pRecordSet(__uuidof(Recordset)/*"ADODB.Recordset"*/)
			{}
		virtual ~CSQLServerDBBase(void)
		 {
			 if (this->m_pRecordSet->State)
			 {
				 this->m_pRecordSet->Close();
				 this->m_pRecordSet.Release();
			 }
			 if (this->m_pConnection->State)
			 {
				 this->m_pConnection->Close();
				 this->m_pConnection.Release();
			 }
		 }
		_ConnectionPtr m_pConnection;
		_RecordsetPtr m_pRecordSet;
	};

	class CSQLServerDB : public CSQLServerDBBase
	{
	public:
		//该构造函数用于连接本地服务器
		//第一个参数是数据库的名称
		//下一个参数是用户名
		//下一个参数是密码
		//下一个参数是数据库服务器的名字
		CSQLServerDB(const string&, const string&, const string&, const string&);

		//该构造函数用于连接远程服务器
		//第一个参数是数据库的名称
		//下一个参数是用户名
		//下一个参数是密码
		//下一个参数是数据库地址
		//下一个参数是数据库连接端口
		CSQLServerDB(const string&, const string&, const string&, const string&, const string&);

		//执行查询语句
		//参数是SQL语句
		//返回值是一个表
		vector<vector<string>> Execute(const string&);

		bool Open(void);
		bool Insert(unsigned short, unsigned int, float, float, unsigned int);
		bool Update(void);
	private:
		//禁止复制和赋值
		CSQLServerDB(const CSQLServerDB&);
		CSQLServerDB& operator =(const CSQLServerDB&);

		//初始化
		//参数为连接字符串
		void InitConnection(const string&);
	};
}

#endif