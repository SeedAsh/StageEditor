#ifndef __SQLITEHELPER_H__
#define __SQLITEHELPER_H__ 

#include "sqlite3.h"
#include "cocos2d.h"
#include <unordered_map>

#define DB_STAGE_EDITOR "data/StageEditor.db"
#define DB_STAGES  "data/Stages.db" 
//对于同一个数据库， 尽量保持只有一个

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

	void openTransaction(bool open);//事务开启控制，执行大量数据存储时，可以打开
private:
	sqlite3* prepareTableInDB(const char* dbFilename);
	void GetTablesName(std::vector<std::string>& vecTable);
	bool GetColName(std::vector<std::string>& vecColName, std::string strTableName);

private:
	sqlite3 *m_pGameDataBase;
	std::string m_tableName;
};
#endif