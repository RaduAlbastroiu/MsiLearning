#include "stdafx.h"
#include "TableMetadata.h"

TableMetadata::TableMetadata(const wstring & aTableName)
  :mTableName(aTableName)
{
}

void TableMetadata::addColumnInSchema(const wstring& aNameColumn, ColumnType aType, bool aIsKeyMember, bool aIsNullable)
{
  auto newColumnInfo = MetadataSchema(aNameColumn, aType, aIsKeyMember, aIsNullable);
  mMetadataCollection.insert(pair<wstring, MetadataSchema>(aNameColumn, newColumnInfo));
}

const MetadataSchema& TableMetadata::operator[](const wstring& aColumnName) const
{
  auto it = mMetadataCollection.find(aColumnName);
  return it->second;
}

const MetadataSchema & TableMetadata::getMetadataForColumn(const wstring & aColumnName) const 
{
  auto it = mMetadataCollection.find(aColumnName);
  return it->second;
}

const wstring& TableMetadata::getTableName() const
{
  return mTableName;
}


MetadataSchema::MetadataSchema(const wstring& aNameColumn, ColumnType aType, bool aIsKeyMember, bool aIsNullable)
  : mName(aNameColumn), mType(aType), isKeyMember(aIsKeyMember), isNullable(aIsNullable) 
{
}
