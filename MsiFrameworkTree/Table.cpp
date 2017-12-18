#pragma once
#include "stdafx.h"
#include "Table.h"

Table::Table(const DatabaseInfo& aDatabaseInfo, const wstring& aTableName)
  :mDatabaseInfo(aDatabaseInfo), mTableName(aTableName)
{
}

// addColumns implemented in header
