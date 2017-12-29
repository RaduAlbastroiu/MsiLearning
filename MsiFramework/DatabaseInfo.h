#pragma once
#include "stdafx.h"
#include "Table.h"
#include "LogicCondition.h"
#include "MsiUtil.h"

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


struct TargetMetadata {
  TargetMetadata(const wstring& aName, const ColumnType aType, bool isKeyMember, bool isNullable)
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

struct targetTable {
  // constructor
  targetTable() = default;
  targetTable(const wstring& aTableName, vector<wstring> aColumnCollection)
    : tableName(aTableName), columnsCollection(aColumnCollection) {}

  wstring tableName;

  vector<wstring> columnsCollection;
  vector<wstring> newValueForColumns;
  vector<TargetMetadata> columnMetadata;
};

class DatabaseInfo
{
public:

  // default constructor
  DatabaseInfo(const wstring& databasePath);

  // update condition with another condition ( add AND )
  // by default no condition
  void updateConditionWith(const LogicCondition& anotherCondition);
  
  // select
  void setTargetTable(const wstring& aTableName);
  unique_ptr<Table> select();

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

  // DO NOT FORGET ABOUT 
  // UINT addRowInTable(Values);

  // run any query
  UINT runSql(const wstring& aSqlQuerry);
  
  template<typename... Types>
  void addTableWithColumns(const Types... aColumns)
  {
    mTargetTabel = targetTable(mTargetTabel.tableName, vector<wstring>{ aColumns... });
  }

private: 

  UINT mErrorMessage = ERROR_SUCCESS;

  MSIHANDLE mDatabaseHandle;

  wstring selectSqlCondition();
  wstring updateSqlCondition();
  wstring insertSqlCondition();

  wstring composeSqlQuerryTable();
  wstring composeSqlEnumerateColumns();
  wstring composeSqlEnumerateColumnValues();
  wstring composeSqlUpdateColumns();
  wstring composeSqlColumnTypes();
  wstring composeSqlCondition();

  void populateMetadataForTargetColumns(MSIHANDLE selectRecord);
  TableMetadata generateMetadataFromTarget();
  RowCollection generateRowCollection(const TableMetadata& aTableMetadata, MSIHANDLE selectRecord);

  // single table
  targetTable mTargetTabel;

  Table createTableFromSqlQuerry(const wstring& sqlQuerry);

  wstring mDatabasePath;

  vector<LogicCondition> mConditions;
};
