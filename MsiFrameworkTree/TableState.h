#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class TableState
{
public:
  TableState(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName);

  // use columns
  template<typename... Types>
  unique_ptr<NeutralState> addColumns(const Types& ... aColumns)
  {
    mDatabaseInfo.addTableWithColumns(mTableName, aColumns...);
    return make_unique<NeutralState>(mDatabaseInfo);
  }

private:

  wstring mTableName;
  DatabaseInfo mDatabaseInfo;
};
