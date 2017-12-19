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
