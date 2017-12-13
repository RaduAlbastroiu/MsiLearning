#pragma once
#include "stdafx.h"

class DatabaseInfo
{
public:
  MSIHANDLE rootHandle;
  MSIHANDLE currentHandle;

  vector<string> tableName;

private:
};
