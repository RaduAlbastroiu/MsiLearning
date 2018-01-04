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

unique_ptr<MetadataSchema> TableMetadata::operator[](const wstring& aColumnName)
{
  auto it = mMetadataCollection.find(aColumnName);
  if (it != mMetadataCollection.end())
    return make_unique<MetadataSchema>(it->second);

  return nullptr;
}

wstring TableMetadata::getTableName()
{
  return mTableName;
}


MetadataSchema::MetadataSchema(const wstring& aNameColumn, ColumnType aType, bool aIsKeyMember, bool aIsNullable)
  : mName(aNameColumn), mType(aType), isKeyMember(aIsKeyMember), isNullable(aIsNullable) 
{
}
