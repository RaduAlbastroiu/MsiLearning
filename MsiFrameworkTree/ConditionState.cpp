#pragma once
#include "ConditionState.h"

ConditionState::ConditionState(const DatabaseInfo & aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<TableState> ConditionState::addTable(const wstring& aTableName)
{
  mDatabaseInfo.addTable(aTableName);
  return make_unique<Node>(mDatabaseInfo);
}

unique_ptr<ConditionState> ConditionState::whereConditionIs(LogicCondition aCondition)
{
  mDatabaseInfo.condition = aCondition;
  return make_unique<Node>(mDatabaseInfo);
}

unique_ptr<Table> ConditionState::select()
{
  return mDatabaseInfo.select();
}

UINT ConditionState::update()
{
  return mDatabaseInfo.update();
}

UINT ConditionState::deleteRows()
{
  return mDatabaseInfo.deleteRow();
}
