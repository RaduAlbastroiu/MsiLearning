#pragma once
#include "DatabaseInfo.h"
#include "Table.h"

class TableState;
class UpdateState;

class ConditionState
{
public:
  ConditionState(const DatabaseInfo& aDatabaseInfo);

  ~ConditionState();

  unique_ptr<ConditionState> whereConditionIs(const LogicCondition& aCondition);
  unique_ptr<UpdateState> updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);
  unique_ptr<Table> select();
  UINT deleteRows();

private:
  DatabaseInfo mDatabaseInfo;
};
