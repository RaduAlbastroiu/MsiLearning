#pragma once
#include "DatabaseInfo.h"

class InsertState
{
public:
  InsertState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<InsertState> insertInColumnWithValue(const wstring& aColumnName, const wstring& aValue);

  UINT insert();

private:
  DatabaseInfo mDatabaseInfo;
};
