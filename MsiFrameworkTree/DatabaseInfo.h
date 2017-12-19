#pragma once
#include "stdafx.h"
#include "Table.h"
#include "LogicCondition.h"

class DatabaseInfo
{
public:

  bool openDatabase(const wstring databasePath);
  unique_ptr<Table> select();

  bool runSql(const wstring& aSqlQuerry);
  
  template<typename... Types>
  void addTableWithColumns(const wstring& aTableName, const Types... aColumns)
  {
    tableCollection.push_back(aTableName, vector<wstring>{ aColumns... });
  }

private:

  UINT mErrorMessage = ERROR_SUCCESS;

  MSIHANDLE mDatabaseHandle;

  wstring composeSqlQuerryTables();
  wstring composeSqlQuerryColumns();
  wstring selectSqlCondition();

  vector<Table> tableCollection;

  wstring databasePath;

  LogicCondition condition;


};
