#include "stdafx.h"
#include "SingleRecord.h"


SingleRecord::SingleRecord(const MSIHANDLE aHandle, const MSIHANDLE aView, const wstring aValue):
  mHandle(aHandle), mView(aView), mValue(aValue)
{
}

SingleRecord::~SingleRecord()
{
}

wstring SingleRecord::getValue() const
{
  return mValue;
}

bool SingleRecord::setValue(wstring aValue)
{
  mValue = aValue;

  UINT errorMessage = ::MsiViewModify(mView, MSIMODIFY_REPLACE, mHandle);
  
  if (errorMessage == ERROR_SUCCESS)
    return true;

  return false;
}
