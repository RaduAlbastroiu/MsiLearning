#pragma once
#include "stdafx.h"
#include "Database.h"

Database::Database(const wstring& aDatabasePath)
  :mDatabaseInfo(aDatabasePath)
{
  // open database
  mDatabaseInfo.openDatabase(mDatabasePath);
}

unique_ptr<Table> Database::inTable(const wstring& aTableName)
{
  return make_unique<Node>(mDatabaseInfo, aTableName);
}

unique_ptr<CreateTableState> Database::createTable(const wstring& aTableName)
{
  mDatabaseInfo.createTable(aTableName);
  return make_unique<CreateTableState>(mDatabaseInfo);
}

bool Database::runSqlQuerry(const wstring& aSqlQuerry)
{
  mDatabaseInfo.runSql(aSqlQuerry);
}
