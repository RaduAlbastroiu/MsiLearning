#pragma once
#include "stdafx.h"
#include "Table.h"

Table::Table(const TableMetadata & aMetadata, const RowCollection & aRowCollection, const MSIHANDLE aTableHandle)
  :mTableSchema(aMetadata), mRowCollection(aRowCollection), mTableHandle(aTableHandle)
{
}

const MetadataSchema& Table::getColumnInfo(const wstring & aColumnName)
{
  return mTableSchema[aColumnName];
}

int Table::getNumberOfRows()
{
  return mRowCollection.getNumberOfRows();
}

std::unique_ptr<Row> Table::operator[](int aRowNumber)
{
  return mRowCollection[aRowNumber];
}

unique_ptr<Row> Table::getRowWithNumber(int aRowNumber)
{
  return mRowCollection.getRowWithNumber(aRowNumber);
}
