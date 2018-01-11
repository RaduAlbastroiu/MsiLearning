#pragma once
#include "stdafx.h"
#include "TableState.h"
#include "CreateTableState.h"
#include "DatabaseInfo.h"
#include "OperationLogicCondition.h"

class Database
{
public:
  Database(const wstring& databasePath);
  Database(const MSIHANDLE handleToDatabase);

  // use table
  unique_ptr<TableState> inTable(const wstring& aTableName);

  // create table
  unique_ptr<CreateTableState> createTable(const wstring& aTableName);

  // run any custom sql
  UINT runSqlQuerry(const wstring& aSqlQuerry);

  // error handling
  wstring getLastError();
  bool isGood();

  // get value from property
  wstring getValueFromProperty(const wstring& aPropertyName);
  UINT setValueInProperty(const wstring& aPropertyName, const wstring& aNewValue);

private:
  wstring mDatabasePath;

  DatabaseInfo mDatabaseInfo;
};
