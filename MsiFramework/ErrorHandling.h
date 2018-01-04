#pragma once
#include "MsiUtil.h"

class ErrorHandling
{
public:
  wstring getLastError();
  bool isGood();
  void addError(const wstring& errorMessage);

private:
  wstring getError();
  wstring mError;
};
