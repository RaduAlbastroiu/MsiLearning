#pragma once
#include "stdafx.h"
#include "TableState.h"
#include "CreateTableState.h"
#include "DatabaseInfo.h"

class Database
{
public:
  Database(const wstring& databasePath);

  // use table
  unique_ptr<TableState> inTable(const wstring& aTableName);

  // create table
  unique_ptr<CreateTableState> createTable(const wstring& aTableName);

  // run any custom sql
  UINT runSqlQuerry(const wstring& aSqlQuerry);

private:
  wstring mDatabasePath;

  DatabaseInfo mDatabaseInfo;
};
