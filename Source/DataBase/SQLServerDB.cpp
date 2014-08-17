#include <iostream>
#include <iomanip>
#include <exception>
#include "MyTools/MyNetTools.h"
#include "DataBase/SQLServerDB.h"

namespace DataBase
{
	using std::exception;
	using MyTools::GetHostName;

	void CSQLServerDB::InitConnection(const string& strConnectString)
	{
		try
		{
			this->m_pConnection->ConnectionString = strConnectString.c_str();
			this->m_pConnection->Open("", "", "", adModeUnknown);
		}
		catch (exception&)
		{
			throw;
		}
		catch (...)
		{
			throw exception("初始化数据库连接时出现错误");
		}
	}

	CSQLServerDB::CSQLServerDB(const string& strDBName, const string& strUserID, const string& strPwd, const string& strServerName)
	{
		try
		{
			string str("Provider=SQLOLEDB;Initial Catalog=" + strDBName + ";uid=" + strUserID + ';' + "DataBase=" + strDBName + ";pwd=" + strPwd + ";Data Source=" + GetHostName() + '\\' + strServerName);
			this->InitConnection(str);
		}
		catch (exception&)
		{
			throw;
		}
		catch (...)
		{
			throw exception("数据库连接对象初始化失败");
		}
	}

	CSQLServerDB::CSQLServerDB(const string& strDBName, const string& strUserID, const string& strPwd, const string& strServerAddress, const string& strPort)
	{
		try
		{
			string str("Provider=SQLOLEDB;Initial Catalog=" + strDBName + ";uid=" + strUserID + ';' + "DataBase=" + strDBName + ";pwd=" + strPwd + ";Data Source=" + strServerAddress + ',' + strPort);
			this->InitConnection(str);
		}
		catch (exception&)
		{
			throw;
		}
		catch (...)
		{
			throw exception("数据库连接对象初始化失败");
		}
	}

	vector<vector<string>> CSQLServerDB::Execute(const string& strSQL)
	{
		try
		{
			vector<vector<string>> vecTable;

			this->m_pRecordSet = this->m_pConnection->Execute(strSQL.c_str(), NULL, adCmdText);
			if (this->m_pRecordSet->State)
			{
				long lColumnCount = this->m_pRecordSet->GetFields()->Count;			//获取列的个数
				vector<string> vecColumn;

				while (!this->m_pRecordSet->rsEOF)
				{
					vector<string> vecRecord;
					for (long l = 0; l < lColumnCount; ++l)
					{
						vecRecord.push_back(static_cast<char*>((static_cast<_bstr_t>(this->m_pRecordSet->GetCollect(this->m_pRecordSet->GetFields()->GetItem(l)->Name)))));
						this->m_pRecordSet->GetCollect(this->m_pRecordSet->GetFields()->GetItem(l)->Name);
					}
					vecTable.push_back(vecRecord);
					this->m_pRecordSet->MoveNext();
				}
			}
			return vecTable;
		}
		catch (exception&)
		{
			throw;
		}
		catch (...)
		{
			throw exception("SQL语句执行失败");
		}
	}

	bool CSQLServerDB::Open(void)
	{
		try
		{
			if (this->m_pRecordSet->State)
			{
				this->m_pRecordSet->Close();
			}
			this->m_pRecordSet->Open("select * from moveobject", this->m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		}
		catch (_com_error&)
		{
			return false;
		}
		return true;
	}

	bool CSQLServerDB::Update(void)
	{
		try
		{
			this->m_pRecordSet->Update();
		}
		catch (_com_error&)
		{
			return false;
		}
		return true;
	}

	bool CSQLServerDB::Insert(unsigned short usStationID, unsigned int uiTargetID, float fX, float fY, unsigned int uiTimeStamp)
	{
		try
		{		
			this->m_pRecordSet->AddNew();
			this->m_pRecordSet->PutCollect("stationID", _variant_t(static_cast<unsigned short>(usStationID)));
			this->m_pRecordSet->PutCollect("targetID", _variant_t(static_cast<unsigned int>(uiTargetID)));
			this->m_pRecordSet->PutCollect("xPosition", _variant_t(static_cast<float>(fX)));
			this->m_pRecordSet->PutCollect("yPosition", _variant_t(static_cast<float>(fY)));
			this->m_pRecordSet->PutCollect("timestamp", _variant_t(static_cast<unsigned int>(uiTimeStamp)));
		}
		catch (_com_error&)
		{
			return false;
		}
		return true;
	}
}
