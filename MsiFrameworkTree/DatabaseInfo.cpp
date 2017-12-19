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

unique_ptr<Table> DatabaseInfo::select()
{
  // database call
  
  return make_unique<Table>();
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = L" SELECT ";
  sqlQuerry += composeSqlQuerryColumns();
  sqlQuerry += L" FROM ";
  sqlQuerry += composeSqlQuerryTables();
  sqlQuerry += L" WHERE ";
  sqlQuerry += condition.getCondition();

  return sqlQuerry;
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
