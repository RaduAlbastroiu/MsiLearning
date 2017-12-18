#pragma once
#include "stdafx.h"
#include "NeutralState.h"

class Database : public Node
{
public:
  Database(const wstring& databasePath);

  unique_ptr<Table> addTable(const wstring& tableName);

  wstring mDatabasePath;

private:
};
