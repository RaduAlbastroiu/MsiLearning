#pragma once
#include "stdafx.h"
#include "TableState.h"
#include "DatabaseInfo.h"

class Database
{
public:
  Database(const wstring& databasePath);

  // use table
  unique_ptr<TableState> addTable(const wstring& tableName);

  bool runSqlQuerry(const wstring& aSqlQuerry);


private:
  wstring mDatabasePath;

  DatabaseInfo mDatabaseInfo;
};
