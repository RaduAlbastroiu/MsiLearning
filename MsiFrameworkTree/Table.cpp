#pragma once
#include "Table.h"

Table::Table(const Metadata & aMetadata, const RowCollection & aRowCollection)
  :mTableSchema(aMetadata), mRowCollection(aRowCollection)
{
}

unique_ptr<MetadataSchema> Table::operator[](const wstring & aColumnName)
{
  return mTableSchema[aColumnName];
}

std::unique_ptr<Row> Table::operator[](int aRowNumber)
{
  return mRowCollection[aRowNumber];
}
