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
    tableCollection.push_back(aTableName, vector<wstring>{ aColumns... });
  }

  void storeColumnNameAndValueforUpdate(const wstring& aColumnName, const wstring& aNewValue);

private:

  UINT mErrorMessage = ERROR_SUCCESS;

  MSIHANDLE mDatabaseHandle;

  wstring composeSqlQuerryTables();
  wstring composeSqlQuerryColumns();
  wstring selectSqlCondition();

  vector<Table> tableCollection;

  wstring databasePath;

  LogicCondition condition;

  vector<pair<wstring, wstring>> updateColumnNameWithValueCollection;
};
