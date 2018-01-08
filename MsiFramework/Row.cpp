#pragma once
#include "stdafx.h"
#include "TableMetadata.h"
#include "Row.h"

Row::Row(const map<wstring, Element> aRowData, MSIHANDLE aRowHandle)
  :mRowData(aRowData), mRowHandle(aRowHandle)
{
}

unique_ptr<Element> Row::operator[](const wstring & aColumnName)
{
  for (auto it = mRowData.begin(); it != mRowData.end(); it++)
  {
    if (it->first == aColumnName)
      return make_unique<Element>(it->second);
  }
  return nullptr;
}

unique_ptr<Element> Row::getElementFromColumn(const wstring & aColumnName)
{
  for (auto it = mRowData.begin(); it != mRowData.end(); it++)
  {
    if (it->first == aColumnName)
      return make_unique<Element>(it->second);
  }
  return nullptr;
}
