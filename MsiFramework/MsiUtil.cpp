#include "MsiUtil.h"
#include "stdafx.h"

namespace MsiUtil 
{
  UINT openDatabase(const wstring & filePath, MSIHANDLE& handleDatabase)
  {
    return ::MsiOpenDatabase(filePath, MSIDBOPEN_DIRECT, &handleDatabase);
  }

  UINT openView(MSIHANDLE aTargetHandle, const wstring & aSqlQuerry, MSIHANDLE & outputHandle)
  {
    LPCTSTR sqlQuerry = aSqlQuerry.c_str();

    UINT mErrorMessage = ::MsiDatabaseOpenView(aTargetHandle, sqlQuerry, &outputHandle);
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

  UINT getFieldCount(MSIHANDLE recordHandle)
  {
    return MsiRecordGetFieldCount(recordHandle);
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

  UINT getColumnsInfo(MSIHANDLE recordHandle, map<wstring, wstring>& columnsInfo)
  {
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

          columnsInfo[name] = type;
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

  UINT getSelectedTable(MSIHANDLE viewHandle, vector<wstring> columnNames, vector<map<wstring, wstring>>& resultTable)
  {
    MSIHANDLE fetch;
    UINT errorMessage = ERROR_SUCCESS;
    while (true)
    {
      // fetch next row
      errorMessage = ::MsiViewFetch(viewHandle, &fetch);
      if (errorMessage != ERROR_SUCCESS)
        return errorMessage;
      
      wstring extracted = L"";
      map<wstring, wstring> row;
      for (size_t i = 0; i < columnNames.size(); i++)
      {
        MsiUtil::getStringFromRecord(fetch, i + 1, extracted);
        row[columnNames[i]] = extracted;
      }
      resultTable.push_back(row);
    }
    return ERROR_SUCCESS;
  }

  UINT commit(MSIHANDLE databaseHandle)
  {
    return ::MsiDatabaseCommit(databaseHandle);
  }

}
