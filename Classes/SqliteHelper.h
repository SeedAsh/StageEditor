#ifndef __SQLITEHELPER_H__
#define __SQLITEHELPER_H__ 

#include "sqlite3.h"
#include "cocos2d.h"
#include <unordered_map>

#define DB_STAGE_EDITOR "data/StageEditor.db"
#define DB_STAGES  "data/Stages.db" 
//����ͬһ�����ݿ⣬ ��������ֻ��һ��

class SqliteHelper
{
public:
	SqliteHelper(): m_pGameDataBase(NULL){}
	SqliteHelper(const char* dbPath);
	~SqliteHelper();

	void openDB(const char* dbPath);
	void createTable(const char *sql_str);
	void executeSql(const char *sql_str);
	std::vector<std::vector<char *>> readRecord(const char *sql_str);
	void clearTable(const char *tabelName);

	std::unordered_map<std::string, std::vector<std::string>> getDBInfo();
	void closeDB();

	void openTransaction(bool open);//���������ƣ�ִ�д������ݴ洢ʱ�����Դ�
private:
	sqlite3* prepareTableInDB(const char* dbFilename);
	void GetTablesName(std::vector<std::string>& vecTable);
	bool GetColName(std::vector<std::string>& vecColName, std::string strTableName);

private:
	sqlite3 *m_pGameDataBase;
	std::string m_tableName;
};
#endif