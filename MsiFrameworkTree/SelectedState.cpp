#pragma once
#include "stdafx.h"
#include "SelectedState.h"


SelectedState::SelectedState(const DatabaseInfo & aDatabaseInfo)
  :mDatabaseInfo(aDatabaseInfo)
{
}

unique_ptr<Row> SelectedState::getRow(int aRowNumber)
{
  return mDatabaseInfo.select()->getRowWithNumber(aRowNumber);
}

unique_ptr<MetadataSchema> SelectedState::getColumnInfo(const wstring & aColumnName)
{
  return mDatabaseInfo.select()->getColumnInfo(aColumnName);
}

