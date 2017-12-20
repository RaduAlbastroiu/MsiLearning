#pragma once
#include "stdafx.h"
#include "CreateTableState.h"


CreateTableState::CreateTableState(const DatabaseInfo& aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<CreateTableState> CreateTableState::createColumn(const wstring& aColumnName, const ColumnType& aColumnType)
{
  mDatabaseInfo.createColumn(aColumnName, aColumnType);
  return make_unique<CreateTableState>(mDatabaseInfo);
}

UINT CreateTableState::addTableToDatabase()
{
  return mDatabaseInfo.addTableToDatabase();
}
