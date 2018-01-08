#pragma once
#include "stdafx.h"
#include "Element.h"
#include "TableMetadata.h"

Element::Element(const wstring & aValue, const wstring & aColumnName, const MetadataSchema & aColumnSchema, UINT aFieldNumber, UINT aRowNumber)
  :mValue(aValue), mColumn(aColumnName), mColumnSchema(aColumnSchema), mFieldNumber(aFieldNumber), mRowNumber(aRowNumber)
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
  return mColumnSchema.isNullable;
}

bool Element::isKeyMember()
{
  return mColumnSchema.isKeyMember;
}

bool Element::isInt()
{
  if(mColumnSchema.mType == ColumnType::Integer)
    return true;
  return false;
}

wstring Element::getTable()
{
  return mTable;
}

wstring Element::getColumn()
{
  return mColumn;
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
