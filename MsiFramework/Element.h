#pragma once

class Element
{
public:
  Element(const wstring& aValue, const wstring& aColumnName, const wstring& aTableName, MSIHANDLE aRowHandle, UINT aFieldNumber);

  wstring getAsString();
  int getAsInt();

  bool isNullable();
  bool isKeyMember();
  bool isInt();
  wstring getTable();
  wstring getColumn();

  void setNullable(bool isNullable);
  void setKeyMember(bool isKeyMember);
  void setIsInt(bool isInt);
  

private:
  wstring mTable;
  wstring mColumn;
  wstring mValue;
  bool mIsNullable;
  bool mIsKeyMember;
  bool mIsInt;

  // update data
  MSIHANDLE mRowHandle;
  UINT mFieldNumber;
};
