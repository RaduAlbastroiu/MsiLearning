#pragma once
#include "stdafx.h"
#include "Metadata.h"

class Row
{
public:
  Row(const Metadata&  aMetadata, const map<wstring, Element> aRowData);

  // check info
  unique_ptr<Element> operator[](const wstring& aColumnName);

private:
  Metadata mMetadata;

  map<wstring, Element> mRowData;

};

// maybe extend
class Element
{
public:
  Element(const wstring& aValue) :mValue(aValue) {}

  wstring getAsString();
  void updateValue(const wstring& aNewValue);

private:
  wstring mValue;
};
