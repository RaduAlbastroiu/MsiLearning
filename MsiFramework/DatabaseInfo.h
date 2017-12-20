#pragma once
#include "stdafx.h"
#include "Table.h"
#include "LogicCondition.h"
#define SELECT L" SELECT "
#define UPDATE L" UPDATE "
#define DELETE L" DELETE "
#define INSERTINTO L" INSERT INTO "
#define VALUES L" VALUES "
#define SET L" SET "
#define FROM L" FROM "
#define WHERE L" WHERE "

// type class
enum class ColumnType {
  Integer,
  String
};

class DatabaseInfo
{
public:

  // default constructor
  DatabaseInfo(const wstring databasePath);

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
  UINT addColumn(const wstring& aColumnName, const ColumnType& aColumnType);
  UINT createTable(const wstring& aTableName);
  UINT addTableToDatabase();

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

  struct targetTable {
    // constructor
    targetTable() = default;
    targetTable(const wstring& aTableName, vector<wstring> aColumnCollection) 
      : tableName(aTableName), columnsCollection(aColumnCollection) {}

    wstring tableName;
    vector<wstring> columnsCollection;
    vector<wstring> newValueForColumns;
  };
  // single table
  targetTable mTargetTabel;

  Table createTableFromSqlQuerry(const wstring& sqlQuerry);

  wstring mDatabasePath;

  LogicCondition mCondition;
};
