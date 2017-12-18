#pragma once
#include "stdafx.h"
#include "Node.h"
#include "SelectedState.h"
#include "Table.h"

class NeutralState : public Node
{
public:

  NeutralState(const DatabaseInfo& aDatabaseInfo);

  unique_ptr<Table> addTable(const wstring& aTableName);
  unique_ptr<NeutralState> addCondition(LogicCondition aCondition);
  unique_ptr<SelectedState> select();

};
