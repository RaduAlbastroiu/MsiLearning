#pragma once
#include "MsiUtil.h"

class MetadataSchema;
class Element
{
public:
  Element(const wstring& aValue, const wstring& aColumnName, const MetadataSchema& aTableName, UINT aFieldNumber, UINT aRowNumber);

  wstring getAsString();
  int getAsInt();

  UINT update(const wstring& aNewValue);
  UINT update(int aNewValue);

  bool isNullable();
  bool isKeyMember();
  bool isInt();
  wstring getTable();
  wstring getColumn();

  void setOpenFromCustAct(bool isCustAct);

  void setRowHandle(MSIHANDLE aRowHandle);
  void setViewHandle(MSIHANDLE aViewHandle);
  void setDatabaseHandle(MSIHANDLE aDatabaseHandle);

private:
  wstring mTable;
  wstring mColumn;
  wstring mValue;

  const MetadataSchema& mColumnSchema;
  bool mIsFromCustact;

  // update data
  MSIHANDLE mRowHandle;
  MSIHANDLE mViewHandle;
  MSIHANDLE mDatabaseHandle;
  UINT mRowNumber;
  UINT mFieldNumber;
};
