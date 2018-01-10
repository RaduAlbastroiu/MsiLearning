#include "MsiUtil.h"
#include "stdafx.h"

namespace MsiUtil 
{
  UINT openDatabase(const wstring & aFilePath, MSIHANDLE& handleDatabase)
  {
    LPCWSTR filePath = aFilePath.c_str();
    return ::MsiOpenDatabase(filePath, MSIDBOPEN_DIRECT, &handleDatabase);
  }

  UINT openActiveDatabase(MSIHANDLE hSession)
  {
    return ::MsiGetActiveDatabase(hSession);
  }

  UINT openView(MSIHANDLE hDatabase, const wstring & aSqlQuerry, MSIHANDLE & outputHandle)
  {
    LPCTSTR sqlQuerry = aSqlQuerry.c_str();

    UINT mErrorMessage = ::MsiDatabaseOpenView(hDatabase, sqlQuerry, &outputHandle);

    if (mErrorMessage == ERROR_SUCCESS)
    {
      mErrorMessage = ::MsiViewExecute(outputHandle, 0);
      if (mErrorMessage == ERROR_SUCCESS)
      {
        return ERROR_SUCCESS;
      }
    }
    return mErrorMessage;
  }

  UINT runSqlQuerryCommit(MSIHANDLE aTargetHandle, const wstring & aSqlQuerry)
  {
    MSIHANDLE phView;
    LPCTSTR sqlQuerry = aSqlQuerry.c_str();

    UINT mErrorMessage = ::MsiDatabaseOpenView(aTargetHandle, sqlQuerry, &phView);

    if (mErrorMessage == ERROR_SUCCESS)
    {
      mErrorMessage = ::MsiViewExecute(phView, 0);
      if (mErrorMessage == ERROR_SUCCESS)
      {
        mErrorMessage = ::MsiDatabaseCommit(aTargetHandle);
        if (mErrorMessage == ERROR_SUCCESS)
        {
          return ERROR_SUCCESS;
        }
      }
    }
    return mErrorMessage;
  }

  UINT getFieldCountFromView(MSIHANDLE hView)
  {
    UINT errorMessage = ERROR_SUCCESS;
    MSIHANDLE hRecord;
    errorMessage = ::MsiViewFetch(hView, &hRecord);
    return ::MsiRecordGetFieldCount(hRecord);
  }

  UINT getFieldCount(MSIHANDLE recordHandle)
  {
    return ::MsiRecordGetFieldCount(recordHandle);
  }

  UINT getStringFromRecord(MSIHANDLE recordHandle, int fieldNumber, wstring & resultString)
  {
    DWORD stringLenght = 0;

    // error more memory
    UINT errorMessage = ::MsiRecordGetString(recordHandle, fieldNumber, L"", &stringLenght);

    // null terminated string
    stringLenght++;

    // get the string
    wchar_t result[256];
    errorMessage = ::MsiRecordGetString(recordHandle, fieldNumber, result, &stringLenght);

    // output parameter
    resultString = result;

    return errorMessage;
  }

  UINT getColumnsInfo(MSIHANDLE recordHandle, vector<pair<wstring, wstring>>& columnsInfo)
  {
    // first: column name
    // second: column type
    
    MSIHANDLE nameHandle;
    MSIHANDLE typeHandle; 
    UINT errorMessage = MsiViewGetColumnInfo(recordHandle, MSICOLINFO_NAMES, &nameHandle);
    if (errorMessage == ERROR_SUCCESS)
    {
      errorMessage = MsiViewGetColumnInfo(recordHandle, MSICOLINFO_TYPES, &typeHandle);
      if (errorMessage == ERROR_SUCCESS)
      {
        int nrColumns = getFieldCount(nameHandle);
        columnsInfo.clear();

        for (int i = 1; i <= nrColumns; ++i)
        {
          // get name
          wstring name = L"";
          getStringFromRecord(nameHandle, i, name);

          // get type
          wstring type = L"";
          getStringFromRecord(typeHandle, i, type);

          columnsInfo.push_back(make_pair(name, type));
        }

        return ERROR_SUCCESS;
      }
    }
    return errorMessage;
  }

  UINT getPrimaryKeys(MSIHANDLE databaseHandle, const wstring & tableName, vector<wstring>& output)
  {
    LPCTSTR tableNameP = tableName.c_str();
    MSIHANDLE outputHandle;
    
    UINT errorMessage = ::MsiDatabaseGetPrimaryKeys(databaseHandle, tableNameP, &outputHandle);
    if (errorMessage == ERROR_SUCCESS)
    {
      int nrKeys = getFieldCount(outputHandle);
      output.clear();
      wstring extracted = L"";
      for (int i = 1; i <= nrKeys; i++)
      {
        getStringFromRecord(outputHandle, i, extracted);
        output.push_back(extracted);
      }
    }
    return errorMessage;
  }

  UINT getSelectedTable(MSIHANDLE hView, vector<UINT> columnNumbers, vector<vector<wstring>>& resultTable, vector<MSIHANDLE>& resultTableHandles)
  {
    MSIHANDLE fetch;
    UINT errorMessage = ERROR_SUCCESS;

    // execute view to move cursor at begin
    errorMessage = ::MsiViewExecute(hView, 0);

    // start fetching items
    for(;;)
    {
      // fetch row
      errorMessage = ::MsiViewFetch(hView, &fetch);
      
      // if last 
      if (errorMessage == ERROR_NO_MORE_ITEMS)
        return ERROR_SUCCESS;
      
      resultTableHandles.push_back(fetch);

      // extract every from every column
      wstring extracted = L"";
      vector<wstring> rowData;
      for (const auto& columnNr : columnNumbers )
      {
        MsiUtil::getStringFromRecord(fetch, columnNr, extracted);
        rowData.push_back(extracted);
      }
      resultTable.push_back(rowData);
    }

    return ERROR_SUCCESS;
  }

  UINT setRecord(MSIHANDLE hRecord, vector<wstring> values, vector<bool> type, vector<UINT> fieldNr)
  {
    UINT errorMessage = ERROR_SUCCESS;
    for (size_t i = 0; i < values.size(); ++i)
    {
      if (type[i] == true)
      {
        int newValue = stoi(values[i]);
        errorMessage = ::MsiRecordSetInteger(hRecord, fieldNr[i], newValue);
      }
      else
      {
        LPCTSTR newValue = values[i].c_str();
        errorMessage = ::MsiRecordSetString(hRecord, fieldNr[i], newValue);
      }
    }
    return errorMessage;
  }

  UINT setRecordInteger(bool isCustAct, MSIHANDLE databaseHandle, MSIHANDLE hView, MSIHANDLE recordHandle, unsigned int rowNumber, unsigned int fieldNumber, int value)
  {
    UINT errorMessage = ERROR_SUCCESS;
    errorMessage = ::MsiViewExecute(hView, 0);

    for (unsigned int i = 0; i < rowNumber; i++)
    {
      errorMessage = ::MsiViewFetch(hView, &recordHandle);
    }

    if (isCustAct)
    {
      // inside a custact
      errorMessage = ::MsiViewModify(hView, MSIMODIFY_DELETE, recordHandle);
      if (errorMessage == ERROR_SUCCESS)
      {
        errorMessage = ::MsiRecordSetInteger(recordHandle, fieldNumber, value);
        if (errorMessage == ERROR_SUCCESS)
        {
          errorMessage = ::MsiViewModify(hView, MSIMODIFY_INSERT_TEMPORARY, recordHandle);
        }
      }
    }
    else
    {
      // database opened from the disk
      errorMessage = ::MsiRecordSetInteger(recordHandle, fieldNumber, value);
      if (errorMessage == ERROR_SUCCESS)
      {
        errorMessage = ::MsiViewModify(hView, MSIMODIFY_UPDATE, recordHandle);
        if (errorMessage == ERROR_SUCCESS)
        {
          errorMessage = ::MsiDatabaseCommit(databaseHandle);
        }
      }
    }

    return errorMessage;
  }

  UINT setRecordString(bool isCustAct, MSIHANDLE databaseHandle, MSIHANDLE hView, MSIHANDLE recordHandle, unsigned int rowNumber, unsigned int fieldNumber, const wstring& value)
  {
    LPCTSTR newValue = value.c_str();
    UINT errorMessage = ERROR_SUCCESS;
    errorMessage = ::MsiViewExecute(hView, 0);

    // move cursor to target row
    for (unsigned int i = 0; i < rowNumber; i++)
    {
      errorMessage = ::MsiViewFetch(hView, &recordHandle);
    }

    if (isCustAct)
    {
      // inside a custact
      errorMessage = ::MsiViewModify(hView, MSIMODIFY_DELETE, recordHandle);
      if(errorMessage == ERROR_SUCCESS)
      {
        errorMessage = ::MsiRecordSetString(recordHandle, fieldNumber, newValue);
        if (errorMessage == ERROR_SUCCESS)
        {
          errorMessage = ::MsiViewModify(hView, MSIMODIFY_INSERT_TEMPORARY, recordHandle);
        }
      }
    }
    else
    {
      // database opened from the disk
      errorMessage = ::MsiRecordSetString(recordHandle, fieldNumber, newValue);
      if (errorMessage == ERROR_SUCCESS)
      {
        errorMessage = ::MsiViewModify(hView, MSIMODIFY_UPDATE, recordHandle);
        if (errorMessage == ERROR_SUCCESS)
        {
          errorMessage = ::MsiDatabaseCommit(databaseHandle);
        }
      }
    }
    return errorMessage;
  }


  UINT getLastError(wstring& error)
  {
    UINT errorMessage = ERROR_SUCCESS;
    MSIHANDLE errorHandle = ::MsiGetLastErrorRecord();
    wstring extracted;
    
    // error code
    errorMessage = getStringFromRecord(errorHandle, 1, extracted);
    if (errorMessage != ERROR_SUCCESS)
      return errorMessage;

    error  = L"Error Code: " + extracted;
    
    // found 
    errorMessage = getStringFromRecord(errorHandle, 3, extracted);
    if (errorMessage != ERROR_SUCCESS)
      return errorMessage;

    error += L"; Found: '" + extracted + L"'";
    
    // position
    errorMessage = getStringFromRecord(errorHandle, 4, extracted);
    if (errorMessage != ERROR_SUCCESS)
      return errorMessage;

    if (extracted.size())
    {
      error += L" In: " + extracted;
    }

    return errorMessage;
  }

  UINT insertRecordInView(MSIHANDLE hView, vector<wstring> values, vector<bool> type, vector<UINT> fieldNr)
  {
    MSIHANDLE hFetch;
    UINT errorMessage = ERROR_SUCCESS;
    errorMessage = ::MsiViewExecute(hView, 0);
    if (errorMessage == ERROR_SUCCESS)
    {
      // first fetch
      errorMessage = ::MsiViewFetch(hView, &hFetch);

      // delete old data from record
      errorMessage = ::MsiRecordClearData(hFetch);
     
      // modify hFetched and existing one
      for (size_t i = 0; i < values.size(); ++i)
      {
        if (type[i] == true)
        {
          int newValue = stoi(values[i]);
          errorMessage = ::MsiRecordSetInteger(hFetch, fieldNr[i], newValue);
        }
        else
        {
          LPCTSTR newValue = values[i].c_str();
          errorMessage = ::MsiRecordSetString(hFetch, fieldNr[i], newValue);
        }
      }

      // insert
      if (errorMessage == ERROR_SUCCESS)
      {
        errorMessage = ::MsiViewModify(hView, MSIMODIFY_INSERT_TEMPORARY, hFetch);
      }
    }
    return errorMessage;
  }

  UINT commit(MSIHANDLE databaseHandle)
  {
    return ::MsiDatabaseCommit(databaseHandle);
  }

  UINT createRecord(UINT nrFields)
  {
    return MsiCreateRecord(nrFields);
  }

}
