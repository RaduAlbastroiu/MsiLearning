#pragma once
#include "stdafx.h"
#include "Database.h"

Database::Database(const wstring& aDatabasePath)
  :mDatabaseInfo(aDatabasePath)
{
  // open database
  this->mDatabaseInfo.openDatabase(mDatabasePath);
}

unique_ptr<Table> Database::addTable(const wstring& aTableName)
{
  mDatabaseInfo.addTable(aTableName);
  return make_unique<Node>(mDatabaseInfo);
}
