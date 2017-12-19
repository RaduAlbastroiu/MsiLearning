#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class SelectedState
{
public:

  SelectedState(const DatabaseInfo& aDatabaseInfo);
 
  vector<vector<wstring>> getAll();
  
private:
  DatabaseInfo mDatabaseInfo;
};
