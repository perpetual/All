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
		//�ù��캯���������ӱ��ط�����
		//��һ�����������ݿ������
		//��һ���������û���
		//��һ������������
		//��һ�����������ݿ������������
		CSQLServerDB(const string&, const string&, const string&, const string&);

		//�ù��캯����������Զ�̷�����
		//��һ�����������ݿ������
		//��һ���������û���
		//��һ������������
		//��һ�����������ݿ��ַ
		//��һ�����������ݿ����Ӷ˿�
		CSQLServerDB(const string&, const string&, const string&, const string&, const string&);

		//ִ�в�ѯ���
		//������SQL���
		//����ֵ��һ����
		vector<vector<string>> Execute(const string&);

		bool Open(void);
		bool Insert(unsigned short, unsigned int, float, float, unsigned int);
		bool Update(void);
	private:
		//��ֹ���ƺ͸�ֵ
		CSQLServerDB(const CSQLServerDB&);
		CSQLServerDB& operator =(const CSQLServerDB&);

		//��ʼ��
		//����Ϊ�����ַ���
		void InitConnection(const string&);
	};
}

#endif