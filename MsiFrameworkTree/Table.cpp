#pragma once
#include "stdafx.h"
#include "Table.h"

Table::Table(const DatabaseInfo & aDatabaseInfo)
{
  mDatabaseInfo = aDatabaseInfo;
}

// addColumns implemented in header
