#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

DatabaseInfo::DatabaseInfo(const wstring aDatabasePath)
  :mCondition(L"")
{
  mDatabasePath = aDatabasePath;

  LPCTSTR databasePath = aDatabasePath.c_str();
  mErrorMessage = ::MsiOpenDatabase(databasePath, MSIDBOPEN_DIRECT, &mDatabaseHandle);

}

void DatabaseInfo::updateConditionWith(const LogicCondition& anotherCondition)
{
  mCondition = mCondition.And(anotherCondition);
}

void DatabaseInfo::setTargetTable(const wstring& aTableName)
{
  mTargetTabel = targetTable(aTableName, vector<wstring> {});
}

std::unique_ptr<Table> DatabaseInfo::select()
{
  wstring sqlSelectQuerry = selectSqlCondition();

  Table resultTable = createTableFromSqlQuerry(sqlSelectQuerry);

  return make_unique<Table>(resultTable);
}

UINT DatabaseInfo::update()
{
  wstring sqlUpdateQuerry = updateSqlCondition();
  
  mErrorMessage = runSql(sqlUpdateQuerry);

  return mErrorMessage;
}

void DatabaseInfo::updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.newValueForColumns.push_back(aNewValue);
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

UINT DatabaseInfo::runSql(const wstring & aSqlQuerry)
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
        return ERROR_SUCCESS;
      }
    }
  }
  return mErrorMessage;
}
