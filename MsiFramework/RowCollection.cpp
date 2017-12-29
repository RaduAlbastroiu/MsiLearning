#pragma once
#include "stdafx.h"
#include "RowCollection.h"

RowCollection::RowCollection(const TableMetadata& aMetadata)
  :mMetadata(aMetadata)
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

bool RowCollection::addRow(map<wstring, wstring>& aRowData)
{
  map<wstring, Element> rowData;

  for (const auto&[columnName, value] : aRowData)
  {
    Element element(value);
    
    element.setIsInt(mMetadata[columnName]->mType == ColumnType::Integer);
    element.setKeyMember(mMetadata[columnName]->isKeyMember);
    element.setNullable(mMetadata[columnName]->isNullable);

    rowData[columnName] = element;
  }

  mRowCollection.push_back(Row(mMetadata, rowData));

  return true;
}
