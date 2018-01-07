#pragma once
#include "stdafx.h"
#include "Row.h"
#include "TableMetadata.h"

class RowCollection {
public:

  RowCollection(MSIHANDLE aDatabaseHandle, MSIHANDLE aViewHandle, const TableMetadata& aMetadata);
  
  // first index is 0
  unique_ptr<Row> operator[](int aRowNumber);
  // first index is 0
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

  int getNumberOfRows();

  bool addRow(map<wstring, Element>& aRowData, MSIHANDLE aRowHandle);

private:
  TableMetadata mMetadata;
  vector<Row> mRowCollection;

  MSIHANDLE mViewHandle;
  MSIHANDLE mDatabaseHandle;
};
