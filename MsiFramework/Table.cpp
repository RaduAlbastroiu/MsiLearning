#pragma once
#include "stdafx.h"
#include "Table.h"

Table::Table(const TableMetadata & aMetadata, const RowCollection & aRowCollection)
  :mTableSchema(aMetadata), mRowCollection(aRowCollection)
{
}

unique_ptr<MetadataSchema> Table::getColumnInfo(const wstring & aColumnName)
{
  return mTableSchema[aColumnName];
}

std::unique_ptr<Row> Table::operator[](int aRowNumber)
{
  return mRowCollection[aRowNumber];
}

unique_ptr<Row> Table::getRowWithNumber(int aRowNumber)
{
  return mRowCollection[aRowNumber];
}
