#include "NeutralState.h"

NeutralState::NeutralState(const DatabaseInfo & aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<Table> NeutralState::addTable(const wstring& aTableName)
{
  mDatabaseInfo.addTable(aTableName);
  return make_unique<Node>(mDatabaseInfo);
}

unique_ptr<NeutralState> NeutralState::addCondition(LogicCondition aCondition)
{
  mDatabaseInfo.condition = aCondition;
  return make_unique<Node>(mDatabaseInfo);
}

unique_ptr<SelectedState> NeutralState::select()
{
  // not implemented yet
  // mDatabaseInfo.select();
  return make_unique<Node>(mDatabaseInfo);
}
