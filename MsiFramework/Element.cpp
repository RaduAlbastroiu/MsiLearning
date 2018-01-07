#pragma once
#include "stdafx.h"
#include "Element.h"

Element::Element(const wstring & aValue, const wstring & aColumnName, const wstring & aTableName, UINT aFieldNumber, UINT aRowNumber)
  :mValue(aValue), mColumn(aColumnName), mTable(aTableName), mFieldNumber(aFieldNumber), mRowNumber(aRowNumber)
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
    return 0xffffffff;
}

UINT Element::update(const wstring & aNewValue)
{
  UINT errorMessage = MsiUtil::setRecordString(mIsFromCustact, mDatabaseHandle, mViewHandle, mRowHandle, mRowNumber, mFieldNumber, aNewValue);
  if (errorMessage == ERROR_SUCCESS)
    mValue = aNewValue;
  return errorMessage;
}

UINT Element::update(int aNewValue)
{
  UINT errorMessage = MsiUtil::setRecordInteger(mIsFromCustact, mDatabaseHandle, mViewHandle, mRowHandle, mRowNumber, mFieldNumber, aNewValue);
  if (errorMessage == ERROR_SUCCESS)
    mValue = to_wstring(aNewValue);
  return errorMessage;
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

void Element::setOpenFromCustAct(bool isCustAct)
{
  mIsFromCustact = isCustAct;
}

void Element::setRowHandle(MSIHANDLE aRowHandle)
{
  mRowHandle = aRowHandle;
}

void Element::setViewHandle(MSIHANDLE aViewHandle)
{
  mViewHandle = aViewHandle;
}

void Element::setDatabaseHandle(MSIHANDLE aDatabaseHandle)
{
  mDatabaseHandle = aDatabaseHandle;
}
