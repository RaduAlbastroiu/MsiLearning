#pragma once
#include "stdafx.h"
#include "ConditionState.h"
#include "UpdateState.h"
#include "InsertState.h"
#include "DatabaseInfo.h"

class TableState
{
public:
  TableState(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName);
  ~TableState() = default;

  // use columns
  template<typename... Types>
  unique_ptr<ConditionState> withColumns(const Types& ... aColumns)
  {
    mDatabaseInfo.addTableWithColumns(mTableName, aColumns...);
    return make_unique<ConditionState>(mDatabaseInfo);
  }

  unique_ptr<UpdateState> updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);
  unique_ptr<InsertState> insertInColumnWithValue(const wstring& aColumnName, const wstring& aValue);
  unique_ptr<ConditionState> whereConditionIs(LogicCondition aCondition);
  UINT deleteAllRows();

private:

  wstring mTableName;
  DatabaseInfo mDatabaseInfo;
};
