#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

bool DatabaseInfo::openDatabase(const wstring aDatabasePath)
{
  databasePath = aDatabasePath;

  LPCTSTR databasePath = aDatabasePath.c_str();
  mErrorMessage = ::MsiOpenDatabase(databasePath, MSIDBOPEN_DIRECT, &mDatabaseHandle);

  if (mErrorMessage == ERROR_SUCCESS)
    return true;

  return false;
}

void DatabaseInfo::updateConditionWith(const LogicCondition& anotherCondition)
{
  mCondition = mCondition.And(anotherCondition);
}

std::unique_ptr<Table> DatabaseInfo::select()
{
  wstring sqlSelectQuerry = selectSqlCondition();

  Table resultTable = createTableFromSqlQuerry(sqlSelectQuerry);

  return make_unique<Table>(resultTable);
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = L" SELECT ";
  sqlQuerry += composeSqlQuerryColumns();
  sqlQuerry += L" FROM ";
  sqlQuerry += composeSqlQuerryTables();
  sqlQuerry += L" WHERE ";
  sqlQuerry += mCondition.getCondition();

  return sqlQuerry;
}

std::wstring DatabaseInfo::composeSqlQuerryTables()
{
  wstring result = L"";
  result += mTargetTabel.tableName;

  return result;
}

std::wstring DatabaseInfo::composeSqlQuerryColumns()
{
  wstring result = L"";
  for (auto columnName : mTargetTabel.columnsCollection)
    result += columnName;

  return result;
}

bool DatabaseInfo::runSql(const wstring & aSqlQuerry)
{
  MSIHANDLE phView;
  LPCTSTR sqlQuerry = aSqlQuerry.c_str();

  mErrorMessage = ::MsiDatabaseOpenView(mDatabaseHandle, sqlQuerry, &phView);
  if (mErrorMessage == ERROR_SUCCESS)
  {
    mErrorMessage = ::MsiViewExecute(phView, 0);
    if (mErrorMessage == ERROR_SUCCESS)
    {
      mErrorMessage = ::MsiDatabaseCommit(mDatabaseHandle);
      if (mErrorMessage == ERROR_SUCCESS)
      {
        return true;
      }
    }
  }
  return false;
}
