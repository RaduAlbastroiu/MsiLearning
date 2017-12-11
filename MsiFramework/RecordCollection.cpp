#include "stdafx.h"
#include "RecordCollection.h"

RecordCollection::RecordCollection(MSIHANDLE aView, wstring aTableName, wstring aColumnName):
  mView(aView), mTableName(mTableName), mColumnName(mColumnName)
{
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

  wstring value(lenght+1, L'\0');
  errorMessage = ::MsiRecordGetString(recordHandle, 1, &value[0], &lenght);
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
  auto errorMessage = ::MsiViewFetch(mView, &handleRecord);

  if (errorMessage == ERROR_SUCCESS)
  {
    mRecords.push_back(createRecord(handleRecord));
  }

  return SingleRecord(handleRecord, mView, L"");
}

wstring RecordCollection::getTableName()
{
  return wstring();
}

wstring RecordCollection::getColumnName()
{
  return wstring();
}

wstring RecordCollection::getView()
{
  return wstring();
}
