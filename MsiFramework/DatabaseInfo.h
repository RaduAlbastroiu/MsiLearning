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

  struct targetTable {
    // constructor
    targetTable() = default;
    targetTable(const wstring& aTableName, vector<wstring> aColumnCollection) 
      : tableName(aTableName), columnsCollection(aColumnCollection) {}

    wstring tableName;

    struct Metadata {
      Metadata(const wstring& aName, const wstring& aType, bool isKeyMember, bool isNullable)
        :mName(aName), mType(aType), isKeyMember(isKeyMember), isNullable(isNullable) {}
      
      wstring mName;
      wstring mType;
      bool isKeyMember;
      bool isNullable;
    };

    vector<wstring> columnsCollection;
    vector<wstring> newValueForColumns;
    vector<Metadata> columnMetadata;
  };
  // single table
  targetTable mTargetTabel;

  Table createTableFromSqlQuerry(const wstring& sqlQuerry);

  wstring mDatabasePath;

  LogicCondition mCondition;
};
