#include "stdafx.h"
#include "RecordCollection.h"

RecordCollection::RecordCollection(MSIHANDLE aView, wstring aTableName, wstring aColumnName):
  mView(aView), mTableName(mTableName), mColumnName(mColumnName)
{
}

RecordCollection::~RecordCollection()
{
  ::MsiCloseHandle(mView);
}

SingleRecord RecordCollection::createRecord(MSIHANDLE recordHandle)
{
  DWORD lenght;
  UINT errorMessage = ::MsiRecordGetString(recordHandle, 1, L"", &lenght);
  
  bool isGood = false;
  if (errorMessage == ERROR_MORE_DATA)
  {
    isGood = true;
  }

  wchar_t value[RECORD_MAX_LENGTH];
  errorMessage = ::MsiRecordGetString(recordHandle, 1, value, &lenght);
  if (errorMessage == ERROR_SUCCESS)
  {
    isGood = true;
  }

  return SingleRecord(recordHandle, mView, value);
}

vector<SingleRecord> RecordCollection::getAllRecords()
{
  UINT errorMessage = ERROR_SUCCESS;

  for (;;)
  {
    MSIHANDLE handleRecord;
    errorMessage = ::MsiViewFetch(mView, &handleRecord);

    if (errorMessage == ERROR_SUCCESS)
    {
      mRecords.push_back(createRecord(handleRecord));
    }
    else
    {
      break;
    }
  }

  return mRecords;
}

SingleRecord RecordCollection::getNextRecord()
{
  MSIHANDLE handleRecord;
  errorMessage = ::MsiViewFetch(mView, &handleRecord);

  if (errorMessage == ERROR_SUCCESS)
  {
    mRecords.push_back(createRecord(handleRecord));
  }
}
