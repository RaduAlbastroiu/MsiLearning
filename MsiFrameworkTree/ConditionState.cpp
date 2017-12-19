#pragma once
#include "ConditionState.h"

ConditionState::ConditionState(const DatabaseInfo & aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<ConditionState> ConditionState::whereConditionIs(LogicCondition aCondition)
{
  mDatabaseInfo.updateConditionWith(aCondition);
  return make_unique<ConditionState>(mDatabaseInfo);
}

std::unique_ptr<UpdateState> ConditionState::updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mDatabaseInfo.storeColumnNameAndValueforUpdate(aColumnName, aNewValue);
  return make_unique<UpdateState>(mDatabaseInfo);
}

unique_ptr<Table> ConditionState::select()
{
  return mDatabaseInfo.select();
}

UINT ConditionState::deleteRows()
{
  return mDatabaseInfo.deleteRow();
}
