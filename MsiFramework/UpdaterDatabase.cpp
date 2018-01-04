#pragma once
#include "stdafx.h"
#include "UpdaterDatabase.h"

UpdaterDatabase::UpdaterDatabase(const MSIHANDLE aHandle)
  :mDatabaseHandle(aHandle)// mDatabaseInfo(aHandle)
{
}

UINT UpdaterDatabase::update()
{
  return 0;// mDatabaseInfo.update();
}

void UpdaterDatabase::setTargetTable(const wstring & /*aTableName*/)
{
  //mDatabaseInfo.setTargetTable(aTableName);
}

void UpdaterDatabase::updateColumnWithValue(const wstring & /*aColumnName*/, const wstring & /*aNewValue*/)
{
  //mDatabaseInfo.updateColumnWithValue(aColumnName, aNewValue);
}
