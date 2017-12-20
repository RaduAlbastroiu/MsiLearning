#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class SelectedState
{
public:

  SelectedState(const DatabaseInfo& aDatabaseInfo);
 
  unique_ptr<Row> getRow(int aRowNumber);
  unique_ptr<MetadataSchema> getColumnInfo(const wstring& aColumnName);
  
private:
  DatabaseInfo mDatabaseInfo;
};
