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

  // open the database
  bool openDatabase(const wstring databasePath);

  // update condition with another condition ( add AND )
  // by default no condition
  void updateConditionWith(const LogicCondition& anotherCondition);
  
  // select
  unique_ptr<Table> select();

  // update
  UINT update();
  void storeColumnNameAndValueforUpdate(const wstring& aColumnName, const wstring& aNewValue);

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
  bool runSql(const wstring& aSqlQuerry);
  
  template<typename... Types>
  void addTableWithColumns(const wstring& aTableName, const Types... aColumns)
  {
    mTargetTabel = targetTable(aTableName, vector<wstring>{ aColumns... });
  }

private:

  UINT mErrorMessage = ERROR_SUCCESS;

  MSIHANDLE mDatabaseHandle;

  wstring selectSqlCondition();
  wstring composeSqlQuerryTables();
  wstring composeSqlQuerryColumns();

  struct targetTable {
    // constructor
    targetTable(const wstring& aTableName, vector<wstring> aColumnCollection) 
      : tableName(aTableName), columnsCollection(aColumnCollection) {}

    wstring tableName;
    vector<wstring> columnsCollection;
  };
  // single table
  targetTable mTargetTabel;

  Table createTableFromSqlQuerry(const wstring& sqlQuerry);

  wstring databasePath;

  LogicCondition mCondition;
};
