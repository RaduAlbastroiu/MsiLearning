#pragma once
#include "stdafx.h"
#include "TableMetadata.h"


// maybe extend
class Element
{
public:
  Element(const wstring& aValue);

  wstring getAsString();
  int getAsInt();

  bool isNullable();
  bool isKeyMember();
  bool isInt();

  void setNullable(bool isNullable);
  void setKeyMember(bool isKeyMember);
  void setIsInt(bool isInt);

private:
  wstring mValue;
  bool mIsNullable;
  bool mIsKeyMember;
  bool mIsInt;
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
