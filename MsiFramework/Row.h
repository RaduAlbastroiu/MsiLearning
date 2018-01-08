#pragma once
#include "stdafx.h"
#include "Element.h"

class Row
{
public:
  Row(const map<wstring, Element> aRowData, MSIHANDLE aROwHandle);

  // check info
  unique_ptr<Element> operator[](const wstring& aColumnName);
  unique_ptr<Element> getElementFromColumn(const wstring& aColumnName);

private:

  map<wstring, Element> mRowData;
  
  MSIHANDLE mRowHandle;
};
