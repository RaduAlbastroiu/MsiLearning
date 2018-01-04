#pragma once

namespace MsiUtil
{
  UINT openDatabase(const wstring& filePath, MSIHANDLE& handleDatabase);
  
  UINT openView(MSIHANDLE aTargetHandle, const wstring& aSqlQuerry, MSIHANDLE& outputHandle);
  UINT runSqlQuerryCommit(MSIHANDLE aTargetHandle, const wstring& aSqlQuerry);

  UINT getFieldCount(MSIHANDLE recordHandle);
  UINT getStringFromRecord(MSIHANDLE recordHandle, int fieldNumber, wstring& resultString);

  UINT getColumnsInfo(MSIHANDLE recordHandle, map<wstring, wstring>& columnsInfo);
  UINT getPrimaryKeys(MSIHANDLE databaseHandle, const wstring& tableName, vector<wstring>& output);

  UINT getSelectedTable(MSIHANDLE viewHandle, vector<wstring> columnNames, vector < map<wstring, wstring> >& resultTable);

  UINT getLastError(wstring& error);

  UINT commit(MSIHANDLE databaseHandle);
}
 
