#pragma once
#include "stdafx.h"
#include "Row.h"

class RowCollection {
public:

  RowCollection(MSIHANDLE aViewHandle);
  
  // first index is 0
  unique_ptr<Row> operator[](int aRowNumber);
  // first index is 0
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

  int getNumberOfRows();

  bool addRow(map<wstring, Element>& aRowData, MSIHANDLE aRowHandle);

  //UINT commitUpdates();

private:
  vector<Row> mRowCollection;

  MSIHANDLE mViewHandle;
};
