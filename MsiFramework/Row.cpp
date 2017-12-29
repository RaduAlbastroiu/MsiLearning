#pragma once
#include "stdafx.h"
#include "Row.h"


Element::Element(const wstring& aValue)
  :mValue(aValue)
{
}

wstring Element::getAsString()
{
  return mValue;
}

int Element::getAsInt()
{
  if (isInt)
    return stoi(mValue);
  else
    return 0xfffffff;
}

bool Element::isNullable()
{
  return mIsNullable;
}

bool Element::isKeyMember()
{
  return mIsKeyMember;
}

bool Element::isInt()
{
  return mIsInt;
}

void Element::setNullable(bool isNullable)
{
  mIsNullable = isNullable;
}

void Element::setKeyMember(bool isKeyMember)
{
  mIsKeyMember = isKeyMember;
}

void Element::setIsInt(bool isInt)
{
  mIsInt = isInt;
}

Row::Row(const TableMetadata&  aMetadata, const map<wstring, Element> aRowData)
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
