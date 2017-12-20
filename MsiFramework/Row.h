#pragma once
#include "stdafx.h"
#include "Metadata.h"


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
  Row(const Metadata&  aMetadata, const map<wstring, Element> aRowData);

  // check info
  unique_ptr<Element> operator[](const wstring& aColumnName);
  unique_ptr<Element> getElementFromColumn(const wstring& aColumnName);

private:
  Metadata mMetadata;

  map<wstring, Element> mRowData;

};
