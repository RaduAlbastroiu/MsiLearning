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

bool RowCollection::addRow(Row& aRow)
{

  mRowCollection.push_back(aRow);

  return true;
}

vector<Row>::iterator RowCollection::begin()
{
  return mRowCollection.begin();
}

vector<Row>::iterator RowCollection::end()
{
  return mRowCollection.end();
}

//UINT RowCollection::commitUpdates()
//{
//  vector<vector<pair<UINT, 
//  for (auto& row : mRowCollection)
//  {
//
//  }
//}
