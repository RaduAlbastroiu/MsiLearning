#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class CreateTableState {
public:
  
  // constructor
  CreateTableState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<CreateTableState> addColumn(const wstring& aColumnName, const ColumnType& ColumnType);

  UINT addTableToDatabase();

private:
  DatabaseInfo mDatabaseInfo;
};