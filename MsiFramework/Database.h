#pragma once

#include "stdafx.h"
#include "Table.h"

class Database
{
private:
  LPCWSTR mDatabasePath;
  MSIHANDLE mDatabaseHandle;

  vector<Table> tables;

public:
  Database(wstring aDatabasePath);

  ~Database();

  void saveDatabase();

  Table getTable(wstring tableName);
};

