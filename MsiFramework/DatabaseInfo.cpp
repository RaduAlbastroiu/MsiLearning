#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

DatabaseInfo::DatabaseInfo(const wstring& aDatabasePath)
{
  mDatabasePath = aDatabasePath;

  LPCTSTR databasePath = aDatabasePath.c_str();
  mErrorMessage = ::MsiOpenDatabase(databasePath, MSIDBOPEN_DIRECT, &mDatabaseHandle);

}

void DatabaseInfo::updateConditionWith(const LogicCondition& anotherCondition)
{
  mConditions.push_back(anotherCondition);
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
  wstring sqlDeleteQuerry = SQLDELETE;
  sqlDeleteQuerry += SQLFROM;
  sqlDeleteQuerry += composeSqlQuerryTable();
  sqlDeleteQuerry += SQLWHERE;
  sqlDeleteQuerry += composeSqlCondition();

  return runSql(sqlDeleteQuerry);
}

UINT DatabaseInfo::deleteAllRows()
{
  wstring sqlDeleteQuerry = SQLDELETE;
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
  mTargetTabel.columnMetadata.push_back(TargetMetadata{ aColumnName, aColumnType, false, false });
}

void DatabaseInfo::createNullableColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.columnMetadata.push_back(TargetMetadata(aColumnName, aColumnType, false, true));
}

void DatabaseInfo::createKeyColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  mTargetTabel.columnsCollection.push_back(aColumnName);
  mTargetTabel.columnMetadata.push_back(TargetMetadata(aColumnName, aColumnType, true, false));
}

UINT DatabaseInfo::addTableToDatabase()
{
  // no working implementation
  /*
  wstring sqlCreateTableQuerry = SQLCREATE;
  sqlCreateTableQuerry += SQLTABLE;
  sqlCreateTableQuerry += L"( " + composeSqlColumnTypes() + L" )";
  */
  return runSql(L"");
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = SQLSELECT;
  sqlQuerry += composeSqlEnumerateColumns();
  sqlQuerry += SQLFROM;
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += SQLWHERE;
  sqlQuerry += composeSqlCondition();

  return sqlQuerry;
}

std::wstring DatabaseInfo::updateSqlCondition()
{
  wstring sqlQuerry = SQLUPDATE;
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += SQLSET;
  sqlQuerry += composeSqlUpdateColumns();
  sqlQuerry += SQLWHERE;
  sqlQuerry += composeSqlCondition();
  
  return sqlQuerry;
}

std::wstring DatabaseInfo::insertSqlCondition()
{
  wstring sqlInsertQuerry = SQLINSERTINTO;
  sqlInsertQuerry += composeSqlQuerryTable();
  sqlInsertQuerry += L" (" + composeSqlEnumerateColumns() + L")";
  sqlInsertQuerry += SQLVALUES;
  sqlInsertQuerry += L"( " + composeSqlEnumerateColumnValues() + L")";

  return sqlInsertQuerry;
}

std::wstring DatabaseInfo::composeSqlQuerryTable()
{
  wstring result = L"`";
  result += mTargetTabel.tableName;
  result += L"`";

  return result;
}

// column names
std::wstring DatabaseInfo::composeSqlEnumerateColumns()
{
  // add columns with comas
  wstring result = L"`";
  for (auto columnName : mTargetTabel.columnsCollection)
    result += columnName + L"`, `";
 
  // delete last coma
  result.pop_back();
  result.pop_back();
  result.pop_back();

  return result;
}

// column values
std::wstring DatabaseInfo::composeSqlEnumerateColumnValues()
{
  // add columns with comas
  wstring result = L"'";
  for (auto columnValue : mTargetTabel.newValueForColumns)
    result += columnValue + L"', '";

  // delete last coma
  result.pop_back();
  result.pop_back();
  result.pop_back();

  return result;
}

std::wstring DatabaseInfo::composeSqlUpdateColumns()
{
  // add columns = value with comas
  wstring result = L"`";
  for (size_t i = 0; i < mTargetTabel.columnsCollection.size(); i++)
  {
    result += mTargetTabel.columnsCollection[i] + L"` = '" + mTargetTabel.newValueForColumns[i] + L"', `";
  }

  // delete las coma
  result.pop_back();
  result.pop_back();
  result.pop_back();

  return result;
}

std::wstring DatabaseInfo::composeSqlColumnTypes()
{
  // add columns, dataType with comas
  wstring result = L"`";
  for (size_t i = 0; i < mTargetTabel.columnsCollection.size(); i++)
  {
    result += mTargetTabel.columnsCollection[i] + L"` = `" + mTargetTabel.columnMetadata[i].mTypeString + L"`, `";
  }

  // delete las coma
  result.pop_back();
  result.pop_back();
  result.pop_back();

  return result;
}

std::wstring DatabaseInfo::composeSqlCondition()
{
  // add condition AND condtion...
  wstring result = L"";
  for (const auto& condition : mConditions)
  {
    result += condition.getCondition() + L" AND ";
  }

  // delete last AND
  result.pop_back();
  result.pop_back();
  result.pop_back();
  result.pop_back();
  result.pop_back();

  return result;

}

void DatabaseInfo::populateMetadataForTargetColumns(MSIHANDLE selectRecord)
{
  map<wstring, wstring> columnsInfo;
  vector<wstring> primaryKeys;

  MsiUtil::getColumnsInfo(selectRecord, columnsInfo);
  MsiUtil::getPrimaryKeys(mDatabaseHandle, mTargetTabel.tableName, primaryKeys);

  mTargetTabel.columnsCollection.clear();
  for (const auto& [columnName, columnType] : columnsInfo)
  {
    mTargetTabel.columnsCollection.push_back(columnName);

    bool nullable = (columnType[0] < L'a');
    bool isKey = find(primaryKeys.begin(), primaryKeys.end(), columnName) != primaryKeys.end();

    bool isInt = (columnType[0] == L'i' || columnType[0] == L'j');

    if (isInt)
    {
      mTargetTabel.columnMetadata.push_back(TargetMetadata(columnName, ColumnType::Integer, isKey, nullable));
    }
    else
    {
      mTargetTabel.columnMetadata.push_back(TargetMetadata(columnName, ColumnType::String, isKey, nullable));
    }
  }
}

TableMetadata DatabaseInfo::generateMetadataFromTarget()
{
  auto tableMetadata = TableMetadata();

  for (auto& columnMetadata : mTargetTabel.columnMetadata)
  {
    tableMetadata.addColumnInSchema(columnMetadata.mName,
      columnMetadata.mType,
      columnMetadata.isKeyMember,
      columnMetadata.isNullable);
  }

  return tableMetadata;
}

RowCollection DatabaseInfo::generateRowCollection(const TableMetadata& aTableMetadata, MSIHANDLE aViewHandle)
{
  RowCollection resultRowCollection(aTableMetadata);

  vector<map<wstring, wstring>> tableData;
  MsiUtil::getSelectedTable(aViewHandle, mTargetTabel.columnsCollection, tableData);

  map<wstring, Element> rowData;
  for (const auto& row : tableData)
  {
    // map[wstring, wstring] -> map [wstring, Element]
    for (const auto&[columnName, value] : row)
    {
      Element element(value);
      rowData[columnName] = element;
    }

    // add map(row) to row collection
    resultRowCollection.addRow(rowData);
  }

  return resultRowCollection;
}

Table DatabaseInfo::createTableFromSqlQuerry(const wstring& sqlQuerry)
{
  MSIHANDLE viewHandle;
  // open select view
  MsiUtil::openView(mDatabaseHandle, sqlQuerry, viewHandle);

  // takes target columns and get metadata
  populateMetadataForTargetColumns(viewHandle);

  // generate real metadata obj for selected table
  auto metadata = generateMetadataFromTarget();

  // create rowCollection
  auto rowCollection = generateRowCollection(metadata, viewHandle);
  
  // populate row collection

  Table t(metadata, rowCollection);
  return t;
}

UINT DatabaseInfo::runSql(const wstring & aSqlQuerry)
{

  return MsiUtil::runSqlQuerryCommit(mDatabaseHandle, aSqlQuerry);

  //MSIHANDLE phView;
  //LPCTSTR sqlQuerry = aSqlQuerry.c_str();
  //wcout << aSqlQuerry << "\n\n";
  //
  //mErrorMessage = ::MsiDatabaseOpenView(mDatabaseHandle, sqlQuerry, &phView);
  //if (mErrorMessage == ERROR_SUCCESS)
  //{
  //  mErrorMessage = ::MsiViewExecute(phView, 0);
  //  if (mErrorMessage == ERROR_SUCCESS)
  //  {
  //    mErrorMessage = ::MsiDatabaseCommit(mDatabaseHandle);
  //    if (mErrorMessage == ERROR_SUCCESS)
  //    {
  //      return ERROR_SUCCESS;
  //    }
  //  }
  //}
  //return mErrorMessage;
}
