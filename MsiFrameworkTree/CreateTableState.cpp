#pragma once
#include "CreateTableState.h"



CreateTableState::CreateTableState(const DatabaseInfo& aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<CreateTableState> CreateTableState::addColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  mDatabaseInfo.addColumn(aColumnName, aColumnType);
  return make_unique<CreateTableState>(mDatabaseInfo);
}

UINT CreateTableState::addTableToDatabase()
{
  return mDatabaseInfo.addTableToDatabase();
}
