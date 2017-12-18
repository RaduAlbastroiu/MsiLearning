#pragma once
#include "stdafx.h"
#include "LogicCondition.h"

class DatabaseInfo
{
public:

  DatabaseInfo() = default;

  wstring databasePath;
  
  MSIHANDLE rootHandle;
  LogicCondition condition;


  void addTable(const wstring& aTableName);
  template<typename... Types>
  void addColumns(const Types... aColumns)
  {
    // add to the last table added
    tableCollection[tableCollection.size() - 1].columns = vector<wstring>{ aColumns... };
  }

  void openDatabase(const wstring databasePath);
  wstring selectSqlCondition();
  wstring updateSqlCondition(wstring aNewValue);
  wstring deleteSqlCondition();

private:

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
