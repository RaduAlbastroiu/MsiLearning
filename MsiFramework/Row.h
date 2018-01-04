#pragma once
#include "stdafx.h"
#include "TableMetadata.h"
#include "Element.h"

class Row
{
public:
  Row(const TableMetadata&  aMetadata, const map<wstring, Element> aRowData, MSIHANDLE aROwHandle);

  // check info
  unique_ptr<Element> operator[](const wstring& aColumnName);
  unique_ptr<Element> getElementFromColumn(const wstring& aColumnName);

private:
  TableMetadata mMetadata;

  map<wstring, Element> mRowData;
  
  wstring mTableName;
  MSIHANDLE mRowHandle;
};
