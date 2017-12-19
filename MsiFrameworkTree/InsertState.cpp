#pragma once
#include "InsertState.h"

InsertState::InsertState(const DatabaseInfo& aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

std::unique_ptr<InsertState> InsertState::insertInColumnWithValue(const wstring& aColumnName, const wstring& aValue)
{
  mDatabaseInfo.insertInColumnValue(aColumnName, aValue);
  return make_unique<InsertState>(mDatabaseInfo);
}

UINT InsertState::insert()
{
  return mDatabaseInfo.insert();
}
