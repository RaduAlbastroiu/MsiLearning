#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class CreateTableState {
public:
  
  // constructor
  CreateTableState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<CreateTableState> createColumn(const wstring& aColumnName, const ColumnType& ColumnType);
  unique_ptr<CreateTableState> createNullableColumn(const wstring& aColumnName, const ColumnType& aColumntType);
  unique_ptr<CreateTableState> createKeyColumn(const wstring& aColumnName, const ColumnType& aColumnType);

  UINT addTableToDatabase();

private:
  DatabaseInfo mDatabaseInfo;
};
