#pragma once

namespace MsiUtil
{
  UINT commit(MSIHANDLE databaseHandle);

  UINT openDatabase(const wstring& filePath, MSIHANDLE& handleDatabase);
  UINT openActiveDatabase(MSIHANDLE& hSession);
  
  UINT openView(MSIHANDLE aTargetHandle, const wstring& aSqlQuerry, MSIHANDLE& outputHandle);
  UINT runSqlQuerryCommit(MSIHANDLE aTargetHandle, const wstring& aSqlQuerry);

  UINT getFieldCount(MSIHANDLE recordHandle);
  UINT getStringFromRecord(MSIHANDLE recordHandle, int fieldNumber, wstring& resultString);

  UINT getColumnsInfo(MSIHANDLE recordHandle, vector<pair<wstring, wstring>>& columnsInfo);
  UINT getPrimaryKeys(MSIHANDLE databaseHandle, const wstring& tableName, vector<wstring>& output);

  UINT getSelectedTable(MSIHANDLE viewHandle, vector<UINT> columnNumbers, vector<vector<wstring>>& resultTable, vector<MSIHANDLE>& resultTableHandles);

  UINT setRecordInteger(bool isCustAct, MSIHANDLE databaseHandle, MSIHANDLE viewHandle, MSIHANDLE recordHandle, unsigned int rowNumber, unsigned int fieldNumber, int value);
  UINT setRecordString(bool isCustAct, MSIHANDLE databaseHandle, MSIHANDLE viewHandle, MSIHANDLE recordHandle, unsigned int rowNumber, unsigned int fieldNumber, const wstring& value);

  UINT getLastError(wstring& error);
}
 
