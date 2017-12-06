#include "stdafx.h"
#include "Record.h"

Record::Record(MSIHANDLE aView, wstring aTableName, wstring aColumnName):
  mView(aView), mTableName(mTableName), mColumnName(mColumnName)
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
}

Record::~Record()
{
  ::MsiCloseHandle(mView);
}

Record::internalRecord Record::createRecord(MSIHANDLE recordHandle)
{
  internalRecord result;
  result.handle = recordHandle;
  
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
    result.value = value;
  }

  return result;
}

vector<wstring> Record::getValues()
{
  vector<wstring> result;
  for (const auto& rec : mRecords)
  {
    result.push_back(rec.value);
  }

  return result;
}

wstring Record::getValueAt(unsigned int aPosition)
{
  return mRecords[aPosition].value;
}

bool Record::modifyValueAt(unsigned int aPosition, wstring aValue)
{
  if (aPosition < mRecords.size())
  {
    mRecords[aPosition].value = aValue;

    // save
    UINT errorMessage = ::MsiViewModify(mView, MSIMODIFY_REPLACE, mRecords[aPosition].handle);
    if (errorMessage == ERROR_SUCCESS)
      return true;
  }

  // something went wrong
  return false;
}
