#pragma once
#include "stdafx.h"
#include "ErrorHandling.h"

wstring ErrorHandling::getLastError()
{
  if (mError.size() == 0)
  {
    MsiUtil::getLastError(mError);
  }

  return mError;
}

bool ErrorHandling::isGood()
{
  wstring error = getError();
  if (error.size())
    return false;
  return true;
}

void ErrorHandling::addError(const wstring & aErrorMessage)
{
  mError = aErrorMessage;
}

wstring ErrorHandling::getError()
{
  MsiUtil::getLastError(mError);

  return mError;
}
