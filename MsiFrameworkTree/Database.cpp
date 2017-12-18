#pragma once
#include "stdafx.h"
#include "Database.h"

Database::Database(const wstring& aDatabasePath)
  :mDatabaseInfo(aDatabasePath)
{
  // open database
  mDatabaseInfo.openDatabase(mDatabasePath);
}

unique_ptr<Table> Database::addTable(const wstring& aTableName)
{
  return make_unique<Node>(mDatabaseInfo, aTableName);
}
