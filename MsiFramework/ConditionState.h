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

  template<typename T = function<bool(Row&)>>
  unique_ptr<Table> select(T op = [](Row&) { return true; }) { return mDatabaseInfo.select(op); }

  unique_ptr<ConditionState> orderByAsc(const wstring& aColumnName);
  //unique_ptr<ConditionState> orderByDesc(const wstring& aColumnName);
  
  UINT deleteRows();

private:
  DatabaseInfo mDatabaseInfo;
};

