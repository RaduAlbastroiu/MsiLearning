#pragma once
#include "stdafx.h"
#include "Row.h"
#include "TableMetadata.h"

class RowCollection {
public:
  RowCollection(const TableMetadata& aMetadata);

  unique_ptr<Row> operator[](int aRowNumber);
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

  bool addRow(const map<wstring, Element>& aRowData);

private:
  TableMetadata mMetadata;
  vector<Row> mRowCollection;
};
