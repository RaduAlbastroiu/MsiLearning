#pragma once
#include "UpdateState.h"

UpdateState::UpdateState(const DatabaseInfo& aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<UpdateState> UpdateState::updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mDatabaseInfo.storeColumnNameAndValueforUpdate(aColumnName, aNewValue);
  return make_unique<UpdateState>(mDatabaseInfo);
}

UINT UpdateState::update()
{
  return mDatabaseInfo.update();
}
