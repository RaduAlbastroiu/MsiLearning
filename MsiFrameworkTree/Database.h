#pragma once
#include "stdafx.h"
#include "Table.h"
#include "DatabaseInfo.h"

class Database
{
public:
  Database(const wstring& databasePath);

  unique_ptr<Table> addTable(const wstring& tableName);

  wstring mDatabasePath;

private:
  DatabaseInfo mDatabaseInfo;
};
