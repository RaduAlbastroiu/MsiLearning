#pragma once
#include "stdafx.h"
#include "Node.h"

class SelectedState : public Node
{
public:

  SelectedState(const DatabaseInfo& aDatabaseInfo);
  vector<wstring> getColumn(const wstring& aColumnName);
  vector<vector<wstring>> getAll();
  
};
