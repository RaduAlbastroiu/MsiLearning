#pragma once
#include "stdafx.h"
#include "ConditionState.h"
#include "TableState.h"
#include "UpdateState.h"


ConditionState::ConditionState(const DatabaseInfo & aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

ConditionState::~ConditionState() = default;

unique_ptr<ConditionState> ConditionState::whereConditionIs(const LogicCondition& aCondition)
{
  mDatabaseInfo.updateConditionWith(aCondition);
  return make_unique<ConditionState>(mDatabaseInfo);
}

std::unique_ptr<UpdateState> ConditionState::updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue)
{
  mDatabaseInfo.updateColumnWithValue(aColumnName, aNewValue);
  return make_unique<UpdateState>(mDatabaseInfo);
}

unique_ptr<Table> ConditionState::select()
{
  return mDatabaseInfo.select();
}

unique_ptr<ConditionState> ConditionState::orderByAsc(const wstring & aColumnName)
{
  mDatabaseInfo.orderBy(aColumnName, true);
  return make_unique<ConditionState>(mDatabaseInfo);
}
/*
unique_ptr<ConditionState> ConditionState::orderByDesc(const wstring & aColumnName)
{
  mDatabaseInfo.orderBy(aColumnName, false);
  return make_unique<ConditionState>(mDatabaseInfo);
}
*/

UINT ConditionState::deleteRows()
{
  return mDatabaseInfo.deleteRows();
}
