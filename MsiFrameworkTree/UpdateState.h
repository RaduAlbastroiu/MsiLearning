#pragma once
#include "DatabaseInfo.h"
#include "ConditionState.h"

class UpdateState
{
public:
  UpdateState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<UpdateState> updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);

  UINT update();

private:
  DatabaseInfo mDatabaseInfo;
};
