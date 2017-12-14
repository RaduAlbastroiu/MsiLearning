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

  struct Table 
  {
    wstring tableName;
    vector<wstring> columns;
  };

  Table tableName;

  void openDatabase(const wstring databasePath);
  wstring selectSqlCondition();
  wstring updateSqlCondition(wstring aNewValue);
  wstring deleteSqlCondition();

private:

  wstring composeSqlQuerryColumns();
  wstring composeSqlQuerryTables();
};
