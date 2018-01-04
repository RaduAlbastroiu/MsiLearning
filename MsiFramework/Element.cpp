#pragma once
#include "stdafx.h"
#include "Element.h"

Element::Element(const wstring & aValue, const wstring & aColumnName, const wstring & aTableName, MSIHANDLE aRowHandle, UINT aFieldNumber)
  :mValue(aValue), mColumn(aColumnName), mTable(aTableName), mRowHandle(aRowHandle), mFieldNumber(aFieldNumber)
{
}

wstring Element::getAsString()
{
  return mValue;
}

int Element::getAsInt()
{
  if (isInt())
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

wstring Element::getTable()
{
  return mTable;
}

wstring Element::getColumn()
{
  return mColumn;
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
