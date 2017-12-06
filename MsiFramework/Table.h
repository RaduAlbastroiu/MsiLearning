#pragma once

#include "Condition.h"
#include "Record.h"

class Table
{
  MSIHANDLE mDatabaseHandle;
  MSIHANDLE mTableView;  
  wstring mTableName; 

  wstring composeSqlQuerry(Condition aCondition);

public:
  Table(wstring aTableName, MSIHANDLE aTableView, MSIHANDLE aDatabaseHandle);
  ~Table();

  Record getRecord(Condition aCondition, bool& succeded);
};

