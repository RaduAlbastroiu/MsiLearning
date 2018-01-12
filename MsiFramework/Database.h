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
  // set value in property
  UINT setValueInProperty(const wstring& aPropertyName, const wstring& aNewValue);

  // insert element in listbox
  void insertElementsInListBox(const wstring& listBoxProp, vector<wstring>& values);
  // insert element in combobox
  void insertElementsInComboBox(const wstring& comboBoxProp, vector<wstring>& values);

private:
  wstring mDatabasePath;

  DatabaseInfo mDatabaseInfo;
};
