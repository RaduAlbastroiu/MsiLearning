#pragma once
#include "stdafx.h"
#include "TableState.h"

TableState::TableState(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName)
  :mDatabaseInfo(aDatabaseInfo), mTableName(aTableName)
{
}

unique_ptr<ConditionState> updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mDatabaseInfo.storeColumnNameAndValueforUpdate(aColumnName, aNewValue);
}

unique_ptr<ConditionState> TableState::whereConditionIs(LogicCondition aCondition)
{
  mDatabaseInfo.condition = aCondition;
  return make_unique<Node>(mDatabaseInfo);
}

UINT TableState::deleteAllRows()
{
  return mDatabaseInfo.deleteAllRows();
}
