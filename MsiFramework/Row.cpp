#pragma once
#include "stdafx.h"
#include "Row.h"

Row::Row(const Metadata&  aMetadata, const map<wstring, Element> aRowData)
  :mMetadata(aMetadata), mRowData(aRowData)
{
}

unique_ptr<Element> Row::operator[](const wstring & aColumnName)
{
  auto it = mRowData.find(aColumnName);
  if (it != mRowData.end())
    return make_unique<Element>(it->second);

  return nullptr;
}

unique_ptr<Element> Row::getElementFromColumn(const wstring & aColumnName)
{
  auto it = mRowData.find(aColumnName);
  if (it != mRowData.end())
    return make_unique<Element>(it->second);

  return nullptr;
}

Element::Element(const wstring& aValue)
  :mValue(aValue)
{
}

wstring Element::getAsString()
{
  return mValue;
}
