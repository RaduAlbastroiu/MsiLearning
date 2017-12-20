#pragma once
#include "stdafx.h"
#include "RowCollection.h"

RowCollection::RowCollection(const vector<Row>& aRowCollection, const Metadata& aMetadata)
  :mRowCollection(aRowCollection), mMetadata(aMetadata)
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

bool RowCollection::addRow(const map<wstring, Element>& aRowData)
{
  mRowCollection.push_back(Row(mMetadata, aRowData));

  // notify DatabaseInfo 
  return true;
}
