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

int RowCollection::getNumberOfRows()
{
  return mRowCollection.size();
}

bool RowCollection::addRow(map<wstring, wstring>& aRowData)
{

  map<wstring, Element> rowData;

  for (const auto& row : aRowData)
  {
    Element element(row.second, row.first, mMetadata.getTableName());
    
    element.setIsInt(mMetadata[row.first]->mType == ColumnType::Integer);
    element.setKeyMember(mMetadata[row.first]->isKeyMember);
    element.setNullable(mMetadata[row.first]->isNullable);

    rowData.insert(std::pair<wstring, Element>(row.first, element));
  }

  mRowCollection.push_back(Row(mMetadata, rowData));

  return true;
}
