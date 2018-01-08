#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

DatabaseInfo::DatabaseInfo(const wstring& aDatabasePath)
{
  mDatabasePath = aDatabasePath;
  isOpenFromDisk = true;
  MsiUtil::openDatabase(aDatabasePath, mDatabaseHandle);
}

DatabaseInfo::DatabaseInfo(const MSIHANDLE hSession)
{
  mDatabaseHandle = MsiUtil::openActiveDatabase(hSession);
  isOpenFromDisk = false;
  mDatabasePath = L"";
}

void DatabaseInfo::updateConditionWith(const LogicCondition& anotherCondition)
{
  mConditions.push_back(anotherCondition);
}

void DatabaseInfo::setTargetTable(const wstring& aTableName)
{
  mTargetTabel = targetTable(aTableName);
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
  // create target column
  targetColumn t;
  t.mName = aColumnName;
  t.mNewValue = aNewValue;

  // add to collection
  mTargetTabel.mColumnCollection.push_back(t);
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
  // create target column
  targetColumn t;
  t.mName = aColumnName;
  t.mNewValue = aValue;

  // add to collection
  mTargetTabel.mColumnCollection.push_back(t);
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
  // create target column
  targetColumn t;
  t.mName = aColumnName;
  t.mMetadata = targetMetadata{ aColumnName, aColumnType, false, false };
 
  // add to collection
  mTargetTabel.mColumnCollection.push_back(t);
}

void DatabaseInfo::createNullableColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  // create target column
  targetColumn t;
  t.mName = aColumnName;
  t.mMetadata = targetMetadata{ aColumnName, aColumnType, false, true };

  // add to collection
  mTargetTabel.mColumnCollection.push_back(t);
}

void DatabaseInfo::createKeyColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  // create target column
  targetColumn t;
  t.mName = aColumnName;
  t.mMetadata = targetMetadata{ aColumnName, aColumnType, true, false };

  // add to collection
  mTargetTabel.mColumnCollection.push_back(t);
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

void DatabaseInfo::orderBy(const wstring & aColumnName, bool /*ascending*/)
{
  if (mOrderByCondition.size())
  {
    mOrderByCondition += L", ";
  }

  mOrderByCondition += L"`" + aColumnName + L"` ";
  /*
  if (ascending)
  {
    mOrderByCondition += SQLASC;
  }
  else
  {
    mOrderByCondition += SQLDESC;
  }
  */
}

UINT DatabaseInfo::order()
{
  wstring sqlQuery = selectSqlCondition();
  sqlQuery += L" ORDER BY " + mOrderByCondition;

  return runSql(sqlQuery);
}

bool DatabaseInfo::isGood()
{
  return mErrorHandling.isGood();
}

wstring DatabaseInfo::getLastError()
{
  return mErrorHandling.getLastError();
}

std::wstring DatabaseInfo::selectSqlCondition()
{
  wstring sqlQuerry = SQLSELECT;

  /*
  Select all columns if working on CustAct
  Select only the needed column if working on disk
  */
  if (isOpenFromDisk)
  {
    sqlQuerry += composeSqlEnumerateColumns();
  }
  else
  {
    //  If the framework is opened from CustAct only temporary modifications are made
    sqlQuerry += L" * ";
  }

  sqlQuerry += SQLFROM;
  sqlQuerry += composeSqlQuerryTable();
  wstring condition = composeSqlCondition();
  if (condition.size())
  {
    sqlQuerry += SQLWHERE;
    sqlQuerry += condition;
  }

  return sqlQuerry;
}

std::wstring DatabaseInfo::updateSqlCondition()
{
  wstring sqlQuerry = SQLUPDATE;
  sqlQuerry += composeSqlQuerryTable();
  sqlQuerry += SQLSET;
  sqlQuerry += composeSqlUpdateColumns();
  
  wstring condition = composeSqlCondition();
  if (condition.size())
  {
    sqlQuerry += SQLWHERE;
    sqlQuerry += condition;
  }
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
  wstring result = L"";
  for (auto column : mTargetTabel.mColumnCollection)
    result += L"`" + column.mName + L"`, ";
 
  // delete last coma
  if (result.size())
  {
    result.pop_back();
    result.pop_back();
  }
  else
  {
    result = L"*";
  }

  return result;
}

// column values
std::wstring DatabaseInfo::composeSqlEnumerateColumnValues()
{
  // add columns with comas
  wstring result = L"'";
  for (auto column : mTargetTabel.mColumnCollection)
    result += column.mNewValue + L"', '";

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
  for (const auto& column : mTargetTabel.mColumnCollection)
  {
    result += column.mName + L"` = '" + column.mNewValue + L"` = '";
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
  for (const auto& column : mTargetTabel.mColumnCollection)
  {
    result += column.mName + L"` = '" + column.mMetadata.mTypeString + L"` = '";
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
  if (result.size())
  {
    result.pop_back();
    result.pop_back();
    result.pop_back();
    result.pop_back();
    result.pop_back();
  }
  return result;

}

void DatabaseInfo::populateMetadataForTargetColumns(MSIHANDLE selectRecord)
{
  // first: column name
  // second: column type
  vector<pair<wstring, wstring>> columnsInfo;
  vector<wstring> primaryKeys;

  MsiUtil::getColumnsInfo(selectRecord, columnsInfo);
  MsiUtil::getPrimaryKeys(mDatabaseHandle, mTargetTabel.tableName, primaryKeys);

  for (auto& aTargetColumn : mTargetTabel.mColumnCollection)
  {
    UINT columnNr = 0;
    for (;columnNr < columnsInfo.size(); columnNr++)
    {
      auto extractedColumnName = columnsInfo[columnNr].first;
      auto extractedColumnType = columnsInfo[columnNr].second;

      if (aTargetColumn.mName == extractedColumnName)
      {
        // starts from 1 to n
        aTargetColumn.mNumber = columnNr + 1;
        bool nullable = (extractedColumnType[0] < L'a');
        bool isKey = find(primaryKeys.begin(), primaryKeys.end(), extractedColumnName) != primaryKeys.end();

        bool isInt = (extractedColumnType[0] == L'i' || extractedColumnType[0] == L'j');

        if (isInt)
        {
          aTargetColumn.mMetadata = targetMetadata(extractedColumnName, ColumnType::Integer, isKey, nullable);
        }
        else
        {
          aTargetColumn.mMetadata = targetMetadata(extractedColumnName, ColumnType::String, isKey, nullable);
        }
      }
    }
  }
}

TableMetadata DatabaseInfo::generateMetadataFromTarget(const wstring& aTableName)
{
  auto tableMetadata = TableMetadata(aTableName);

  for (auto& column : mTargetTabel.mColumnCollection)
  {
    tableMetadata.addColumnInSchema(column.mMetadata.mName,
      column.mMetadata.mType,
      column.mMetadata.isKeyMember,
      column.mMetadata.isNullable);
  }

  return tableMetadata;
}

RowCollection DatabaseInfo::generateRowCollection(const TableMetadata& aTableMetadata, MSIHANDLE aHView)
{
  // create row collection
  RowCollection resultRowCollection(mDatabaseHandle, aHView, aTableMetadata);

  vector<MSIHANDLE> rowHandles;
  vector<vector<wstring>> tableExtracted;
  vector<UINT> columnNumbers;
  for (const auto& column : mTargetTabel.mColumnCollection)
    columnNumbers.push_back(column.mNumber);

  MsiUtil::getSelectedTable(aHView, columnNumbers, tableExtracted, rowHandles);

  // create row collection
  for (size_t i = 0; i < tableExtracted.size(); i++)
  {
    // create row
    map<wstring, Element> rowData;
    for (size_t j = 0; j < tableExtracted[i].size(); j++)
    {
      wstring columnName = mTargetTabel.mColumnCollection[j].mName;
      
      Element element(tableExtracted[i][j], columnName, mTargetTabel.tableName, mTargetTabel.mColumnCollection[j].mNumber, i + 1);

      element.setOpenFromCustAct(!/* is not */isOpenFromDisk);

      element.setRowHandle(rowHandles[i]);
      element.setViewHandle(aHView);
      element.setDatabaseHandle(mDatabaseHandle);


      element.setIsInt(mTargetTabel.mColumnCollection[j].mMetadata.mType == ColumnType::Integer);
      element.setKeyMember(mTargetTabel.mColumnCollection[j].mMetadata.isKeyMember);
      element.setNullable(mTargetTabel.mColumnCollection[j].mMetadata.isNullable);

      rowData.insert(pair<wstring, Element>(columnName, element));
    }

    resultRowCollection.addRow(rowData, rowHandles[i]);
  }

  return resultRowCollection;
}

Table DatabaseInfo::createTableFromSqlQuerry(const wstring& sqlSelect)
{
  MSIHANDLE hViewSelect;
  // open select view
  MsiUtil::openView(mDatabaseHandle, sqlSelect, hViewSelect);

  // takes target columns and get metadata
  populateMetadataForTargetColumns(hViewSelect);

  // generate real metadata obj for selected table
  auto metadata = generateMetadataFromTarget(mTargetTabel.tableName);

  // create rowCollection
  auto rowCollection = generateRowCollection(metadata, hViewSelect);

  Table t(metadata, rowCollection, hViewSelect);
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
