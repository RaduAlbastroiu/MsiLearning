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

UINT DatabaseInfo::deleteRows()
{
  return 0;
}

UINT DatabaseInfo::deleteAllRows()
{
  return 0;
}

UINT DatabaseInfo::insertInColumnValue(const wstring & /*aColumnName*/, const wstring & /*aValue*/)
{
  return 0;
}

UINT DatabaseInfo::insert()
{
  return 0;
}

UINT DatabaseInfo::addColumn(const wstring & /*aColumnName*/, const ColumnType & /*aColumnType*/)
{
  return 0;
}

UINT DatabaseInfo::createTable(const wstring & /*aTableName*/)
{
  return 0;
}

UINT DatabaseInfo::addTableToDatabase()
{
  return 0;
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = L" SELECT ";
  sqlQuerry += composeSqlEnumerateColumns();
  sqlQuerry += L" FROM ";
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += L" WHERE ";
  sqlQuerry += mCondition.getCondition();

  return sqlQuerry;
}

std::wstring DatabaseInfo::updateSqlCondition()
{
  wstring sqlQuerry = L" UPDATE ";
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += L" SET ";
  //
  sqlQuerry += L" WHERE ";
  sqlQuerry += mCondition.getCondition();
  
  return sqlQuerry;
}

std::wstring DatabaseInfo::composeSqlQuerryTable()
{
  wstring result = L"";
  result += mTargetTabel.tableName;

  return result;
}

std::wstring DatabaseInfo::composeSqlEnumerateColumns()
{
  // add columns with comas
  wstring result = L"";
  for (auto columnName : mTargetTabel.columnsCollection)
    result += columnName + L", ";
 
  // delete last coma
  result.pop_back();
  result.pop_back();

  return result;
}

std::wstring DatabaseInfo::composeSqlUpdateColumns()
{
  // add columns = value with comas
  wstring result = L"";
  for (size_t i = 0; i < mTargetTabel.columnsCollection.size(); i++)
  {
    result += mTargetTabel.columnsCollection[i] + L" = " + mTargetTabel.newValueForColumns[i] + L", ";
  }

  // delete las coma
  result.pop_back();
  result.pop_back();

  return result;
}

Table DatabaseInfo::createTableFromSqlQuerry(const wstring & /*sqlQuerry*/)
{
  return Table();
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
