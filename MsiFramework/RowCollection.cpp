#pragma once
#include "stdafx.h"
#include "RowCollection.h"

RowCollection::RowCollection(MSIHANDLE aViewHandle)
  :mViewHandle(aViewHandle)
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

  mRowCollection.push_back(Row(aRowData, aRowHandle));

  return true;
}

//UINT RowCollection::commitUpdates()
//{
//  vector<vector<pair<UINT, 
//  for (auto& row : mRowCollection)
//  {
//
//  }
//}
