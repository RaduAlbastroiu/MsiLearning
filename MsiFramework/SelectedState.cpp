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

