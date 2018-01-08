#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class SelectedState
{
public:

  SelectedState(const DatabaseInfo& aDatabaseInfo);
 
  unique_ptr<Row> getRow(int aRowNumber);
  
private:
  DatabaseInfo mDatabaseInfo;
};
