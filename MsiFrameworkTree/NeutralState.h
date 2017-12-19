#pragma once
#include "stdafx.h"
#include "SelectedState.h"
#include "DatabaseInfo.h"
#include "TableState.h"
#include "Table.h"

class NeutralState
{
public:
  NeutralState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<TableState> addTable(const wstring& aTableName);
  unique_ptr<NeutralState> addCondition(LogicCondition aCondition);
  unique_ptr<Table> select();

private:
  DatabaseInfo mDatabaseInfo;
};
