#pragma once
#include "stdafx.h"
#include "Row.h"
#include "Metadata.h"

class RowCollection {
public:
  RowCollection(const vector<Row>& aRowCollection, const Metadata& aMetadata);

  unique_ptr<Row> operator[](int aRowNumber);

  bool addRow(const map<wstring, Element>& aRowData);

private:
  Metadata mMetadata;
  vector<Row> mRowCollection;
};
