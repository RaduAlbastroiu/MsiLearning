#pragma once
//#include "DatabaseInfo.h"

class UpdaterDatabase
{
public:
  UpdaterDatabase(const MSIHANDLE aHandle);

  // update
  UINT update();
  void setTargetTable(const wstring& aTableName);
  void updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);

private:
  MSIHANDLE mDatabaseHandle;
  //DatabaseInfo mDatabaseInfo;
};
