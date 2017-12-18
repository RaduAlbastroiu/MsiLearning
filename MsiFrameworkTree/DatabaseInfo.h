#pragma once
#include "stdafx.h"
#include "LogicCondition.h"

class DatabaseInfo
{
public:

  DatabaseInfo() = default;

  wstring databasePath;
  
  LogicCondition condition;

  template<typename... Types>
  void addTableWithColumns(const wstring& aTableName, const Types... aColumns)
  {
    tableCollection.push_back(aTableName, vector<wstring>{ aColumns... });
  }

  bool openDatabase(const wstring databasePath);
  wstring selectSqlCondition();
  wstring updateSqlCondition(wstring aNewValue);
  wstring deleteSqlCondition();

  bool runSql(const wstring& aSqlQuerry);

private:

  UINT mErrorMessage = ERROR_SUCCESS;

  MSIHANDLE mDatabaseHandle;

  wstring composeSqlQuerryTables();
  wstring composeSqlQuerryColumns();

  struct DbInfoTable
  {
    // constructor
    DbInfoTable(wstring aTableName, vector<wstring> aColumns) :
      tableName(aTableName), columns(aColumns)
    {}

    wstring tableName;
    vector<wstring> columns;
  };
  vector<DbInfoTable> tableCollection;
};
