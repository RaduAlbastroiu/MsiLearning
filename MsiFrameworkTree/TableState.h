#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"
#include "ConditionState.h"

class TableState
{
public:
  TableState(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName);

  // use columns
  template<typename... Types>
  unique_ptr<ConditionState> withColumns(const Types& ... aColumns)
  {
    mDatabaseInfo.addTableWithColumns(mTableName, aColumns...);
    return make_unique<ConditionState>(mDatabaseInfo);
  }

  unique_ptr<ConditionState> updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);

private:

  wstring mTableName;
  DatabaseInfo mDatabaseInfo;
};
