#pragma once
#include "stdafx.h"
#include "DatabaseInfo.h"

class Table
{
public:
  Table(const DatabaseInfo& aDatabaseInfo);

  template<typename... Types>
  unique_ptr<NeutralState> addColumns(const Types& ... aColumns)
  {
    mDatabaseInfo.addColumns(aColumns...);
    return make_unique<Node>(mDatabaseInfo);
  }

private:
  DatabaseInfo mDatabaseInfo;
};
