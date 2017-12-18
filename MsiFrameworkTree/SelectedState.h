#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class SelectedState
{
public:

  SelectedState(const DatabaseInfo& aDatabaseInfo);
  vector<wstring> getColumn(const wstring& aColumnName);
  vector<vector<wstring>> getAll();
  
private:
  DatabaseInfo mDatabaseInfo;
};
