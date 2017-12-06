#pragma once

#include "SingleRecord.h"

#define RECORD_MAX_LENGTH 2048

class RecordCollection
{
  const wstring mTableName;
  const wstring mColumnName;
  const MSIHANDLE mView;

  SingleRecord createRecord(MSIHANDLE recordHandle);

  vector<SingleRecord> mRecords;

public:
  RecordCollection(MSIHANDLE aView, wstring aTableName, wstring aColumnName);
  ~RecordCollection();

  vector<SingleRecord> getAllRecords();
  SingleRecord getNextRecord();

  // maybe later, not sure if it will work
  // bool modifyAllValues(vector<wstring> aValues);

};

