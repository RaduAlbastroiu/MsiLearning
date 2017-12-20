#include "stdafx.h"
#include "Metadata.h"

void Metadata::addColumnInSchema(const wstring& aNameColumn, const wstring& aType, bool aIsKeyMember, bool aIsNullable)
{
  auto newColumnInfo = MetadataSchema(aNameColumn, aType, aIsKeyMember, aIsNullable);
  mMetadataCollection.insert(pair<wstring, MetadataSchema>(aNameColumn, newColumnInfo));
}

unique_ptr<MetadataSchema> Metadata::operator[](const wstring& aColumnName)
{
  auto it = mMetadataCollection.find(aColumnName);
  if (it != mMetadataCollection.end())
    return make_unique<MetadataSchema>(it->second);

  return nullptr;
}


MetadataSchema::MetadataSchema(const wstring& aNameColumn, const wstring& aType, bool aIsKeyMember, bool aIsNullable)
  : mName(aNameColumn), mType(aType), isKeyMember(aIsKeyMember), isNullable(aIsNullable) 
{
}
