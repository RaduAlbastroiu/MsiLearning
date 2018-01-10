#pragma once
#include "stdafx.h"
#include "Database.h"

Database::Database(const wstring& aDatabasePath)
  :mDatabaseInfo(aDatabasePath), mDatabasePath(aDatabasePath)
{
}

Database::Database(const MSIHANDLE handleToDatabase)
  :mDatabaseInfo(handleToDatabase)
{
}

unique_ptr<TableState> Database::inTable(const wstring& aTableName)
{
  mDatabaseInfo.setTargetTable(aTableName);
  return make_unique<TableState>(mDatabaseInfo);
}

unique_ptr<CreateTableState> Database::createTable(const wstring& aTableName)
{
  mDatabaseInfo.createTable(aTableName);
  return make_unique<CreateTableState>(mDatabaseInfo);
}

UINT Database::runSqlQuerry(const wstring& aSqlQuerry)
{
  return mDatabaseInfo.runSql(aSqlQuerry);
}

wstring Database::getLastError()
{
  return mDatabaseInfo.getLastError();
}

bool Database::isGood()
{
  return mDatabaseInfo.isGood();
}

wstring Database::getValueFromProperty(const wstring & aPropertyName)
{
  return mDatabaseInfo.getPropertyValue(aPropertyName);
}
