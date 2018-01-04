#pragma once
#include "stdafx.h"
#include "Row.h"
#include "TableMetadata.h"

class RowCollection {
public:
  RowCollection(const TableMetadata& aMetadata);

  unique_ptr<Row> operator[](int aRowNumber);
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

  int getNumberOfRows();

  bool addRow(map<wstring, wstring>& aRowData);

private:
  TableMetadata mMetadata;
  vector<Row> mRowCollection;
};
