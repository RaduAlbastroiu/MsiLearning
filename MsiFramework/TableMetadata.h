#pragma once
#include "stdafx.h"

// type class
enum class ColumnType
{
  Integer,
  String,
};

class MetadataSchema
{
public:
  // constructor
  MetadataSchema(const wstring& aNameColumn, ColumnType aType, bool aIsKeyMember, bool aIsNullable);

  // mandatory for every table schema
  wstring mName;
  ColumnType mType;
  bool isKeyMember;
  bool isNullable;

};


class TableMetadata
{
public:
  TableMetadata(const wstring& tableName);

  // add column
  void addColumnInSchema(const wstring& aNameColumn, ColumnType aType, bool aIsKeyMember, bool aIsNullable);

  // check info
  unique_ptr<MetadataSchema> operator[](const wstring& aColumnName);

  wstring getTableName();

private:

  wstring mTableName;
  
  // collection of columns
  map<wstring, MetadataSchema> mMetadataCollection;

};
