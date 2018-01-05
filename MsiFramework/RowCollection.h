#pragma once
#include "stdafx.h"
#include "Row.h"
#include "TableMetadata.h"

class RowCollection {
public:

  RowCollection(MSIHANDLE aDatabaseHandle, MSIHANDLE aViewHandle, const TableMetadata& aMetadata);
  
  unique_ptr<Row> operator[](int aRowNumber);
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

  int getNumberOfRows();

  bool addRow(map<wstring, wstring>& aRowData, MSIHANDLE aRowHandle, int rowNumber, vector<wstring>& columnNames);

private:
  TableMetadata mMetadata;
  vector<Row> mRowCollection;

  MSIHANDLE mViewHandle;
  MSIHANDLE mDatabaseHandle;
};
