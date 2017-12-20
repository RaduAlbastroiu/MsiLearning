#pragma once
#include "stdafx.h"
#include "TableMetadata.h"


// maybe extend
class Element
{
public:
  Element(const wstring& aValue);

  wstring getAsString();

private:
  wstring mValue;
};

class Row
{
public:
  Row(const TableMetadata&  aMetadata, const map<wstring, Element> aRowData);

  // check info
  unique_ptr<Element> operator[](const wstring& aColumnName);
  unique_ptr<Element> getElementFromColumn(const wstring& aColumnName);

private:
  TableMetadata mMetadata;

  map<wstring, Element> mRowData;

};
