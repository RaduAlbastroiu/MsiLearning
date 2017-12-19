#pragma once
#include "stdafx.h"

class MetadataSchema
{
public:
  // constructor
  MetadataSchema(const wstring& aNameColumn, const wstring& aType, bool aIsKeyMember, bool aIsNullable);

  // mandatory for every table schema
  wstring mName;
  wstring mType;
  bool isKeyMember;
  bool isNullable;

private:
  // 0 - undefined
  // 1 - integer
  // 2 - wstring
  UINT mRealType;
};


class Metadata
{
public:
  Metadata();

  // add column
  void addColumnInSchema(const wstring& aNameColumn, const wstring& aType, bool aIsKeyMember, bool aIsNullable);

  // check info
  unique_ptr<MetadataSchema> operator[](const wstring& aColumnName);

private:

  // collection of columns
  map<wstring, MetadataSchema> mMetadataCollection;

};
