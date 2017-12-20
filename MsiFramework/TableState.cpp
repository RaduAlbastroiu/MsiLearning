#pragma once
#include "stdafx.h"
#include "TableState.h"

TableState::TableState(const DatabaseInfo& aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<UpdateState> TableState::updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mDatabaseInfo.updateColumnWithValue(aColumnName, aNewValue);
  return make_unique<UpdateState>(mDatabaseInfo);
}

std::unique_ptr<InsertState> TableState::insertInColumnWithValue(const wstring& aColumnName, const wstring& aValue)
{
  mDatabaseInfo.insertInColumnValue(aColumnName, aValue);
  return make_unique<InsertState>(mDatabaseInfo);
}

unique_ptr<ConditionState> TableState::whereConditionIs(LogicCondition aCondition)
{
  mDatabaseInfo.updateConditionWith(aCondition);
  return make_unique<ConditionState>(mDatabaseInfo);
}

UINT TableState::deleteAllRows()
{
  return mDatabaseInfo.deleteAllRows();
}
