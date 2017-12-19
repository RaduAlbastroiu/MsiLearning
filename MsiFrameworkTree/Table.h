#pragma once
#include "stdafx.h"
#include "Metadata.h"
#include "Row.h"
#include "RowCollection.h"

class Table
{
public:
  Table(const Metadata& aMetadata, const RowCollection& aRowCollection);

  // access metadata
  unique_ptr<MetadataSchema> getColumnInfo(const wstring& aColumnName);

  // access row
  unique_ptr<Row> operator[](int aRowNumber);
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

private:
  // access one column via columnName
  Metadata mTableSchema;

  RowCollection mRowCollection;
  
};