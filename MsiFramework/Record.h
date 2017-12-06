#pragma once

#define RECORD_MAX_LENGTH 2048

class Record
{
  const wstring mTableName;
  const wstring mColumnName;
  const MSIHANDLE mView;

  // the way database handles records
  struct internalRecord
  {
    MSIHANDLE handle;
    wstring value;
  };

  internalRecord createRecord(MSIHANDLE recordHandle);

  vector<internalRecord> mRecords;

public:
  Record(MSIHANDLE aView, wstring aTableName, wstring aColumnName);
  ~Record();

  vector<wstring> getValues();
  wstring getValueAt(unsigned int aPosition);
  bool modifyValueAt(unsigned int aPosition, wstring aValue);

  // maybe later, not sure if it will work
  // bool modifyAllValues(vector<wstring> aValues);

};

