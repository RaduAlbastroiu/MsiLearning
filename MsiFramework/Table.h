#pragma once

#include "Condition.h"
#include "RecordCollection.h"

class Table
{
  MSIHANDLE mDatabaseHandle;
  MSIHANDLE mTableView;  
  wstring mTableName; 

  wstring composeSqlQuerry(Condition aCondition);

  

public:
  Table(wstring aTableName, MSIHANDLE aTableView, MSIHANDLE aDatabaseHandle);
  ~Table();

  RecordCollection getRecordCollection(Condition aCondition);
};


