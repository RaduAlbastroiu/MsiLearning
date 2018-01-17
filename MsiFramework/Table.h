#pragma once
#include "stdafx.h"
#include "TableMetadata.h"
#include "Row.h"
#include "RowCollection.h"

class Table
{
public:
  Table(const TableMetadata& aMetadata, const RowCollection& aRowCollection, const MSIHANDLE aTableHandle);

  // access metadata
  const MetadataSchema& getColumnInfo(const wstring& aColumnName);

  // last row is numberOrRows - 1
  int getNumberOfRows();

  // first index is 0
  unique_ptr<Row> operator[](int aRowNumber);

  // first index is 0
  unique_ptr<Row> getRowWithNumber(int aRowNumber);

  // TODO: get rid of i = 0; i < getNrOfRows and create an iterable range

private:
  // access one column via columnName
  TableMetadata mTableSchema;

  RowCollection mRowCollection;

  MSIHANDLE mTableHandle;
};
