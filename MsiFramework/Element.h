#pragma once
#include "MsiUtil.h"

class MetadataSchema;

template<class T>
class IElement {
public:
  virtual T getValue() = 0;
  virtual UINT update(const T& aNewValue) = 0;
  virtual wstring getTable() = 0;
  virtual wstring getColumn() = 0;
  virtual const MetadataSchema& getColumnMetadata() = 0;
  virtual void setOpenFromCustAct(bool isCustAct) = 0;
  virtual void setRowHandle(MSIHANDLE aRowHandle) = 0;
  virtual void setViewHandle(MSIHANDLE aViewHandle) = 0;
  virtual void setDatabaseHandle(MSIHANDLE aDatabaseHandle) = 0;
};


//template<class T>
class Element
{
public:
  Element(const wstring& aValue, const wstring& aColumnName, const MetadataSchema& aTableName, UINT aFieldNumber, UINT aRowNumber, bool aIsCustact);
  
  // TODO: getAsX() -> getValue() with type deduction
  wstring getAsString();
  int getAsInt();
  //T getValue();

  UINT update(const wstring& aNewValue);
  UINT update(int aNewValue);
  //UINT update(const T& aNewValue);

  wstring getTable();
  wstring getColumn();
  const MetadataSchema& getColumnMetadata();

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
