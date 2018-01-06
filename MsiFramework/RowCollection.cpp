#pragma once
#include "stdafx.h"
#include "RowCollection.h"

RowCollection::RowCollection(MSIHANDLE aDatabaseHandle, MSIHANDLE aViewHandle, const TableMetadata& aMetadata)
  :mDatabaseHandle(aDatabaseHandle), mMetadata(aMetadata), mViewHandle(aViewHandle)
{
}

unique_ptr<Row> RowCollection::operator[](int aRowNumber)
{
  if (static_cast<size_t>(aRowNumber) >= mRowCollection.size())
    return nullptr;
  return make_unique<Row>(mRowCollection[aRowNumber]);
}

unique_ptr<Row> RowCollection::getRowWithNumber(int aRowNumber)
{
  if (static_cast<size_t>(aRowNumber) >= mRowCollection.size())
    return nullptr;
  return make_unique<Row>(mRowCollection[aRowNumber]);
}

int RowCollection::getNumberOfRows()
{
  return mRowCollection.size();
}

bool RowCollection::addRow(map<wstring, Element>& aRowData, MSIHANDLE aRowHandle)
{

  mRowCollection.push_back(Row(mMetadata, aRowData, aRowHandle));

  return true;
}
