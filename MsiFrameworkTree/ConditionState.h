#pragma once
#include "stdafx.h"
#include "SelectedState.h"
#include "DatabaseInfo.h"
#include "TableState.h"
#include "Table.h"

class ConditionState
{
public:
  ConditionState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<ConditionState> whereConditionIs(LogicCondition aCondition);
  unique_ptr<Table> select();
  UINT update();
  UINT deleteRows();

private:
  DatabaseInfo mDatabaseInfo;
};
