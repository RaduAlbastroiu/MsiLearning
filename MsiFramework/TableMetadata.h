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
  const MetadataSchema& operator[](const wstring& aColumnName) const;
  const MetadataSchema& getMetadataForColumn(const wstring& aColumnName) const;

  const wstring& getTableName() const;

private:

  const wstring mTableName;
  
  // collection of columns
  map<wstring, MetadataSchema> mMetadataCollection;

};
