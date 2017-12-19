#include "Metadata.h"

Metadata::Metadata(const wstring & aName, const wstring & aType, bool aIsKeyMember, bool aIsNullable)
{
}

void Metadata::addColumnInSchema(const wstring& aNameColumn, const wstring& aType, bool aIsKeyMember, bool aIsNullable)
{
  auto newColumnInfo = MetadataSchema(aNameColumn, aType, aIsKeyMember, aIsNullable);
  MetadataSchema[aNameColumn] = newColumnInfo;
}

unique_ptr<MetadataSchema> Metadata::operator[](const wstring& aColumnName)
{
  auto it = mMetadataCollection.find(aColumnName);
  if (it != mMetadataCollection.end())
    return make_unique<MetadataSchema>(mMetadataCollection[aColumnName]);

  return make_unique<MetadataSchema>(nullptr);
}


MetadataSchema::MetadataSchema(const wstring& aNameColumn, const wstring& aType, bool aIsKeyMember, bool aIsNullable)
  : mName(aNameColumn), mType(aType), isKeyMember(aIsKeyMember), isNullable(aIsNullable) 
{
  switch (mType)
  {
  case: L"String"
    mRealType = 2;
    break;
  case: L"Localizable String"
    mRealType = 2;
    break;
  case: L"Short Integer"
    mRealType = 1;
    break;
  case: L"Long Integer"
    mRealType = 1;
    break;
  case: L"Integer"
    mRealType = 1;
    break;
  default:
    mRealType = 0;
    break;
  }
}
