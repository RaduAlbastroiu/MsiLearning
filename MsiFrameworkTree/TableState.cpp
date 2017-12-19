#pragma once
#include "stdafx.h"
#include "TableState.h"

TableState::TableState(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName)
  :mDatabaseInfo(aDatabaseInfo), mTableName(aTableName)
{
}

unique_ptr<UpdateState> updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mDatabaseInfo.storeColumnNameAndValueforUpdate(aColumnName, aNewValue);
}

std::unique_ptr<InsertState> UpdateState::insertInColumnWithValue(const wstring& aColumnName, const wstring& aValue)
{
  mDatabaseInfo.insertInColumnValue(aColumnName, aValue);
  return make_unique<InsertState>(mDatabaseInfo);
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
