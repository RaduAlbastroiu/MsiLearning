#pragma once
#include "stdafx.h"
#include "Element.h"
#include "TableMetadata.h"

//template <class T>
Element::Element(const wstring & aValue, const wstring & aColumnName, const MetadataSchema & aColumnSchema, UINT aFieldNumber, UINT aRowNumber, bool aIsCustact)
  :mValue(aValue), mColumn(aColumnName), mColumnSchema(aColumnSchema), mFieldNumber(aFieldNumber), mRowNumber(aRowNumber), mIsFromCustact(aIsCustact)
{
}

wstring Element::getAsString()
{
  return mValue;
}

int Element::getAsInt()
{
  if (mColumnSchema.mType == ColumnType::Integer)
    return stoi(mValue);
  else
    return 0xffffffff;
}

//template<class T>
//T Element<T>::getValue()
//{
//  return mValue;
//}

//template<class T>
UINT Element::update(const wstring & aNewValue)
{
  UINT errorMessage = MsiUtil::setRecordString(mIsFromCustact, mDatabaseHandle, mViewHandle, mRowHandle, mRowNumber, mFieldNumber, aNewValue);
  if (errorMessage == ERROR_SUCCESS)
    mValue = aNewValue;
  return errorMessage;
}

//template<class T>
UINT Element::update(int aNewValue)
{
  UINT errorMessage = MsiUtil::setRecordInteger(mIsFromCustact, mDatabaseHandle, mViewHandle, mRowHandle, mRowNumber, mFieldNumber, aNewValue);
  if (errorMessage == ERROR_SUCCESS)
    mValue = to_wstring(aNewValue);
  return errorMessage;
}

//template<class T>
wstring Element::getTable()
{
  return mTable;
}

//template<class T>
wstring Element::getColumn()
{
  return mColumn;
}

const MetadataSchema& Element::getColumnMetadata()
{
  return mColumnSchema;
}

//template<class T>
void Element::setRowHandle(MSIHANDLE aRowHandle)
{
  mRowHandle = aRowHandle;
}

//template<class T>
void Element::setViewHandle(MSIHANDLE aViewHandle)
{
  mViewHandle = aViewHandle;
}

//template<class T>
void Element::setDatabaseHandle(MSIHANDLE aDatabaseHandle)
{
  mDatabaseHandle = aDatabaseHandle;
}
