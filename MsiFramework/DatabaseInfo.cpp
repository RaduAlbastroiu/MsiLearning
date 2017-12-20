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
  wstring sqlDeleteQuerry = DELETE;
  sqlDeleteQuerry += FROM;
  sqlDeleteQuerry += composeSqlQuerryTable();
  sqlDeleteQuerry += WHERE;
  sqlDeleteQuerry += mCondition.getCondition();

  return runSql(sqlDeleteQuerry);
}

UINT DatabaseInfo::deleteAllRows()
{
  wstring sqlDeleteQuerry = L" DELETE FROM ";
  sqlDeleteQuerry += composeSqlQuerryTable();
  
  return runSql(sqlDeleteQuerry);
}

void DatabaseInfo::insertInColumnValue(const wstring& aColumnName, const wstring& aValue)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.newValueForColumns.push_back(aValue);
}

UINT DatabaseInfo::insert()
{
  return runSql(insertSqlCondition());
}

void DatabaseInfo::createTable(const wstring& aTableName)
{
  mTargetTabel.tableName = aTableName;
}

void DatabaseInfo::createColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.columnMetadata.push_back(Metadata(aColumnName, aColumnType, false, false));
}

void DatabaseInfo::createNullableColumn(const wstring& aColumnName, const ColumnType& aColumntType)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.columnMetadata.push_back(Metadata(aColumnName, aColumnType, false, true));
}

void DatabaseInfo::createKeyColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.columnMetadata.push_back(Metadata(aColumnName, aColumnType, true, false));
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = SELECT;
  sqlQuerry += composeSqlEnumerateColumns();
  sqlQuerry += FROM;
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += WHERE;
  sqlQuerry += mCondition.getCondition();

  return sqlQuerry;
}

std::wstring DatabaseInfo::updateSqlCondition()
{
  wstring sqlQuerry = UPDATE;
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += SET;
  sqlQuerry += composeSqlUpdateColumns();
  sqlQuerry += WHERE;
  sqlQuerry += mCondition.getCondition();
  
  return sqlQuerry;
}

std::wstring DatabaseInfo::insertSqlCondition()
{
  wstring sqlInsertQuerry = INSERTINTO;
  sqlInsertQuerry += composeSqlQuerryTable();
  sqlInsertQuerry += L" (" + composeSqlEnumerateColumns() + L")";
  sqlInsertQuerry += VALUES;
  sqlInsertQuerry += L"( " + composeSqlEnumerateColumnValues() + L")";

  return sqlInsertQuerry;
}

std::wstring DatabaseInfo::composeSqlQuerryTable()
{
  wstring result = L"";
  result += mTargetTabel.tableName;

  return result;
}

// column names
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

// column values
std::wstring DatabaseInfo::composeSqlEnumerateColumnValues()
{
  // add columns with comas
  wstring result = L"";
  for (auto columnValue : mTargetTabel.newValueForColumns)
    result += columnValue + L", ";

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
