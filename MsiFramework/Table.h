#pragma once
#include "stdafx.h"
#include "TableMetadata.h"
#include "Row.h"
#include "RowCollection.h"
#include "UpdaterDatabase.h"

class Table
{
public:
  Table(const TableMetadata& aMetadata, const RowCollection& aRowCollection, const MSIHANDLE aDatabaseHandle);

  // access metadata
  unique_ptr<MetadataSchema> getColumnInfo(const wstring& aColumnName);

  // access row
  int getNumberOfRows();
  unique_ptr<Row> operator[](int aRowNumber);
  unique_ptr<Row> getRowWithNumber(int aRowNumber);


private:
  // access one column via columnName
  TableMetadata mTableSchema;

  RowCollection mRowCollection;

  UpdaterDatabase mUpdater;
  
};
