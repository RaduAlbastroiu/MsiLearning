#pragma once
#include "stdafx.h"
#include "Table.h"
#include "LogicCondition.h"
#include "MsiUtil.h"
#include "ErrorHandling.h"

#define SQLSELECT L" SELECT "
#define SQLUPDATE L" UPDATE "
#define SQLDELETE L" DELETE "
#define SQLINSERTINTO L" INSERT INTO "
#define SQLVALUES L" VALUES "
#define SQLSET L" SET "
#define SQLFROM L" FROM "
#define SQLWHERE L" WHERE "
#define SQLCREATE L" CREATE "
#define SQLTABLE L" TABLE "
#define SQLORDERBY L" ORDER BY "
#define SQLASC L" ASC ";
#define SQLDESC L" DESC ";

class IEvaluator;

struct targetMetadata {
  targetMetadata(const wstring& aName, const ColumnType aType, bool isKeyMember, bool isNullable)
    :mName(aName), mType(aType), isKeyMember(isKeyMember), isNullable(isNullable) 
  {
    if (mType == ColumnType::Integer)
      mTypeString = L" int ";
    if (mType == ColumnType::String)
      mTypeString = L" varchar(255) ";
  }

  wstring mName;
  wstring mTypeString;
  ColumnType mType;
  bool isKeyMember;
  bool isNullable;
};

struct targetColumn {
  targetColumn() :mMetadata(L"", ColumnType::String, true, true) {}
  targetColumn(const wstring& aColumnName) :mName(aColumnName), mMetadata(L"", ColumnType::String, true, true) {}

  targetMetadata mMetadata;
  UINT mNumber;
  wstring mName;
  wstring mNewValue;
};

struct targetTable {
  // constructor
  targetTable() = default;
  targetTable(const wstring& aTableName)
    : tableName(aTableName) {}
  // constructor with column names
  targetTable(const wstring& aTableName, vector<wstring> aColumnNames) 
    : tableName(aTableName)
  {
    for (auto& columnName : aColumnNames)
    {
      mColumnCollection.push_back(targetColumn(columnName));
    }
  }

  wstring tableName;

  vector<targetColumn> mColumnCollection;
};

class DatabaseInfo
{
public:

  // default constructor
  DatabaseInfo(const wstring& databasePath);
  DatabaseInfo(const MSIHANDLE handleToDatabase);

  // update condition with another condition ( add AND )
  // by default no condition
  void updateConditionWith(const LogicCondition& anotherCondition);
  
  // select
  void setTargetTable(const wstring& aTableName);

  template<typename T = function<bool(Row&)>>
  unique_ptr<Table> select(T op = [](Row&) { return true; })
  {

    wstring sqlSelectQuerry = selectSqlCondition();

    Table resultTable = createTableFromSqlQuerry(sqlSelectQuerry, op);

    return make_unique<Table>(resultTable);
  }

  // update
  UINT update();
  void updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);

  // delete
  UINT deleteRows();
  UINT deleteAllRows();

  // insert
  void insertInColumnValue(const wstring& aColumnName, const wstring& aValue);
  UINT insert();

  // create a table
  void createTable(const wstring& aTableName);
  void createColumn(const wstring& aColumnName, const ColumnType& aColumnType);
  void createNullableColumn(const wstring& aColumnName, const ColumnType& aColumntType);
  void createKeyColumn(const wstring& aColumnName, const ColumnType& aColumnType);
  UINT addTableToDatabase();

  // order by
  void orderBy(const wstring& aColumnName, bool ascending);

  // get property
  wstring getPropertyValue(const wstring& aPropertyName);
  UINT setPropertyValue(const wstring& aPropertyName, const wstring& aNewValue);

  // insert element in listbox
  void insertElementsInListBox(const wstring& listBoxProp, vector<wstring>& values);
  // insert element in combobox
  void insertElementsInComboBox(const wstring& comboBoxProp, vector<wstring>& values);

  // error handling
  bool isGood();
  wstring getLastError();

  // run any query
  UINT runSql(const wstring& aSqlQuerry);
  
  // set target table
  template<typename... Types>
  void addTableWithColumns(const Types... aColumns)
  {
    mTargetTabel = targetTable(mTargetTabel.tableName, vector<wstring>{ aColumns... });
  }

private: 

  // if opened from CustAct -> false
  bool isOpenFromDisk;

  UINT mErrorMessage = ERROR_SUCCESS;

  ErrorHandling mErrorHandling;

  wstring selectSqlCondition();
  wstring updateSqlCondition();
  wstring insertSqlCondition();

  wstring composeSqlQuerryTable();
  wstring composeSqlEnumerateColumns();
  wstring composeSqlEnumerateColumnValues();
  wstring composeSqlUpdateColumns();
  wstring composeSqlColumnTypes();
  wstring composeSqlCondition();

  void populateMetadataForTargetColumns(MSIHANDLE hView);
  TableMetadata generateMetadataFromTarget(const wstring& aTableName);

  template<typename T>
  RowCollection generateRowCollection(const TableMetadata& aTableMetadata, MSIHANDLE aHView, T op)
  {
    // create row collection
    RowCollection resultRowCollection(aHView);

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

        Element element(tableExtracted[i][j], columnName, aTableMetadata.getMetadataForColumn(columnName), mTargetTabel.mColumnCollection[j].mNumber, i + 1, false == isOpenFromDisk);

        element.setRowHandle(rowHandles[i]);
        element.setViewHandle(aHView);
        element.setDatabaseHandle(mDatabaseHandle);

        rowData.insert(pair<wstring, Element>(columnName, element));
      }

      Row row(rowData, rowHandles[i]);
      if (op(row))
      {
        resultRowCollection.addRow(row);
      }
    }

    return resultRowCollection;
  }

  // single table
  targetTable mTargetTabel;

  template<typename T>
  Table createTableFromSqlQuerry(const wstring& sqlSelect, T op)
  {
    MSIHANDLE hViewSelect;
    // open select view
    MsiUtil::openView(mDatabaseHandle, sqlSelect, hViewSelect);

    // takes target columns and get metadata
    // also set column nr
    populateMetadataForTargetColumns(hViewSelect);

    // generate real metadata obj for selected table
    auto metadata = generateMetadataFromTarget(mTargetTabel.tableName);

    // create rowCollection
    auto rowCollection = generateRowCollection(metadata, hViewSelect, op);

    Table t(metadata, rowCollection, hViewSelect);
    return t;
  }

  wstring mDatabasePath;

  MSIHANDLE mDatabaseHandle;
  MSIHANDLE mSessionInstall;

  wstring mOrderByCondition = L"";

  vector<LogicCondition> mConditions;
};
