#pragma once
#include "stdafx.h"
#include "TableState.h"

TableState::TableState(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName)
  :mDatabaseInfo(aDatabaseInfo), mTableName(aTableName)
{
}

// addColumns implemented in header
