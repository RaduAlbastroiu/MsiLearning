#pragma once
#include "stdafx.h"
#include "Table.h"
#include "LogicCondition.h"

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
  UINT insertInColumnValue(const wstring& aColumnName, const wstring& aValue);
  UINT insert();

  // create a table
  UINT addColumn(const wstring& aColumnName, const ColumnType& aColumnType);
  UINT createTable(const wstring& aTableName);
  UINT addTableToDatabase();

  // run any query
  UINT runSql(const wstring& aSqlQuerry);
  
  template<typename... Types>
  void addTableWithColumns(const wstring& aTableName, const Types... aColumns)
  {
    mTargetTabel = targetTable(aTableName, vector<wstring>{ aColumns... });
  }

private:

  UINT mErrorMessage = ERROR_SUCCESS;

  MSIHANDLE mDatabaseHandle;

  wstring selectSqlCondition();
  wstring updateSqlCondition();
  wstring composeSqlQuerryTables();
  wstring composeSqlQuerryColumns();

  struct targetTable {
    // constructor
    targetTable();
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
