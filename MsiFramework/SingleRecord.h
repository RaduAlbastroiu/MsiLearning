#pragma once
class SingleRecord
{
  const MSIHANDLE mHandle;
  const MSIHANDLE mView;
  wstring mValue;

public:
  SingleRecord(const MSIHANDLE aHandle, const MSIHANDLE aView, const wstring aValue);
  ~SingleRecord();

  wstring getValue() const;
  bool setValue(wstring aValue);
};

